This is an x86-64 bomb for self-study students. 


# 二进制炸弹

## 介绍

输入六段内容，来拆解炸弹。当输入错误时，炸弹就会爆炸！

这里补充下几个作为参数的寄存器
- #1 `%rdi`
- #2 `%rsi`
- #3 `%rdx`
- #4 `%rcx`
- #5 `%r8`
- #6 `%r9`

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

## phase_3

打印汇编信息
```shell script
b phase_3
r decode2.txt
# 输入一个 hello3 来探探路
```

**func main**
```nasm
0x400e6a <main+202>     callq  0x40149e <read_line>
0x400e6f <main+207>     mov    %rax,%rdi ; 第1个参数为用户输入值
0x400e72 <main+210>     callq  0x400f43 <phase_3>
0x400e77 <main+215>     callq  0x4015c4 <phase_defused>
```

**func phase_3**
```nasm
0x400f43 <phase_3>      sub    $0x18,%rsp      ;1 申请 24 字节的栈空间
0x400f47 <phase_3+4>    lea    0xc(%rsp),%rcx  ;2 rsp+12 作为 sscanf 的 param 4
0x400f4c <phase_3+9>    lea    0x8(%rsp),%rdx  ;3 rsp+8  作为 sscanf 的 param 3
0x400f51 <phase_3+14>   mov    $0x4025cf,%esi  ;4 "%d %d" -> esi(执行完该语句，通过 x $esi可得到)
0x400f56 <phase_3+19>   mov    $0x0,%eax       ;5 返回值设置为 0
0x400f5b <phase_3+24>   callq  0x400bf0 <__isoc99_sscanf@plt> ;6 sscan(input_string, "%d %d", rsp+8, rsp+12)
0x400f60 <phase_3+29>   cmp    $0x1,%eax              ;7 确定是不是有两个变量(rsp+8, rsp+12)被填充了
0x400f63 <phase_3+32>   jg     0x400f6a <phase_3+39>  ;8.1 sscanf 执行 OK，跳转到 0x400f6a
0x400f65 <phase_3+34>   callq  0x40143a <explode_bomb>;8.2 否则引爆炸弹 BOOM!
0x400f6a <phase_3+39>   cmpl   $0x7,0x8(%rsp)         ;9 比较 rsp+8 和 7 的关系
0x400f6f <phase_3+44>   ja     0x400fad <phase_3+106> ;10.1 (rsp+8) > 7，跳转到 0x400fad, 经查，对应BOOM!! （`ja` 表示无符号的大于）
0x400f71 <phase_3+46>   mov    0x8(%rsp),%eax         ;10.2 (rsp+8) <=7，则 rax <- rsp+8【rsp+8是小于等于7的数】
0x400f75 <phase_3+50>   jmpq   *0x402470(,%rax,8)     ;11 跳转到 (0x400f7c + 8*rax)  (jmpq * 表示间接跳转，经打印 `p/x *0x402470`=0x400f7c)
0x400f7c <phase_3+57>   mov    $0xcf,%eax             ;12 如果 rsp+8==0, 则跳转到这里， eax <- 0xcf=207
0x400f81 <phase_3+62>   jmp    0x400fbe <phase_3+123> ;13 判断 eax 和 rsp+12 是否相等，不等则爆炸！
0x400f83 <phase_3+64>   mov    $0x2c3,%eax            ;14 eax <- 0x2c3
0x400f88 <phase_3+69>   jmp    0x400fbe <phase_3+123> ;15 eax === rsp+12 ?
0x400f8a <phase_3+71>   mov    $0x100,%eax            ;16 0x199 <- eax
0x400f8f <phase_3+76>   jmp    0x400fbe <phase_3+123> ;17 eax === rsp+12 ?
0x400f91 <phase_3+78>   mov    $0x185,%eax            ; eax=0x185
0x400f96 <phase_3+83>   jmp    0x400fbe <phase_3+123> ;
0x400f98 <phase_3+85>   mov    $0xce,%eax             ; eax=0xce
0x400f9d <phase_3+90>   jmp    0x400fbe <phase_3+123>                                            
0x400f9f <phase_3+92>   mov    $0x2aa,%eax                                                       
0x400fa4 <phase_3+97>   jmp    0x400fbe <phase_3+123>                                            
0x400fa6 <phase_3+99>   mov    $0x147,%eax                                                       
0x400fab <phase_3+104>  jmp    0x400fbe <phase_3+123>                                            
0x400fad <phase_3+106>  callq  0x40143a <explode_bomb> ; BOOM!
0x400fb2 <phase_3+111>  mov    $0x0,%eax               ; eax=0
0x400fb7 <phase_3+116>  jmp    0x400fbe <phase_3+123>  ;
0x400fb9 <phase_3+118>  mov    $0x137,%eax             ;
0x400fbe <phase_3+123>  cmp    0xc(%rsp),%eax         ; 比较 rsp+12 和 eax 关系
0x400fc2 <phase_3+127>  je     0x400fc9 <phase_3+134> ; rsp+12 == eax 顺利结束
0x400fc4 <phase_3+129>  callq  0x40143a <explode_bomb>; rsp+12 != eax，爆炸！ BOOM
0x400fc9 <phase_3+134>  add    $0x18,%rsp             ; 释放栈空间
0x400fcd <phase_3+138>  retq  
```

