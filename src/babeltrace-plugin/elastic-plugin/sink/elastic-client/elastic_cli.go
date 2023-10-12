package main

import (
	"C"
	"context"
	"fmt"
	"strings"
	"time"

	elasticsearch "github.com/elastic/go-elasticsearch/v7"
	esapi "github.com/elastic/go-elasticsearch/v7/esapi"
	"github.com/elastic/go-elasticsearch/v7/esutil"
)
import (
	"encoding/json"
	"io"
	"os"
	"strconv"
)

var esWriter *elasticSearchWriter

type elasticSearchWriter struct {
	es_client  *elasticsearch.Client
	ctx        context.Context
	index_name string
	bi         esutil.BulkIndexer
}

func elkEnabled() (bool, error) {
	value, defined := os.LookupEnv("ELK_ENABLED")
	if !defined {
		// default is True
		value = "True"
	}
	return strconv.ParseBool(value)
}

//export startElasticClient
func startElasticClient() C.int {
	enabled, err := elkEnabled()
	if !enabled || err != nil {
		return 0
	}

	ctx := context.Background()
	cfg := elasticsearch.Config{
		Addresses:            strings.Split(os.Getenv("ES_ADDRESSES"), ", "),
		MaxRetries:           10,
		EnableRetryOnTimeout: true,
		Username:             os.Getenv("ES_USER"),
		Password:             os.Getenv("ES_PWD"),
	}
	es, err := elasticsearch.NewClient(cfg)
	if err != nil {
		fmt.Print(err, "\n")
		return 1
	}
	mappings := string(`{
		"mappings": {
			"properties": {
			"time_called": { "type": "date_nanos" },
			"time_returned": { "type": "date_nanos" }
			}
		}
	}`)
	err = createIndex(es, mappings)
	if err != nil {
		fmt.Printf("failed to create index %s: %v", os.Getenv("ES_INDEX_NAME"), err)
		return 1
	}
	biConf := esutil.BulkIndexerConfig{
		Index:         os.Getenv("ES_INDEX_NAME"),
		Client:        es,
		NumWorkers:    4,
		FlushBytes:    7000000,
		FlushInterval: 30 * time.Second,
	}
	bi, err := esutil.NewBulkIndexer(biConf)
	if err != nil {
		fmt.Print(err, "\n")
		return 1
	}
	esWriter = &elasticSearchWriter{
		es_client:  es,
		ctx:        ctx,
		index_name: os.Getenv("ES_INDEX_NAME"),
		bi:         bi,
	}
	return 0
}

func createIndex(es_client *elasticsearch.Client, mappings string) error {
	var res *esapi.Response
	var err error
	if mappings != "" {
		res, err = es_client.Indices.Create(os.Getenv("ES_INDEX_NAME"), es_client.Indices.Create.WithBody(strings.NewReader(mappings)))
	} else {
		res, err = es_client.Indices.Create(os.Getenv("ES_INDEX_NAME"))
	}
	if err != nil {
		return err
	}

	var r map[string]interface{}
	if err := json.NewDecoder(res.Body).Decode(&r); err != nil {
		return fmt.Errorf("failed to parse the response body: %s", err)
	}

	if res.StatusCode != 200 {
		var errorstr map[string]interface{} = r["error"].(map[string]interface{})
		return fmt.Errorf("%s: %s", errorstr["type"].(string), errorstr["reason"].(string))
	}

	return nil
}

//export sendEventElastic
func sendEventElastic(json *C.char, singleEvent C.int) C.int {
	enabled, err := elkEnabled()

	if !enabled || err != nil {
		discard, derr := strconv.ParseBool(os.Getenv("BABELTRACE_DISCARD"))

		if !discard || derr != nil {
			fmt.Println(C.GoString(json))
			return 0
		}

		fmt.Fprintln(io.Discard, C.GoString(json))
		return 0
	}

	if singleEvent == 1 {
		err = indexSingleEvent(C.GoString(json))
	} else {
		err = add2BulkIndexer(C.GoString(json))
	}

	if err != nil {
		fmt.Print(err, "\n")
		return 1
	}
	return 0
}

func indexSingleEvent(json string) error {
	req := esapi.IndexRequest{
		Index: esWriter.index_name,
		Body:  strings.NewReader(json),
	}
	res, err := req.Do(esWriter.ctx, esWriter.es_client)
	if err != nil {
		return fmt.Errorf("failed sending event to Elasticsearch: %s", err)
	}
	defer res.Body.Close()
	if res.IsError() {
		return fmt.Errorf("%s error indexing document", res.Status())
	}
	return nil
}

func add2BulkIndexer(json string) error {
	err := esWriter.bi.Add(
		esWriter.ctx,
		esutil.BulkIndexerItem{
			Action: "index",
			Body:   strings.NewReader(json),
			OnFailure: func(ctx context.Context, item esutil.BulkIndexerItem, res esutil.BulkIndexerResponseItem, err error) {
				if err != nil {
					fmt.Print("BulkIndexer error: ", err, "\n")
				} else {
					fmt.Print("BulkIndexer failed: ", res.Error.Type, ": ", res.Error.Reason, "\n")
				}
			},
		},
	)
	if err != nil {
		return fmt.Errorf("unexpected error: %s", err)
	}
	return nil
}

//export closeElasticClient
func closeElasticClient() C.int {
	enabled, err := elkEnabled()
	if !enabled || err != nil {
		return 0
	}

	if err := esWriter.bi.Close(esWriter.ctx); err != nil {
		fmt.Print(err, "\n")
		return 1
	}
	return 0
}

func main() {}
