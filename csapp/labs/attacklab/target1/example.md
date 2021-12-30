使用 GCC 获取指令编码的字节

example.s，手写汇编源码

```nasm
pushq $0xabcdef  # push value onto stack
addq  $17, %rax
movl  %eax, %edx
```



example.o，使用 gcc 生成目标文件

```shell
gcc -c example.s
``




example.d，使用 objdump 生成反汇编代码

```shell
objdump -d example.o > exampld.d
```


得到

```

example.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	68 ef cd ab 00       	pushq  $0xabcdef
   5:	48 83 c0 11          	add    $0x11,%rax
   9:	89 c2                	mov    %eax,%edx

```

我们得到字节编码，可以直接通过 hex2raw 输入到 ctarget

```
68 ef cd ab 00
48 83 c0 11
89 c2
```
