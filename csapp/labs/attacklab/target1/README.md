## 实验说明


| Phase | Program | Level | Method | unction | Points |
| ----- | ------- | ----- | ------ | ------- | ------ |
| 1     | ctarget | 1     | CI     | touch1  | 10     |
| 2     | ctarget | 2     | CI     | touch2  | 25     |
| 3     | ctarget | 3     | CI     | touch3  | 25     |
| 4     | rtarget | 2     | ROP    | touch2  | 35     |
| 5     | rtarget | 3     | ROP    | touch3  | 5      |

两种攻击方式：

- CI: Code injection
- ROP: Return-oriented programming


## 文件说明

| 实验     | 文件         | 说明                                          |
| -------- | ------------ | --------------------------------------------- |
| 通用文件 | ctarget      | 进行 Code Injection 实验的二进制程序          |
|          | rtarget      | 进行 ROP 实验的二进制程序                     |
|          | hex2raw      | 将用户输入的注入代码转成主机字节序            |
| phase1   | phase1.md    | 题解说明                                      |
|          | exploit1.txt | 注入的字节字符串                              |
|          | raw1.txt     | 通过 hex2raw 处理后的符合主机字节序的注入内容 |
| phase2   | phase2.md    | 题解说明                                      |
|          | exploit2.txt | 注入的字节字符串                              |
|          | raw2.txt     | 通过 hex2raw 处理后的符合主机字节序的注入内容 |
|          | exploit2.s   | 注入的汇编代码源文件                          |
|          | exploit2.o   | 通过 gcc 生成的目标文件                       |
|          | exploit2.d   | 通过 objdump 生成的指令字节                   |



## 参考

- [《深入理解计算机系统/CSAPP》Attack Lab](https://zhuanlan.zhihu.com/p/57771748)
