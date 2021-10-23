This is an x86-64 bomb for self-study students. 


# 二进制炸弹

## 介绍

输入六段内容，来拆解炸弹。当输入错误时，炸弹就会爆炸！


## phase_1

使用 GDB 来进行调试

```shell script
b main # main 函数入口打断点
```


## phase_2

### func main

```nasm
0x400e4e <main+174>     callq  0x40149e <read_line>
0x400e53 <main+179>     mov    %rax,%rdi
0x400e56 <main+182>     callq  0x400efc <phase_2>
0x400e5b <main+187>     callq  0x4015c4 <phase_defused>  
```

用户输入值，作为 `<phase_2>` 第一个参数，经过打印发现 %rdi 和 %rdx 都是用户输入的字符串。
```shell
(gdb) ni
(gdb) x $rdi
0x6037d0 <input_strings+80>:    "hello"
(gdb) x $rsi
0x6037d0 <input_strings+80>:    "hello"
```

### func phase_2

```nasm
0x400efc <phase_2>      push   %rbp       ;1 rbp 和 rbx 属于 callee saver 寄存器，这里 push 是为了保存现场，在函数结束时 pop 来恢复现场
0x400efd <phase_2+1>    push   %rbx
0x400efe <phase_2+2>    sub    $0x28,%rsp ;2 申请 40 字节的栈空间
0x400f02 <phase_2+6>    mov    %rsp,%rsi  ;3 把栈指针作为第二个参数传入 read_six_numbers，通过 `x/s $rdi` 打印出 %rdi 至就是 phase_2 用户输入值
0x400f05 <phase_2+9>    callq  0x40145c <read_six_numbers> ;4 稍后再议
0x400f0a <phase_2+14>   cmpl   $0x1,(%rsp)             ;6 栈顶元素是不是立即数 1
0x400f0e <phase_2+18>   je     0x400f30 <phase_2+52>   ;6.1 继续执行，跳转到 0x400f30
0x400f10 <phase_2+20>   callq  0x40143a <explode_bomb> ;6.2 栈顶不是 1，BOOM
0x400f15 <phase_2+25>   jmp    0x400f30 <phase_2+52>
0x400f17 <phase_2+27>   mov    -0x4(%rbx),%eax         ;10 (%rbx-4) 表示上一个元素
0x400f1a <phase_2+30>   add    %eax,%eax               ;11 %eax*2，其实这个 %eax 充当了临时变量的作用
0x400f1c <phase_2+32>   cmp    %eax,(%rbx)             ;12 根据 ;10~;12 三行可以得到，这里判断当前元素(%rbx)是不是上一个元素的两倍
0x400f1e <phase_2+34>   je     0x400f25 <phase_2+41>   ;13.1 当前元素 == 前一个元素x2，跳转到 0x400f25
0x400f20 <phase_2+36>   callq  0x40143a <explode_bomb> ;13.2 不满足当前元素是上一个元素两倍的要求，BOOM 
0x400f25 <phase_2+41>   add    $0x4,%rbx               ;14 指向下一个元素
0x400f29 <phase_2+45>   cmp    %rbp,%rbx               ;15 判断边界情况，因为满足的情况下，直接跳到 0x400f3c <phase_2+64> 了，那里干的事情是函数退出的现场恢复动作
0x400f2c <phase_2+48>   jne    0x400f17 <phase_2+27>   ;16.1 这里开始循环了，结合 ;9，发现这是个 guarded do 结构的循环
0x400f2e <phase_2+50>   jmp    0x400f3c <phase_2+64>   ;16.2 结束
0x400f30 <phase_2+52>   lea    0x4(%rsp),%rbx        ;7 栈 +4
0x400f35 <phase_2+57>   lea    0x18(%rsp),%rbp       ;8 栈 + 24，根据后文判断，这里 +24 表示栈的边界，即：6个元素，每个元素 4 字节
0x400f3a <phase_2+62>   jmp    0x400f17 <phase_2+27> ;9 跳转到 0x400f17，开始循环了就
0x400f3c <phase_2+64>   add    $0x28,%rsp ; 释放栈
0x400f40 <phase_2+68>   pop    %rbx       ; 恢复 callsee saved register
0x400f41 <phase_2+69>   pop    %rbp       ; 恢复 callsee saved register
0x400f42 <phase_2+70>   retq   
```