- 根据 0x400f56 `;6` 可以获得信息：用户输入的格式是按照 "%d %d" 的方式来的，并且输入的第一个值是 `rsp+8`，第二个值是 `rsp+12`。
- 根据 0x400f71 `;11` 我们可以知道第一个输入值(即rsp+8)必须是小于等于7的，不然就会爆炸！ 
- 其中 0x400f75 `;11` 是一个间接跳转，其跳转的地址是 *(0x400f7c + 8x第一个参数)
  > 我们可以通过 `p/x address` 指令来打印间接跳转的地址
  > - `p/x *(0x402470+8*0) = 0x400f7c`
  > - `p/x *(0x402470+8*1) = 0x400fb9`
  > - `p/x *(0x402470+8*2) = 0x400f83`
  > - `p/x *(0x402470+8*3) = 0x400f8a`
  > - `p/x *(0x402470+8*4) = 0x400f91`
  > - `p/x *(0x402470+8*5) = 0x400f98`
  > - `p/x *(0x402470+8*6) = 0x400f9f`
  > - `p/x *(0x402470+8*7) = 0x400fa6`

> 我们后面可以得到 0x400fbe 处干的事情就是判断 eax 和第二个参数是否相等，相等则解除炸弹！

接下来分情况讨论，我们输入的是 "%d %d"，对应十进制
1. 第一个值是 0，则 0x400f75 跳转到 0x400f7c, 第二个值是 0xcf = 207
2. 第一个值是 1，则 0x400f75 跳转到 0x400fb9, 第二个值是 0x137 = 311
3. 第一个值是 2，则 0x400f75 跳转到 0x400f83, 第二个值是 0x2c3 = 707
4. 第一个值是 3，则 0x400f75 跳转到 0x400f8a, 第二个值是 0x100 = 256
5. 第一个值是 4，则 0x400f75 跳转到 0x400f91, 第二个值是 0x185 = 389
6. 第一个值是 5，则 0x400f75 跳转到 0x400f98, 第二个值是 0xce = 206
7. 第一个值是 6，则 0x400f75 跳转到 0x400f9f, 第二个值是 0x2aa = 682
8. 第一个值是 7，则 0x400f75 跳转到 0x400fa6, 第二个值是 0x147 = 327


## phase_4

```shell script
b main
b phase_4
r decode3.txt
```


**func main**
```nasm
0x400e86 <main+230>     callq  0x40149e <read_line>                                           
0x400e8b <main+235>     mov    %rax,%rdi                                                      
0x400e8e <main+238>     callq  0x40100c <phase_4>                                             
0x400e93 <main+243>     callq  0x4015c4 <phase_defused>  
```

