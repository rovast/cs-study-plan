# IEEE 浮点数

CreatedAt: September 30, 2021 3:38 PM
Tags: CSAPP

$$Value = sign \times exponent \times fraction$$

也就是浮点数的实际值，等于符号位（sign bit）乘以指数偏移值(exponent bias)再乘以分数值(fraction)。

$$V=(-1)^s \times 2^E \times M$$

- `s` 符号位 Sign
- `E` 阶码 Exponent
- `M` 尾数 Significand

![Untitled](assets/2-1.png)

# 32位机器为例

单精度浮点数

$$\underbrace{ b_{31}}_\text{s 符号位字段 1bit}
\underbrace{ b_{30} b_{29} \dots b_{24} b_{23} }_\text{ e 阶码字段8bits} 
\underbrace{ b_{22} b_{21} \dots b_1 b_0 }_\text{f 小数字段 23bits}$$

# 四种表示方式（或者叫四种情况）

[Untitled](https://www.notion.so/76b312b7757142af961c4f62a9123a48)

其中

- Bias 是个固定值 $Bias = 2^{k-1} - 1$
- 小写表达的字母，如 $s、e、f$ 表示二进制的具体字段。适用于具体存储时（二进制）的表示。
- 大写表达的字母，如 $V、E、M$ 表示的是具体十进制数值时的计算。适用于公式 $V=(-1)^s \times 2^E \times M$
- 我们还需要看到，在四种不同表示方式的情况下，$E、M$ 的具体计算方式有差异。经过这样的设置之后，我们可以很平滑的在非规格化和规格化之间过渡。
    
    ![Untitled](assets/2-2.png)
    

# 整数转浮点数表示

## 步骤

1、转化为 IEEE 的表达方式 $V=(-1)^s \times 2^E \times M$

2、根据第一步的公式，可以得到 $s、E、M$ 的值

3、根据 $E、M$可以得到 $e、f$ 

非规格化表示的几个关系

$$\begin{align}
Bias &= 2^{k-1}-1 \\
由 E &= e-Bias, &得到 e&=E+Bias \\
由 M &=1+f, &得到 f&=M-1
\end{align}$$

## 示例

```html
整数 3510593 的十六进制表示为 0x00359141
浮点数 3510593.0 十六进制表示 0x4A564504
```

推导过程（以 32 位机器表示，其中 $s=1,k(阶码字段)=8bits,n(小数字段)=23bits$

1. 0x00359141 的二进制表示为
    
    $$00359141_{16}=
    \underbrace{0011}_3\space
    \underbrace{0101}_5\space
    \underbrace{1001}_9\space
    \underbrace{0001}_1\space
    \underbrace{0100}_4\space
    \underbrace{0001}_1$$
    
    转化为 $V=(-1)^s \times 2^E \times M$的表示，得到
    
    $$\begin{align}
    00359141_{16} &= -1^0 \times 1.1\space0101\space1001\space0001\space0100\space0001\times2^{21} \\
    得到 \\
    s &=0,\\
    E &=21,\\
    M &=1.1\space0101\space1001\space0001\space0100\space0001
    \end{align}$$
    
2. 根据公式(1)，(2)，(3) 我们可以得到
    
    $$\begin{align}
    Bias &= 2^{8-1}-1=128-1=127 &偏置量 \\
    e &= E + Bias = 21+127=148=1001\space0100_2 &阶码字段(8位) \\
    f&=M-1=0.1\space0101\space1001\space0001\space0100\space0001_2 & 小数字段(23位)
    \end{align}$$
    
3. 可以得到最后的二进制表达为
    
    $$\underbrace{0}_s
    \underbrace{1001\space0100}_{e 共8位}
    \underbrace{
    {1010}\space{1100}\space
    {1000}\space{1010}\space
    {0000}\space{100}
    }_{f 共23位}$$
    
    得到整个 32 位表示为 `0x4A564504`
    
    $$\underbrace{0100}_4\space
    \underbrace{1010}_A\space
    \underbrace{0101}_5\space
    \underbrace{0110}_6\space
    \underbrace{0100}_4\space
    \underbrace{0101}_5\space
    \underbrace{0000}_0\space
    \underbrace{0100}_4$$
