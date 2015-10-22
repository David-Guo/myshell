# 从零构建自己的 mini shell

## 1. Shell Prompt

执行`mysh`后立马打印用户名`welcome to mysh by <student ID>`，并显示当前工作目录` <username> in <current working directory>`

思路：编写函数`mysh_print_promt()`输出信息，放在`mysh`主循环的最开头调用，就能在每次巡回时打印信息。

实现如下：

```C
#define PATH_BUFSIZE 1024

void mysh_print_promt() {
    /* Print "<username> in <current working directory>" */
    char namebuf[PATH_BUFSIZE];
    getlogin_r(namebuf, sizeof(namebuf));
    printf("%s in ", namebuf);
    char pathbuf[PATH_BUFSIZE];
    getcwd(pathbuf, sizeof(pathbuf));
    printf("%s\n", pathbuf);

    /* Print ">mysh " */
    printf(">mysh");
}
```

## 2. Command Parser


## Question

将读进的每一行解析到 command 结构的各个变量中，由 mode 控制前后台执行
* 需要搜索字符串中的特定字符 & 
* 字符串处理，分割字符字符串到 command 结构中
* 链表初始化后怎么释放申请的内存？

#include <string.h>j
函数struct command* mysh_parse_command(char *line)

struct command* command;
char* pStart = line;
while ( (*pStart != '\n') && (*pStart != '\0') ){
	if ( *pStart == '&' ） command->mode = BACKGROUND_EXECUTION;
	else command->mode = FOREGROUND_EXECUTION;
	pStrat++;	
}
char* res;
while ( (res = strsep(&line, " ")) != NULL ){
	*command->root->args++ = strdup(res);
}
return command;

函数int mysh_exec_command(struct command*)

int rtun;
rtun = fork();
if ( rtun == 0 ){
	rtun = execvp(*command->root->args, command->root->args);
	}
else{
	wait(&status);
	if(status == 0) printf("%s exit abnormally", *command->root->args);
}
return rtun;



## Reference