随便输入一个字符串 "hello4"，进行 phase_4 功能的探测
```nasm
0x40100c <phase_4>      sub    $0x18,%rsp     ; 申请 24 字节的栈空间
0x401010 <phase_4+4>    lea    0xc(%rsp),%rcx ; rsp+12 作为 sscanf 的 param 4
0x401015 <phase_4+9>    lea    0x8(%rsp),%rdx ; rsp+8  作为 sscanf 的 param 3
0x40101a <phase_4+14>   mov    $0x4025cf,%esi ; 0x4025cf 作为 sccanf 的 param 2，即数据格式的定义，内容为 "%d %d"
0x40101f <phase_4+19>   mov    $0x0,%eax      ; 返回值设置为 0
0x401024 <phase_4+24>   callq  0x400bf0 <__isoc99_sscanf@plt> ; 调用 sscanf
0x401029 <phase_4+29>   cmp    $0x2,%eax      ; 看看 sscanf 是不是成功执行了，输入了 "%d %d"
0x40102c <phase_4+32>   jne    0x401035 <phase_4+41> ; sscanf 没有按预期执行，BOOM!
0x40102e <phase_4+34>   cmpl   $0xe,0x8(%rsp)        ; 比较 rsp+8(第一个输入值) 和 14 大小
0x401033 <phase_4+39>   jbe    0x40103a <phase_4+46> ; rsp+8 <= 14，跳转到 0x40103a，不然就爆炸！
0x401035 <phase_4+41>   callq  0x40143a <explode_bomb> ; BOOM
0x40103a <phase_4+46>   mov    $0xe,%edx        ; param3 = 4
0x40103f <phase_4+51>   mov    $0x0,%esi        ; param2 = 0
0x401044 <phase_4+56>   mov    0x8(%rsp),%edi   ; param1 = 8
0x401048 <phase_4+60>   callq  0x400fce <func4> ; func4(8, 0, 4)
0x40104d <phase_4+65>   test   %eax,%eax        ; 看返回值是不是 = 0
0x40104f <phase_4+67>   jne    0x401058 <phase_4+76>  ; func4(8, 0, 4) !=2, BOOM!
0x401051 <phase_4+69>   cmpl   $0x0,0xc(%rsp)         ; rsp+12(第二个输入值) 和 0 比较
0x401056 <phase_4+74>   je     0x40105d <phase_4+81>  ; 第二个输入值 == 0，则没问题
0x401058 <phase_4+76>   callq  0x40143a <explode_bomb>; rsp+12 != 0, BOOM!
0x40105d <phase_4+81>   add    $0x18,%rsp             ; 释放栈空间
0x401061 <phase_4+85>   retq 
```

查看立即数对应的字符串可以用下述指令
```shell script
(gdb) x/s 0x4025cf
0x4025cf:       "%d %d"
(gdb) p/c "%d %d"
$3 = {37 '%', 100 'd', 32 ' ', 37 '%', 100 'd', 0 '\000'}
```

根据以下关键的两行指令，可以得到 rsp+8 和 rsp+12 的含义分别是输入的 第一个参数 和 第二个参数
```nasm
0x401010 <phase_4+4>    lea    0xc(%rsp),%rcx ; rsp+12 作为 sscanf 的 param 4
0x401015 <phase_4+9>    lea    0x8(%rsp),%rdx ; rsp+8  作为 sscanf 的 param 3
0x40101a <phase_4+14>   mov    $0x4025cf,%esi ; 0x4025cf 作为 sccanf 的 param 2，即数据格式的定义，内容为 "%d %d"
...
0x401024 <phase_4+24>   callq  0x400bf0 <__isoc99_sscanf@plt> ; 调用 sscanf
...
```

