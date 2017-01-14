# 使用 	Thread 數到 1000000

此篇將會介紹如何在 C 語言上執行 thread，且也會介紹在使用時會遇到的同步問題該如何解決(semaphore)。

### 目標
使用 4 個 Thread 把數值從 0 數到 1000000。

### 起手

引入 Thread 的 Library：

```c
#include <pthread.h>
...
```

> pthread 的 p 其實是代表著 POSIX。可以說是使用 符合 POSIX 1003.1c 標準的 thread Library。

宣告並初始化要計數的變數：

```c
static int a=0;
```

宣告需要使用到的 thread，並初始化數值：

```c
int main() {
	pthread_t t1, t2, t3, t4;
	int t = 1;
	...
}
```

宣告 thread 要使用的 function。其中使用：

* `pthread_self`：顯示目前 thread 的 ID。
* `pthread_exit`：thread 結束自己。

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
建立 thread 使用：

* `pthread_create`：
	* 參數 1：pthread_t。
	* 參數 2：要設定 thread 的屬性（一般使用 NULL）。
	* 參數 3：thread 要使用的 function。
	* 參數 4：傳入 function 的參數。

在此建立了 4 個 thread，其使用的 function 為```counter_thread```，傳入參數為`t`（轉成型態`void *`）。

```c
int main(){
	...
	pthread_create(&t1, NULL, counter_thread, (void *)t);
	pthread_create(&t2, NULL, counter_thread, (void *)t);
	pthread_create(&t3, NULL, counter_thread, (void *)t);
	pthread_create(&t4, NULL, counter_thread, (void *)t);
	...
}
```

擷取各 thread 執行狀況，使用：

* pthread_join：
	*  參數 1：pthread_t。
	*  參數 2：結束後的回傳值（一般使用 NULL）。

使用後，會在指定的 thread 結束後，才會繼續往下執行。透過它，我們可以確認所有 thread 結束後，在使用`printf`看看最後的結果：

```c
int main(){
	...
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	printf("Value= %d\n", a);
	return 0;
}
```
執行看看：

```shell
$ ./count_to_1000000.o
Thread ID:123145511104512
Thread ID:123145511641088
Thread ID:123145512714240
Thread ID:123145512177664
Argument:1
Argument:1
Argument:1
Argument:1
Value= 302607
```
可以發現，這並不是我們想要的結果。這個原因在於 thread 間轉換時，造成的執行錯誤。所以我們需要透過`semaphore`來處理這個問題。

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

static int a=0;
static sem_t sem; //建立 semaphore signal

void *counter_thread(void *arg) {
    printf("Thread ID:%lu\n", pthread_self());
    printf("Argument:%d\n", (int)arg);
    int i=0;
    for(i=0;i<250000;i++){
        sem_wait(&sem); // 確認其他 thread 做完了沒有（還沒的話，不往下執行，以免產生指令順序錯誤的問題）
        a++;
        sem_post(&sem); // 執行完成後，修改 signal 的狀況，告知執行完畢
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1,t2,t3,t4;
    int t = 1;
    // 初始化 semaphore signal
    if (sem_init(&sem, 0, 1)== -1){
        printf("err");
        exit (1);
    }


    pthread_create(&t1, NULL, counter_thread, (void *)t);
    pthread_create(&t2, NULL, counter_thread, (void *)t);
    pthread_create(&t3, NULL, counter_thread, (void *)t);
    pthread_create(&t4, NULL, counter_thread, (void *)t);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    printf("Value= %d\n", a);
    sem_destroy(&sem); // 釋放 semaphore signal
    return 0;
}
```