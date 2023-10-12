CC = gcc
CFLAGS = -ggdb -O2 -Wall -fPIC -c `pkg-config --cflags babeltrace2` `pkg-config --cflags glib-2.0` `pkg-config --cflags json-c`
LDFLAGS = `pkg-config --libs babeltrace2` `pkg-config --libs glib-2.0` `pkg-config --libs json-c`
OBJFILES = plugin.o sink.o event.o clock.o sink/elastic-client/elastic_cli.so metadata.o network.o storage.o
CFILES = plugin.c sink/sink.c sink/event.c sink/clock.c sink/metadata.c sink/network.c sink/storage.c

plugin:
	$(CC) $(CFILES) $(CFLAGS)
	ld $(OBJFILES) -o babeltrace-plugin-elastic.so -shared $(LDFLAGS)

clean:
	rm *.o *.so