**接下来确定输入的第一个值**
```nasm
0x40102e <phase_4+34>   cmpl   $0xe,0x8(%rsp)        ; 比较 rsp+8(第一个输入值) 和 14 大小
0x401033 <phase_4+39>   jbe    0x40103a <phase_4+46> ; rsp+8 <= 14，跳转到 0x40103a，不然就爆炸！
0x401035 <phase_4+41>   callq  0x40143a <explode_bomb> ; BOOM
0x40103a <phase_4+46>   mov    $0xe,%edx        ; param3 = 14
0x40103f <phase_4+51>   mov    $0x0,%esi        ; param2 = 0
0x401044 <phase_4+56>   mov    0x8(%rsp),%edi   ; param1 = rsp+8
0x401048 <phase_4+60>   callq  0x400fce <func4> ; func4(rsp+8, 0, 14)
0x40104d <phase_4+65>   test   %eax,%eax        ; 看返回值是不是 = 0
```
得到，两个重要信息
1. 第一个输入值不大于 14
2. func4(input1, 0, 14) 返回值等于 0

func func4(input,i,j)  rdi:input, rsi:i, rdx:j
```nasm
0x400fce <func4>        sub    $0x8,%rsp
0x400fd2 <func4+4>      mov    %edx,%eax
0x400fd4 <func4+6>      sub    %esi,%eax  ; eax = j-i
0x400fd6 <func4+8>      mov    %eax,%ecx
0x400fd8 <func4+10>     shr    $0x1f,%ecx ;     (逻辑右移 31 位，则只剩下符号位 注：shr逻辑右移，sar算术右移)
0x400fdb <func4+13>     add    %ecx,%eax  ; 以上三行在判断 eax 的符号
0x400fdd <func4+15>     sar    %eax       ; eax /= 2
0x400fdf <func4+17>     lea    (%rax,%rsi,1),%ecx  ; val = eax + i = (j-i)/2 + i = (i+j)/2
0x400fe2 <func4+20>     cmp    %edi,%ecx           ; 比较输入和 val
0x400fe4 <func4+22>     jle    0x400ff2 <func4+36> ; 如果输入小于等于 val，则跳转
0x400fe6 <func4+24>     lea    -0x1(%rcx),%edx     ;
0x400fe9 <func4+27>     callq  0x400fce <func4>    ; 否则继续执行 func4，第三个参数变为 val-1
0x400fee <func4+32>     add    %eax,%eax
0x400ff0 <func4+34>     jmp    0x401007 <func4+57> ; return 2*func4(n, i, val-1)
0x400ff2 <func4+36>     mov    $0x0,%eax             ; eax = 0
0x400ff7 <func4+41>     cmp    %edi,%ecx
0x400ff9 <func4+43>     jge    0x401007 <func4+57>   ; 如果输入大于 val, 则 return
0x400ffb <func4+45>     lea    0x1(%rcx),%esi
0x400ffe <func4+48>     callq  0x400fce <func4>      ; 否则递归执行 func4，第二个参数变为 val+1
0x401003 <func4+53>     lea    0x1(%rax,%rax,1),%eax ; rax = 2*func(n, val+1, j)
0x401007 <func4+57>     add    $0x8,%rsp
0x40100b <func4+61>     retq
```

我们假设函数的原型为 `func4(int n, int i, int j)`，
汇编开头的几行，实际上是在计算 `(i+j)/2`，其实就是二分法求中值。之后进行了判断，如果输入值小于 val，则

```c
int func4(int n, int i, int j) {
    int val = (j + i) / 2;
    if (val <= n) {
        if (val >= n) return 0;
        else return 2 * func4(n, val+1, j) + 1;
    } else {
        return 2 * func4(n, i, val-1);
    }
}
```

这段代码的作用类似二分搜索，但是目标值只能向小的半段搜索，否则 `return 2 * func4(n, val+1, j) + 1`; 会返回非零的值。我们分析这个函数的取值可以得知满足条件的数有 0, 1, 3, 7

