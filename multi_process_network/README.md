# Multi process network

使用三種方式，完成多人連線聊天室：

* fork
* thread
* select

## fork

### 運行方式(程式在 `using_fork` 資料夾中)：

```shell
# 編譯
$ gcc using_fork.c -o server.o
$ gcc client.c -o client.o
# 執行
$ ./server.o
$ ./client.o
```
### snapshot
![using_fork](https://github.com/YanHaoChen/Learning-C/blob/master/multi_process_network/using_fork/images/using_fork.png?raw=true)

## thread

### 運行方式(程式在 `using_thread` 資料夾中)：

```shell
# 編譯
$ gcc using_thread.c -o server.o
$ gcc client.c -o client.o
# 執行
$ ./server.o
$ ./client.o
```
### snapshot
![using_fork](https://github.com/YanHaoChen/Learning-C/blob/master/multi_process_network/using_thread/images/using_thread.png?raw=true)

## select

### 運行方式(程式在 `using_select` 資料夾中)：

```shell
# 編譯
$ gcc using_select.c -o server.o
$ gcc client.c -o client.o
# 執行
$ ./server.o
$ ./client.o
```
### snapshot
![using_fork](https://github.com/YanHaoChen/Learning-C/blob/master/multi_process_network/using_select/images/using_select.png?raw=true)