# 实现自己的shell

这是我在国立交通大学交换期间修选OS课程实现的课程项目,代码量300行左右

目标：实现一个简单的shell解释器，要求支持如下功能

1. 解释执行命令
2. 内建命令`cd` `exit`
3. pipe 管道
4. `fg` 前台执行命令
5. `bg` 后台执行命令
6. 彩色提示符
7. Ctrl -Z Ctrl -C 信号处理

详细的实现细节见文档：[从零构建自己的mini shell](./build_mysh.md)

## 架构

环境：ubuntu 14.4

编译器：gcc

main 函数和功能函数放在源文件 `sh.c` 

执行 `make` 可生成 `mysh` 可执行文件

## 功能要求与参考文档

[HW1 process & IPC](./SPEC.md)
