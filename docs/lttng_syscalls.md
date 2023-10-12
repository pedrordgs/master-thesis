## Raw version

| Syscall name     | Arg0              | Arg1                          | Arg3                  | Arg4               | Arg5             | Arg6                    | Arg7                    | Arg8                    | Arg9                    | Arg10           | Return value |
| ---------------- | ----------------- | ----------------------------- | --------------------- | ------------------ | ---------------- | ----------------------- | ----------------------- | ----------------------- | ----------------------- | --------------- | :----------: |
| **read**         | fd (uint32)       | count (uint64)                | buf (pointer)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **write**        | fd (uint32)       | buf (pointer)                 | count (uint64)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **open**         | filename (string) | flags (int32)                 | mode (uint16)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **close**        | fd (uint32)       | -                             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **stat**         | filename (string) | statbuf (pointer)             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **fstat**        | fd (uint32)       | statbuf (pointer)             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **lstat**        | filename (string) | statbuf (pointer)             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **lseek**        | fd (uint32)       | offset (int64)                | whence (uint32)       | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **pread64**      | fd (uint32)       | count (uint64)                | pos (int64)           | buf (pointer)      | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **pwrite64**     | fd (uint32)       | buf (pointer)                 | count (uint64)        | pos (int64)        | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **readv**        | fd (uint64)       | vec (pointer)                 | vlen (uint64)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **writev**       | fd (uint64)       | vec (pointer)                 | vlen (uint64)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **socket**       | family (int32)    | type (int32)                  | protocol (int32)      | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **connect**      | fd (int32)        | uservaddr (pointer)      | addrlen (int32)  | family (uint16)    | dport (uint16)   | _v4addr_lentgh (uint32) | v4addr ([uint8])        | _v6addr_length (uint32) | v6addr ([uint16])       | -               |    int64     |
| **accept**       | fd (int32)        | upeer_sockaddr (pointer) | upeer_addrlen (int32) | family (uint16)    | sport (uint16)   | _v4addr_length (uint32) | v4addr ([uint8])        | _v6addr_length (uint32) | v6addr ([uint16])       | -               |    int64     |
| **sendto**       | fd (int32)        | buff (pointer)                | len (uint64)          | flags (uint32)     | addr (pointer)   | addr_len (int32)        | -                       | -                       | -                       | -               |    int64     |
| **recvfrom**     | fd (int32)        | size (uint64)                 | flags (uint32)        | addr_len (pointer) | ubuf (pointer)   | addr (pointer)          | -                       | -                       | -                       | -               |    int64     |
| **sendmsg**      | fd (int32)        | msg (pointer)                 | flags (uint32)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **recvmsg**      | fd (int32)        | msg (pointer)                 | flags (uint32)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **bind**         | fd (int32)        | umyaddr (pointer)             | addrlen (int32)       | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **listen**       | fd (int32)        | backlog (int32)               | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **socketpair**   | family (int32)    | type (int32)                  | protocol (int32)      | socket ([int32])   | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **setsockopt**   | fd (int32)        | level (int32)                 | optname (int32)       | optval (pointer)   | optlen (int32)   | -                       | -                       | -                       | -                       | -               |    int64     |
| **getsockopt**   | fd (int32)        | level (int32)                 | optname (int32)       | optlen (pointer)   | optval (pointer) | -                       | -                       | -                       | -                       | -               |    int64     |
| **fsync**        | fd (uint32)       | -                             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **fdatasync**    | fd (uint32)       | -                             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **truncate**     | path (string)     | length (int64)                | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **ftruncate**    | fd (uint32)       | length (uint64)               | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **rename**       | oldname (string)  | newname (string)              | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **creat**        | pathname (string) | mode (uint16)                 | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **unlink**       | pathname (string) | -                             | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **readlink**     | path (string)     | bufsiz (int32)                | buf (pointer)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **mknod**        | filename (string) | mode (uint16)                 | dev (uint32)          | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **fstatfs**      | fd (uint32)       | buf (pointer)                 | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **readahead**    | fd (int32)        | offset (int64)                | count (uint64)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **setxattr**     | pathname (string) | name (string)                 | value (pointer)       | size (uint64)      | flags (int32)    | -                       | -                       | -                       | -                       | -               |    int64     |
| **lsetxattr**    | pathname (string) | name (string)                 | value (pointer)       | size (uint64)      | flags (int32)    | -                       | -                       | -                       | -                       | -               |    int64     |
| **fsetxattr**    | fd (int32)        | name (string)                 | value (pointer)       | size (uint64)      | flags (int32)    | -                       | -                       | -                       | -                       | -               |    int64     |
| **getxattr**     | pathname (string) | name (string)                 | size (uint64)         | value (pointer)    | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **lgetxattr**    | pathname (string) | name (string)                 | size (uint64)         | value (pointer)    | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **fgetxattr**    | fd (int32)        | name (string)                 | size (uint64)         | value (pointer)    | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **listxattr**    | pathname (string) | size (uint64)                 | list (pointer)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **llistxattr**   | pathname (string) | size (uint64)                 | list (pointer)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **flistxattr**   | fd (int32)        | size (uint64)                 | list (pointer)        | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **removexattr**  | pathname (string) | name (string)                 | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **lremovexattr** | pathname (string) | name (string)                 | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **fremovexattr** | fd (int32)        | name (string)                 | -                     | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **openat**       | dfd (int32)       | filename (string)             | flags (int32)         | mode (uint16)      | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **mknodat**      | dfd (int32)       | filename (string)             | mode (uint16)         | dev (uint32)       | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **newfstatat**   | dfd (int32)       | filename (string)             | flag (int32)          | statbuf (pointer)  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **unlinkat**     | dfd (int32)       | pathname (string)             | flag (int 32)         | -                  | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **renameat**     | olddfd (int32)    | oldname (string)              | newdfd (int32)        | newname (string)   | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **readlinkat**   | dfd (int32)       | pathname (string)             | bufsiz (int32)        | buf (pointer)      | -                | -                       | -                       | -                       | -                       | -               |    int64     |
| **accept4**      | fd (int32)        | upeer_sockaddr (pointer)      | upeer_addrlen (int32) | flags (int32) | family (uint16)  | sport (uint16)          | _v4addr_length (uint32) | v4addr ([uint8])        | _v6addr_length (uint32) | v6addr (uint16) |    int64     |


