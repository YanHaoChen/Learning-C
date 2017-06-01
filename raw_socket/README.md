# Packet Capture Analyze

### Capture 100 packets and print out a summary of the packets

```shell
# 編譯
$ gcc raw_socket_all.c -o raw_socket_all.o
# 執行
$ sudo ./raw_socket_all.o
```
![hw1](https://github.com/YanHaoChen/Learning-C/blob/master/raw_socket/images/hw1.png?raw=true)
### Capture 10 UDP packets
```shell
# 編譯
$ gcc raw_socket_udp.c -o raw_socket_udp.o
# 執行
$ sudo ./raw_socket_udp.o
```
![hw2](https://github.com/YanHaoChen/Learning-C/blob/master/raw_socket/images/hw2.png?raw=true)
### Capture 10 TCP packets
```shell
# 編譯
$ gcc raw_socket_tcp.c -o raw_socket_tcp.o
# 執行
$ sudo ./raw_socket_tcp.o
```
![hw3](https://github.com/YanHaoChen/Learning-C/blob/master/raw_socket/images/hw3.png?raw=true)
### IP Spoof Attack
```shell
# 編譯
$ gcc injection.c -o injection.o
# 執行
$ sudo ./injection.o 192.168.12.11 8.8.8.8
```
![hw4](https://github.com/YanHaoChen/Learning-C/blob/master/raw_socket/images/hw4.png?raw=true)