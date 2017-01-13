# 使用 	Thread 數到 1000000

此篇將會介紹如何在 C 語言上執行 Thread，且也會介紹在使用時會遇到的同步問題該如何解決(semaphore)。

### 目標
使用 4 個 Thread 把數值從 0 數到 1000000。

### 起手

引入 Thread 的 Library：

```c
#include <pthread.h>
...
```

> pthread 的 p 其實是代表著 POSIX。可以說是使用 符合 POSIX 1003.1c 標準的 Thread Library。

宣告並初始化要計數的變數：

```c
static int a=0;
```

宣告需要使用到的 Thread，並初始化數值：

```c
int main() {
	pthread_t t1, t2, t3, t4;
	...
}
```

宣告 thread 要使用的 function：

```c
void *counter_thread(void *arg) {
	printf("Thread ID:%lu\n", pthread_self());
	printf("Argument:%d\n", (int)arg);
	int i=0;
	for(i=0;i<250000;i++){
		a++;	
	}
	pthread_exit(NULL);
}
```