### Examples

<details> 
<summary>read</summary>

```json
{"system_call_name":"read","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.248981303Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.248991760Z","execution_time":10457.0,"category":"FileManagement","event_type":"storage","type":"data","pid":1870915,"procname":"kube-apiserver","ppid":1870892,"hostname":"cloud73","thread":"1870994@cloud73","args":{"fd":10,"count":1954,"ret":42,"buf":824645591040},"tid":1870994,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>write</summary>

```json
{"system_call_name":"write","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.249078063Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.249095760Z","execution_time":17697.0,"category":"FileManagement","event_type":"storage","type":"data","pid":1870915,"procname":"kube-apiserver","ppid":1870892,"hostname":"cloud73","thread":"1870983@cloud73","args":{"fd":5,"count":1,"buf":824664489531,"ret":1},"tid":1870983,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>open</summary>

```json
{"system_call_name":"open","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.564422085Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.564426213Z","execution_time":4128.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":2543139,"procname":"iptables","ppid":35732,"hostname":"cloud73","thread":"2543139@cloud73","args":{"filename":"/etc/ld-musl-x86_64.path","flags":557056,"mode":0,"ret":-2},"tid":2543139,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>close</summary>

```json
{"system_call_name":"close","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.343857753Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.343863120Z","execution_time":5367.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":36087,"procname":"coredns","ppid":36037,"hostname":"coredns-64897985d-sp44c","thread":"36126@coredns-64897985d-sp44c","args":{"fd":12,"ret":0},"tid":36126,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>stat</summary>

```json
```

</details>

<details>
<summary>fstat</summary>

```json
```

</details>

<details>
<summary>lstat</summary>

```json
```

</details>

<details>
<summary>lseek</summary>

```json
{"system_call_name":"lseek","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.250186681Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.250192061Z","execution_time":5380.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":33266,"procname":"etcd","ppid":33209,"hostname":"cloud73","thread":"33287@cloud73","args":{"fd":11,"offset":0,"whence":1,"ret":21616272},"tid":33287,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>pread64</summary>

```json
{"system_call_name":"pread64","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.633199006Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.633203090Z","execution_time":4084.0,"category":"FileManagement","event_type":"storage","type":"data","pid":591263,"procname":"elasticsearch[l","ppid":591251,"hostname":"lttng-trace-cluster-es-node-0","thread":"591722@lttng-trace-cluster-es-node-0","args":{"fd":424,"pos":0,"count":49,"ret":49,"buf":140736213309520},"tid":591722,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>pwrite64</summary>

```json
{"system_call_name":"pwrite64","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.281312402Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.281347092Z","execution_time":34690.0,"category":"FileManagement","event_type":"storage","type":"data","pid":33266,"procname":"etcd","ppid":33209,"hostname":"cloud73","thread":"33319@cloud73","args":{"fd":10,"pos":475136,"count":4096,"buf":824636485632,"ret":4096},"tid":33319,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>readv</summary>

```json
```

</details>

<details>
<summary>writev</summary>

```json
{"system_call_name":"writev","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.517681908Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.517769346Z","execution_time":87438.0,"category":"FileManagement","event_type":"storage","type":"data","pid":589804,"procname":"node","ppid":589779,"hostname":"lttng-trace-kibana-kb-56fb884dc-x5c4h","thread":"589804@lttng-trace-kibana-kb-56fb884dc-x5c4h","args":{"fd":38,"vec":140737488345048,"vlen":2,"ret":6962},"tid":589804,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>socket</summary>

```json
{"system_call_name":"socket","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.342853733Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.342883772Z","execution_time":30039.0,"category":"Communication","event_type":"network","type":"metadata","pid":36087,"procname":"coredns","ppid":36037,"hostname":"coredns-64897985d-sp44c","thread":"1127820@coredns-64897985d-sp44c","args":{"family":2,"protocol":0,"type":526337,"ret":12},"tid":1127820,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>connect</summary>

```json
{"system_call_name":"connect","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.342927989Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.343155734Z","execution_time":227745.0,"category":"Communication","event_type":"network","type":"metadata","pid":36087,"procname":"coredns","ppid":36037,"hostname":"coredns-64897985d-sp44c","thread":"1127820@coredns-64897985d-sp44c","args":{"addrlen":16,"family":2,"fd":12,"_v6addr_length":0,"v4addr":[0,0,0,0],"dport":8080,"_v4addr_length":4,"v6addr":[],"uservaddr":824642135404,"ret":-115},"tid":1127820,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>accept</summary>

```json
{"system_call_name":"accept","call_timestamp":1661805080,"time_called":"2022-08-29T20:31:20.7686458Z","return_timestamp":1661805080,"time_returned":"2022-08-29T20:31:20.7700026Z","execution_time":13568.0,"category":"Communication","event_type":"network","type":"metadata","pid":591263,"procname":"elasticsearch[l","ppid":591251,"hostname":"lttng-trace-cluster-es-node-0","thread":"591574@lttng-trace-cluster-es-node-0","args":{"fd":279,"upeer_addrlen":28,"upeer_sockaddr":140736484820432,"family":2,"_v6addr_length":0,"v4addr":[127,0,0,1],"_v4addr_length":4,"v6addr":[],"ret":378,"sport":43628},"tid":591574,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>sendto</summary>

```json
{"system_call_name":"sendto","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.796893237Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.796919875Z","execution_time":26638.0,"category":"Communication","event_type":"network","type":"data","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"3161621@cloud73","args":{"fd":17,"flags":0,"len":17,"addr":824659193636,"buff":824659193648,"addr_len":12,"ret":17},"tid":3161621,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>recvfrom</summary>

```json
{"system_call_name":"recvfrom","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.796923767Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.797049428Z","execution_time":125661.0,"category":"Communication","event_type":"network","type":"data","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"3161621@cloud73","args":{"fd":17,"size":4096,"flags":0,"addr_len":824672924324,"ubuf":824665079808,"ret":3288,"addr":824672924336},"tid":3161621,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>sendmsg</summary>

```json
{"system_call_name":"sendmsg","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.963777466Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.963807561Z","execution_time":30095.0,"category":"Communication","event_type":"network","type":"data","pid":1,"procname":"systemd","ppid":0,"hostname":"cloud73","thread":"1@cloud73","args":{"fd":57,"flags":16448,"msg":140724184034736,"ret":320},"tid":1,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>recvmsg</summary>

```json
{"system_call_name":"recvmsg","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.96149227Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.96154437Z","execution_time":5210.0,"category":"Communication","event_type":"network","type":"data","pid":36086,"procname":"coredns","ppid":36054,"hostname":"coredns-64897985d-ccznm","thread":"36122@coredns-64897985d-ccznm","args":{"fd":13,"flags":0,"msg":824640518648,"ret":-11},"tid":36122,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>bind</summary>

```json
{"system_call_name":"bind","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.796888256Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.796891346Z","execution_time":3090.0,"category":"Communication","event_type":"network","type":"metadata","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"3161621@cloud73","args":{"fd":17,"umyaddr":824659193636,"addrlen":12,"ret":0},"tid":3161621,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>listen</summary>

```json
{"system_call_name":"listen","call_timestamp":1661805143,"time_called":"2022-08-29T20:32:23.186618026Z","return_timestamp":1661805143,"time_returned":"2022-08-29T20:32:23.186619941Z","execution_time":1915.0,"category":"Communication","event_type":"network","type":"metadata","pid":2492717,"procname":"containerd-shim","ppid":1,"hostname":"cloud73","thread":"2492726@cloud73","args":{"fd":3,"backlog":4096,"ret":0},"tid":2492726,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>socketpair</summary>

```json
{"system_call_name":"socketpair","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.955425944Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.955441473Z","execution_time":15529.0,"category":"Communication","event_type":"network","type":"metadata","pid":2543166,"procname":"runc","ppid":591232,"hostname":"cloud73","thread":"2543172@cloud73","args":{"family":1,"protocol":0,"type":524289,"ret":0,"socket":[7,8]},"tid":2543172,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>setsockopt</summary>

```json
{"system_call_name":"setsockopt","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.343243983Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.343251490Z","execution_time":7507.0,"category":"Communication","event_type":"network","type":"metadata","pid":36087,"procname":"coredns","ppid":36037,"hostname":"coredns-64897985d-sp44c","thread":"36114@coredns-64897985d-sp44c","args":{"fd":14,"level":6,"optname":1,"optlen":4,"optval":824639180148,"ret":0},"tid":36114,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>fsync</summary>

```json
{"system_call_name":"fsync","call_timestamp":1661805088,"time_called":"2022-08-29T20:31:28.294055542Z","return_timestamp":1661805088,"time_returned":"2022-08-29T20:31:28.305282972Z","execution_time":11227430.0,"category":"DeviceManagement","event_type":"storage","type":"data","pid":591263,"procname":"elasticsearch[l","ppid":591251,"hostname":"lttng-trace-cluster-es-node-0","thread":"591630@lttng-trace-cluster-es-node-0","args":{"fd":435,"ret":0},"tid":591630,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>fdatasync</summary>

```json
{"system_call_name":"fdatasync","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.250234432Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.254403921Z","execution_time":4169489.0,"category":"DeviceManagement","event_type":"storage","type":"data","pid":33266,"procname":"etcd","ppid":33209,"hostname":"cloud73","thread":"33287@cloud73","args":{"fd":11,"ret":0},"tid":33287,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>truncate</summary>

```json
```

</details>

<details>
<summary>ftruncate</summary>

```json
{"system_call_name":"ftruncate","call_timestamp":1661805085,"time_called":"2022-08-29T20:31:25.219618082Z","return_timestamp":1661805085,"time_returned":"2022-08-29T20:31:25.219639863Z","execution_time":21781.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":284,"procname":"systemd-journal","ppid":1,"hostname":"cloud73","thread":"284@cloud73","args":{"fd":20,"length":33554432,"ret":0},"tid":284,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>rename</summary>

```json
{"system_call_name":"rename","call_timestamp":1661805088,"time_called":"2022-08-29T20:31:28.305456224Z","return_timestamp":1661805088,"time_returned":"2022-08-29T20:31:28.305528483Z","execution_time":72259.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":591263,"procname":"elasticsearch[l","ppid":591251,"hostname":"lttng-trace-cluster-es-node-0","thread":"591630@lttng-trace-cluster-es-node-0","args":{"oldname":"/usr/share/elasticsearch/data/nodes/0/indices/25QHgwDiSHejsbfIJ7vjvw/0/_state/retention-leases-19872.st.tmp","newname":"/usr/share/elasticsearch/data/nodes/0/indices/25QHgwDiSHejsbfIJ7vjvw/0/_state/retention-leases-19872.st","ret":0},"tid":591630,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>creat</summary>

```json
```

</details>


<details>
<summary>unlink</summary>

```json
{"system_call_name":"unlink","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.633255914Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.633280153Z","execution_time":24239.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":591263,"procname":"elasticsearch[l","ppid":591251,"hostname":"lttng-trace-cluster-es-node-0","thread":"591722@lttng-trace-cluster-es-node-0","args":{"pathname":"/usr/share/elasticsearch/data/nodes/0/indices/25QHgwDiSHejsbfIJ7vjvw/0/index/_712z_Lucene85FieldsIndex-doc_ids_e25y.tmp","ret":0},"tid":591722,"session_name":"sample-session","cpu":0}
```

</details>

<details>
<summary>readlink</summary>

```json
{"system_call_name":"readlink","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.802833224Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.802850622Z","execution_time":17398.0,"category":"Other","event_type":"storage","type":"metadata","pid":2543147,"procname":"docker-init","ppid":29686,"hostname":"cloud73","thread":"2543147@cloud73","args":{"path":"","bufsiz":4096,"ret":20,"buf":140737488345904},"tid":2543147,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>mknod</summary>

```json
```

</details>


<details>
<summary>fstatfs</summary>

```json
{"system_call_name":"fstatfs","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.305334975Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.305338932Z","execution_time":3957.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"619063@cloud73","args":{"fd":17,"ret":0,"buf":824670099680},"tid":619063,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>readahead</summary>

```json
```

</details>


<details>
<summary>setxattr</summary>

```json
{"system_call_name":"setxattr","call_timestamp":1661805123,"time_called":"2022-08-29T20:32:03.532237908Z","return_timestamp":1661805123,"time_returned":"2022-08-29T20:32:03.532246478Z","execution_time":8570.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":1,"procname":"systemd","ppid":0,"hostname":"cloud73","thread":"1@cloud73","args":{"pathname":"/sys/fs/cgroup/unified/kubepods.slice/kubepods-burstable.slice","size":32,"name":"trusted.invocation_id","value":140724184034144,"flags":0,"ret":0},"tid":1,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>lsetxattr</summary>

```json
```

</details>

<details>
<summary>fsetxattr</summary>

```json
```

</details>

<details>
<summary>getxattr</summary>

```json
```

</details>

<details>
<summary>lgetxattr</summary>

```json
```

</details>

<details>
<summary>fgetxattr</summary>

```json
```

</details>

<details>
<summary>listxattr</summary>

```json
```

</details>

<details>
<summary>llistxattr</summary>

```json
```

</details>

<details>
<summary>flistxattr</summary>

```json
```

</details>


<details>
<summary>removexattr</summary>

```json
{"system_call_name":"removexattr","call_timestamp":1661805123,"time_called":"2022-08-29T20:32:03.532249395Z","return_timestamp":1661805123,"time_returned":"2022-08-29T20:32:03.532254422Z","execution_time":5027.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":1,"procname":"systemd","ppid":0,"hostname":"cloud73","thread":"1@cloud73","args":{"pathname":"/sys/fs/cgroup/unified/kubepods.slice/kubepods-burstable.slice","name":"trusted.delegate","ret":-61},"tid":1,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>lremovexattr</summary>

```json
```

</details>

<details>
<summary>fremovexattr</summary>

```json
```

</details>

<details>
<summary>openat</summary>

```json
{"system_call_name":"openat","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.457363285Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.457427007Z","execution_time":63722.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"2401721@cloud73","args":{"filename":"/sys/fs/cgroup/systemd/kubepods.slice/kubepods-besteffort.slice","dfd":-100,"mode":0,"flags":524288,"ret":17},"tid":2401721,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>mknodat</summary>

```json
{"system_call_name":"mknodat","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.927280115Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.927293345Z","execution_time":13230.0,"category":"Other","event_type":"other","type":"metadata","pid":29686,"procname":"dockerd","ppid":1,"hostname":"cloud73","thread":"32972@cloud73","args":{"filename":"/var/run/docker/containerd/5aae3f49f2c26977d03eb437ca6b3315b65b243bb31411c3aca762c878764350/dfacef19900fa65ae8f17969e0ce79101f500a2162368e4345bee9dc3213ba67-stdout","dfd":-100,"mode":4544,"dev":0,"ret":0},"tid":32972,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>newfstatat</summary>

```json
{"system_call_name":"newfstatat","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.457469540Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.457488008Z","execution_time":18468.0,"category":"FileManagement","event_type":"storage","type":"metadata","pid":33431,"procname":"kubelet","ppid":1,"hostname":"cloud73","thread":"2401721@cloud73","args":{"filename":"/sys/fs/cgroup/systemd/kubepods.slice/kubepods-besteffort.slice/cgroup.procs","dfd":-100,"flag":256,"statbuf":824663970952,"ret":0},"tid":2401721,"session_name":"sample-session","cpu":2}
```

</details>

<details>
<summary>unlinkat</summary>

```json
{"system_call_name":"unlinkat","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.989036895Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.989086099Z","execution_time":49204.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":591232,"procname":"containerd-shim","ppid":1,"hostname":"cloud73","thread":"591240@cloud73","args":{"pathname":"/tmp/runc-process3858097528","dfd":-100,"flag":0,"ret":0},"tid":591240,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>renameat</summary>

```json
{"system_call_name":"renameat","call_timestamp":1661805079,"time_called":"2022-08-29T20:31:19.988233071Z","return_timestamp":1661805079,"time_returned":"2022-08-29T20:31:19.988244437Z","execution_time":11366.0,"category":"InformationManagement","event_type":"storage","type":"metadata","pid":2543166,"procname":"runc","ppid":591232,"hostname":"cloud73","thread":"2543172@cloud73","args":{"olddfd":-100,"oldname":"/run/containerd/io.containerd.runtime.v2.task/moby/5aae3f49f2c26977d03eb437ca6b3315b65b243bb31411c3aca762c878764350/.dfacef19900fa65ae8f17969e0ce79101f500a2162368e4345bee9dc3213ba67.pid","newdfd":-100,"newname":"/run/containerd/io.containerd.runtime.v2.task/moby/5aae3f49f2c26977d03eb437ca6b3315b65b243bb31411c3aca762c878764350/dfacef19900fa65ae8f17969e0ce79101f500a2162368e4345bee9dc3213ba67.pid","ret":0},"tid":2543172,"session_name":"sample-session","cpu":3}
```

</details>

<details>
<summary>readlinkat</summary>

```json
{"system_call_name":"readlinkat","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.800802027Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.800831204Z","execution_time":29177.0,"category":"Other","event_type":"storage","type":"metadata","pid":2543141,"procname":"runc","ppid":29686,"hostname":"cloud73","thread":"2543141@cloud73","args":{"pathname":"/proc/self/exe","dfd":-100,"bufsiz":128,"ret":13,"buf":824634982400},"tid":2543141,"session_name":"sample-session","cpu":1}
```

</details>

<details>
<summary>accept4</summary>

```json
{"system_call_name":"accept4","call_timestamp":1661805078,"time_called":"2022-08-29T20:31:18.343183774Z","return_timestamp":1661805078,"time_returned":"2022-08-29T20:31:18.343208175Z","execution_time":24401.0,"category":"Communication","event_type":"network","type":"metadata","pid":36087,"procname":"coredns","ppid":36037,"hostname":"coredns-64897985d-sp44c","thread":"36114@coredns-64897985d-sp44c","args":{"fd":8,"upeer_addrlen":112,"flags":526336,"upeer_sockaddr":824639179696,"family":10,"_v6addr_length":8,"v4addr":[],"_v4addr_length":0,"v6addr":[0,0,0,0,0,65535,32512,1],"ret":14,"sport":55450},"tid":36114,"session_name":"sample-session","cpu":2}
```

</details>