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
``````

## 2. Command Parser


### Question

将读进的每一行解析到 command 结构的各个变量中，由 mode 控制前后台执行
* 需要搜索字符串中的特定字符 & 
* 字符串处理，分割字符字符串到 command 结构中
* 链表初始化后怎么释放申请的内存？


## 3. Shell Pipe

### Question

对简单情形 `mysh >> who | sort | cat`而言在
`fur (cur_segment = command->root; cur_segment != NULL; cur_segment->next)`
中`cur`依次遍历 Link list时
* cur 分别指向 who 和 sort 时如何区分二者的 in_fd

* 不在child 和 parent 中加入 `close` 语句，parent 会出现 block

## 4. Signal

### 目标

实现`Ctrl C`中断`mysh`创建的子进程，但不结束自身

实现`Ctrl Z`将 `mysh` 创建的子进程挂起，但不将自身挂起

### 理解

使用系统调用 `signal`

* `Ctrl C` 产生 `SIGINT`,默认动作是使进程结束
* `Ctrl Z` 产生 `SIGTSTP`,默认动作是使进程停止
* `SIG_DFL` 表示对信号的响应取默认
* `SIG_IGN` 表示忽略捕获到的信号

parent process 和 child process 都会捕获到键盘输入的信号，但是各自对信号的响应不同。

所以要在child 中加入如下语句：

    signal(SIGINT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);

parent 中加入如下语句：

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

### bug fix

`Ctrl Z` 后会出现 parent process block 现象，原因是child process 捕获挂起信号后挂起，而parent 在wait 语句中等待child process 执行结束。

需要使用`watipid` 的 `WUNTRACED` option, 表示当child stop 时`waitpid` 即可以返回，而不是block。

参考 [man watipid](http://linux.die.net/man/2/waitpid)


## Job control

* fg 实现将挂起的进程调到前台继续执行
* bg 实现将挂起的进程在后台继续执行

两者都要向进程号发送`SIGCONT`信号

使用如下语句：

    kill(pid, SIGCONT);

在子进程中捕获该信号，并设置默认响应

    signal(SIGCONT, SIG_DFL);

## 终端颜色

可以同过设置printf 打印出彩色的提示，从而修饰shell 解释的显示风格。

## Reference