初步判断下来，就是栈指针作为参数传递到函数 `read_six_numbers` 里了，返回时变为携带了六个元素的数组，每个元素大小是 4字节。
然后从栈顶开始循环，判断下一个是不是上一个的 2倍，且栈顶元素是 1。

我们可以在 `0x400f05 callq  0x40145c <read_six_numbers>` 处打印断点，
看到 `read_six_numbers` 的第一个参数是用户输入值（）第二个参数是栈指针，汇编代码有说明）

```shell script
gdb boom
layout asm   # 显示汇编代码
b * 0x400f05 # 打断点

r

# Welcome to my fiendish little bomb. You have 6 phases with
# which to blow yourself up. Have a nice day!
# 输入 Border relations with Canada have never been better.

# Phase 1 defused. How about the next one?
# 随便输入一个 hello

si # stepi 缩写，单步执行汇编，查看 <read_six_numbers> 汇编代码
x $rdi #1 参数 hello，即用户输入值
```

这里补充下几个作为参数的寄存器
- #1 `%rdi`
- #2 `%rsi`
- #3 `%rdx`
- #4 `%rcx`
- #5 `%r8`
- #6 `%r9`

### func read_six_numbers

```nasm
0x40145c <read_six_numbers>     sub    $0x18,%rsp      ;1 申请 24 字节的栈空间
0x401460 <read_six_numbers+4>   mov    %rsi,%rdx       ;2 函数 `read_six_numbers` 的第 2 个参数(栈指针)，变成 `__isoc99_sscanf` 函数的第 3 个参数【3】
0x401463 <read_six_numbers+7>   lea    0x4(%rsi),%rcx  ;3 下一个元素(rsi+4) 作为第 4 个参数【4】
0x401467 <read_six_numbers+11>  lea    0x14(%rsi),%rax ;4 rsi+20
0x40146b <read_six_numbers+15>  mov    %rax,0x8(%rsp)  ;5 (rsp)+8 = (rsi)+20【8】
0x401470 <read_six_numbers+20>  lea    0x10(%rsi),%rax ;6 rsi+16
0x401474 <read_six_numbers+24>  mov    %rax,(%rsp)     ;7 (rsp) = rsi+16【7】寄存器一共就能有6个作为参数，多出的用栈来存
0x401478 <read_six_numbers+28>  lea    0xc(%rsi),%r9   ;8 （rsi)+12 第6 个参数【6】
0x40147c <read_six_numbers+32>  lea    0x8(%rsi),%r8   ;9  (rsi)+8  第5个参数【5】
0x401480 <read_six_numbers+36>  mov    $0x4025c3,%esi  ;10 `__isoc99_sscanf` 的第二个参数，打印下 "%d %d %d %d %d %d"
0x401485 <read_six_numbers+41>  mov    $0x0,%eax       ;11 调用 __isoc99_sscanf 之前，把 rax 设置为 0
0x40148a <read_six_numbers+46>  callq  0x400bf0 <__isoc99_sscanf@plt> ;12 函数调用，具体函数参数前面用【n】标注了
0x40148f <read_six_numbers+51>  cmp    $0x5,%eax  ;13 看看返回值是不是 5
0x401492 <read_six_numbers+54>  jg     0x401499 <read_six_numbers+61>                            
0x401494 <read_six_numbers+56>  callq  0x40143a <explode_bomb>                                   
0x401499 <read_six_numbers+61>  add    $0x18,%rsp                                                
0x40149d <read_six_numbers+65>  retq  
```

`x 0x4025c3` 打印立即数 `0x4025c3` 对应的内存内容为 `"%d %d %d %d %d %d"`
```shell
(gdb) x 0x4025c3
0x4025c3:       "%d %d %d %d %d %d"
```

所以猜测函数 `sscanf` 干了啥 

```c
// @see https://www.tutorialspoint.com/c_standard_library/c_function_sscanf.htm
sscanf(input_string, "%d %d %d %d %d %d", rsp, rsp+4, rsp+8, rsp+12, rsp+16, rsp+20);
```

就是把用户的输入解码到栈里。在 `func phase_2` 我们知道 rsp 对应立即数 1，且下一位是上一位的 2 倍，共 6 位，且占用 4 字节(32bits)。所以有，答案是
```
1 2 4 8 16 32
```