**我们可以确定第二个输入是 0**
```nasm
0x401051 <phase_4+69>   cmpl   $0x0,0xc(%rsp)         ; rsp+12(第二个输入值) 和 0 比较
0x401056 <phase_4+74>   je     0x40105d <phase_4+81>  ; 第二个输入值 == 0，则没问题
0x401058 <phase_4+76>   callq  0x40143a <explode_bomb>; rsp+12 != 0, BOOM!
```

所以满足条件的值有

```text
0 0
1 0
3 0
7 0
```

## phase_5

打断点调试
```shell script
gdb bomb
layout asm
b main
b phase_5
r decode4.txt # run with file, and fill prev 4 phases
c # contine

# input a string
si # 单步执行汇编代码
```

**func phase_5**
```nasm
0x401062 <phase_5>      push   %rbx                  
0x401063 <phase_5+1>    sub    $0x20,%rsp            ; 申请 32 字节栈空间
0x401067 <phase_5+5>    mov    %rdi,%rbx             
0x40106a <phase_5+8>    mov    %fs:0x28,%rax         ; 栈保护
0x401073 <phase_5+17>   mov    %rax,0x18(%rsp)       ;
0x401078 <phase_5+22>   xor    %eax,%eax             ; set rax=0
0x40107a <phase_5+24>   callq  0x40131b <string_length>
0x40107f <phase_5+29>   cmp    $0x6,%ea
0x401082 <phase_5+32>   je     0x4010d2 <phase_5+112>            
0x401084 <phase_5+34>   callq  0x40143a <explode_bomb>  ; 如果输入的长度不等于6，则爆炸
0x401089 <phase_5+39>   jmp    0x4010d2 <phase_5+112>            
0x40108b <phase_5+41>   movzbl (%rbx,%rax,1),%ecx       ; ecx = rdi
0x40108f <phase_5+45>   mov    %cl,(%rsp)
0x401092 <phase_5+48>   mov    (%rsp),%rdx                       
0x401096 <phase_5+52>   and    $0xf,%edx                         
0x401099 <phase_5+55>   movzbl 0x4024b0(%rdx),%edx               
0x4010a0 <phase_5+62>   mov    %dl,0x10(%rsp,%rax,1)             
0x4010a4 <phase_5+66>   add    $0x1,%rax                         
0x4010a8 <phase_5+70>   cmp    $0x6,%rax                         
0x4010ac <phase_5+74>   jne    0x40108b <phase_5+41>             
0x4010ae <phase_5+76>   movb   $0x0,0x16(%rsp)                   
0x4010b3 <phase_5+81>   mov    $0x40245e,%esi                    
0x4010b8 <phase_5+86>   lea    0x10(%rsp),%rdi                   
0x4010bd <phase_5+91>   callq  0x401338 <strings_not_equal>      
0x4010c2 <phase_5+96>   test   %eax,%eax                         
0x4010c4 <phase_5+98>   je     0x4010d9 <phase_5+119>            
0x4010c6 <phase_5+100>  callq  0x40143a <explode_bomb>           
0x4010cb <phase_5+105>  nopl   0x0(%rax,%rax,1)                  
0x4010d0 <phase_5+110>  jmp    0x4010d9 <phase_5+119>            
0x4010d2 <phase_5+112>  mov    $0x0,%eax              ; rax=0
0x4010d7 <phase_5+117>  jmp    0x40108b <phase_5+41>             
0x4010d9 <phase_5+119>  mov    0x18(%rsp),%rax
0x4010de <phase_5+124>  xor    %fs:0x28,%rax                     
0x4010e7 <phase_5+133>  je     0x4010ee <phase_5+140>            
0x4010e9 <phase_5+135>  callq  0x400b30 <__stack_chk_fail@plt>   
0x4010ee <phase_5+140>  add    $0x20,%rsp                        
0x4010f2 <phase_5+144>  pop    %rbx                              
0x4010f3 <phase_5+145>  retq
```
