# HW1: boot xv6

如果使用 gdb 不能直接打断点，可在 `~/.gdbinit` 中设置下述指令即可：

```bash
set auto-load safe-path /
```

## Exercise: What is on the stack?

查看寄存器和堆栈的内容，对每一个非0的值进行解释。打印出来的部分，哪些是真正的栈？

```bash
>>> info registers
eax            0x0      0
ecx            0x0      0
edx            0x1f0    496
ebx            0x10094  65684
esp            0x7bdc   0x7bdc
ebp            0x7bf8   0x7bf8
esi            0x10094  65684
edi            0x0      0
eip            0x10000c 0x10000c
eflags         0x46     [ PF ZF ]
cs             0x8      8
ss             0x10     16
ds             0x10     16
es             0x10     16
fs             0x0      0
gs             0x0      0

>>> x/24x $esp
0x7bdc: 0x00007d8d      0x00000000      0x00000000      0x00000000
0x7bec: 0x00000000      0x00000000      0x00000000      0x00000000
0x7bfc: 0x00007c4d      0x8ec031fa      0x8ec08ed8      0xa864e4d0
0x7c0c: 0xb0fa7502      0xe464e6d1      0x7502a864      0xe6dfb0fa
0x7c1c: 0x16010f60      0x200f7c78      0xc88366c0      0xc0220f01
0x7c2c: 0x087c31ea      0x10b86600      0x8ed88e00      0x66d08ec0
```

我们得到从栈开始的地址 7c00 开始

```nasm
0x7bdc: 0x00007d8d # 执行完 entry 后的返回地址：return address after call *0x10018
0x7be0: 0x00000000
0x7be4: 0x00000000
0x7be8: 0x00000000
0x7bec: 0x00000000 # Callee saved EBX by bootmain
0x7bd0: 0x00000000 # Callee saved ESI by bootmain
0x7bd4: 0x00000000 # Callee saved EDI by bootmain
0x7bd8: 0x00000000 # EBP of bootasm frame, bootmain ESP initialized here
0x7bfc: 0x00007c4d # EIP of instruction after call to bootmain
0x7c00: 0x8ec031fa # x/i 0x7c00: cli   
```

- 最后一行  `0x7c00: 0x8ec031fa`, 压入的是 ebp 的值，其内容等于调用者的esp 地址
    
    ```bash
    00007d3b <bootmain>:
    {
        7d3b:	55                   	push   %ebp
        **7d3c:	89 e5                	mov    %esp,%ebp**
    ```
    

---

下面的问题会有所帮助：

1、**在 boot block（bootasm.S）开始处 0x7c00 设置断点，使用 si 进行单步调试，看看 bootasm.S 什么时候进行栈的初始化的（即：观察什么时候向 %esp 中写入值）。**

下面是 GDB 调试的截图：


![Untitled](https://user-images.githubusercontent.com/9459488/159193890-610e400f-56c8-4943-8284-6818cde1adab.png)


通过阅读 bootblock.asm，我们知道在进行栈初始化前进行了以下主要事宜

- 关闭中断 `cli`
- 数据段寄存器 DS, ES, SS 清零
- 启用 A20 物理地址线
- 从 16bits real mode 切换到 32bits 保护模式，加载全局描述符表，开启虚拟内存映射

---

- 初始化保护模式下的数据段寄存器值 ES, ES, SS 为 0x10； FS, GS 设置为 0
- 接下来就是设置栈指针 esp 了 `mov $0x7c00,%esp`

```bash
## xv6-public/bootblock.asm

.code32  # Tell assembler to generate 32-bit code now.
start32:
  # Set up the protected-mode data segment registers
  # .........

  # Set up the stack pointer and call into C.
  movl    $start, %esp
    7c43:	bc 00 7c 00 00       	mov    $0x7c00,%esp
  call    bootmain
    7c48:	e8 ee 00 00 00       	call   7d3b <bootmain>
```

当执行完 `mov    $0x7c00,%esp` 我们查看各寄存器的值：

```bash
(gdb) info registers
eax            0x0      0
ecx            0x0      0
edx            0x80     128
ebx            0x0      0
esp            0x7c00   0x7c00
ebp            0x0      0x0
esi            0x0      0
edi            0x0      0
eip            0x7c48   0x7c48
eflags         0x6      [ PF ]
cs             0x8      8
ss             0x10     16
ds             0x10     16
es             0x10     16
fs             0x0      0
gs             0x0      0
```

**2、单步调试执行完 bootmain，这时候栈里面是什么内容？**

在之前 gdb 调试中，或者结合 `botoblock.asm` 的 line 103 我们知道 bootmain 函数入口地址为 0x7d3b

```bash
b *0x7d3b
```

![Untitled](https://user-images.githubusercontent.com/9459488/159193886-7ff72eec-4cca-4f1a-9942-2b8c1366a004.png)

```bash
b *0x7cf2
c

### 查看寄存器内容
(gdb) info registers
eax            0x40     64
ecx            0x80     128
edx            0x1f0    496
ebx            0x1      1
esp            0x7ba8   0x7ba8
ebp            0x7bb0   0x7bb0
esi            0x1      1
edi            0x10000  65536
eip            0x7cf2   0x7cf2
eflags         0x46     [ PF ZF ]
cs             0x8      8
ss             0x10     16
ds             0x10     16
es             0x10     16
fs             0x0      0
gs             0x0      0
```

**3、在 bootblock.asm 中看看：bootmain 的第一条汇编指令在栈上面做了什么事情。**

```nasm
00007d3b <bootmain>:
{
    7d3b:	55                   	push   %ebp
    7d3c:	89 e5                	mov    %esp,%ebp
    7d3e:	57                   	push   %edi
    7d3f:	56                   	push   %esi
    7d40:	53                   	push   %ebx
    7d41:	83 ec 0c             	sub    $0xc,%esp
```

bootmain 对应的指令如上，第一条汇编指令将 ebp 入栈，并且把当前的 esp 值存入到 ebp 中。主要每个过程调用都遵守这样的约定，那么就可以形成一条可供溯源的调用链。

**4、继续调试，查找修改 %eip 为 0x1000c 是哪个调用。这个调用对栈做了什么？（提示：思考下这调用在 boot 启动顺序中想完成的事情，在 bootmain.c 中定位到。在 bootblock.asm 中找到对应的 bootmain 指令。这样会帮助你快速调试）。**

通过观察 bootmain.c 知道，bootmain 最后一条执行语句是 `entry()`。其作用是根据 elf 提供的入口信息，加载内核。

进一步在 bootblock.asm 中查找 entry 关键字，得到下面指令 line 322

```nasm
entry();
    7d87:	ff 15 18 00 01 00    	call   *0x10018
    7d8d:	eb d5                	jmp    7d64 <bootmain+0x29>
```

我们在 0x7d87 设置断点后，打印出 0x10018 处存放的值，知道其存放的是 0x10000c，即：kernel 的入口地址。

![Untitled](https://user-images.githubusercontent.com/9459488/159193889-2622074e-059a-418e-89ee-0a5a6f9a3d97.png)
