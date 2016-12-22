# 讀取資料

在 C 中，讀取資料可以透過```<stdio.h>```內的函式達成。其中，又可以透過三種方式讀出內容，分別為`fgetc`、`fgets`、`fscanf`。實作方式如下：

### 先準備好要讀取的檔案（`test.txt`）

```
I'm reading!
Be quiet!
```

### 宣告指向檔案的指標（read_file.c）

```c
FILE *file_print;
```

### 使用`fgetc`
	
讀取一個字元，直到讀完目標檔案為止（函式回傳 EOF）。

```c
// with fgetc
     char get_char;
     file_print = fopen("./test.txt","r");

     if(file_print == NULL){
         printf("error");
         exit(1);
     }
     while((get_char=fgetc(file_print)) != EOF){
         printf("%c",get_char);
     }
     fclose(file_print);
```

### 使用`fgets`

讀取固定長度字串，直到讀完目標檔案為止（函式回傳 NULL）。

#### `fgets`參數格式
```c
fgets(存放讀取到的字串的變數, 讀取一次的字串長度, 目標檔案)
```
> 字串長度（第二個參數）建議設定與變數長度（第一個參數）相等。

```c
//with fgets
     char get_str[20];
     file_print = fopen("./test.txt","r");

     if(file_print == NULL){
         printf("error");
         exit(1);
     }
     printf("\n");
     while(fgets(get_str,20,file_print) != NULL){
         printf("%s",get_str);
     }
     fclose(file_print);
```

### 使用`fscanf`

依給定的格式讀取（參數二），直到讀完目標檔案為止（函式回傳 EOF）。

#### `fscanf`參數格式

```c
fscanf(目標檔案, 格式, 存放讀取到的字串的變數)
```

```c
//with fscanf
     char get_str2[20];
     file_print = fopen("./test.txt","r");

     if(file_print == NULL){
         printf("error");
         exit(1);
     }
     printf("\n");
     while(fscanf(file_print,"%s",get_str2) != EOF){
         printf("%s ",get_str2);
     }
     fclose(file_print);
```

> 讀取完後，記得都要使用`fclose`關閉檔案。

### 結果
```c
./read_file.out
I'm reading now!
Be quiet!

I'm reading now!
Be quiet!

I'm reading now! Be quiet! 
```