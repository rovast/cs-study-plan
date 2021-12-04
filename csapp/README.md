# CSAPP 第一部分总结

CreatedAt: November 14, 2021 4:32 PM

学习时间：2021.09.20 至 2021.11.14

学完第一部分后，对计算机底层知识有了一个新的补充。最大的感触就是对编写出来的代码有了一个新的认知，同时对代码性能优化有了方向。

如果只能拎出来一个点来讲的话，知道书写出高性能代码。

# 编写高性能代码

从以下几个方向入手

- 选择格式的数据结构和算法（正好在 cs plan 的第二阶段会涉及）
- 低级的优化策略，包括：指令级别、数据结构设计级别、编写告诉缓存友好的代码
- 【流水线】书写适合指令流水线的代码。使用功能性代码，而不是跳转类代码，这样可以充分使指令能够被预测。举例说明。
    
    ```c
    if(a == 0) {
    	return b;
    }
    
    return c;
    
    // replace
    a ? b : c;
    ```
    
- 【指令并发】书写适合指令并发的代码。比如，循环展开、多累计变量、重新结合。其底层原理是为了贴近现代CPU的设计，其内部有多个指令单元和运算单元。
    - 循环展开
    - 多累计变量
    - 重新结合
- 【字节对齐】对定义 struct 时有很高的指导作用。结构体的各成员分布的顺序是讲究的，可以有效节省空间。
- 【减少内存访问】尽量减少内存引用，因为每次的内存引用需要从内存总线传递到系统总线，这个访问是存在大量的时间成本的。
- 内存的读写分离，不要相互依赖。因为在内存的底层层次，其读写和分开处理，在没有依赖的情况下，可以并行处理。
- 
- 减少函数调用。其实函数的嵌套本质上也是使用了 push 指令，把函数的地址压入 栈 rsp 中。在函数结束时需要从 (rsp) 中读出函数地址，本质上也是触发了一次内存的读取。
- 【提高高速缓存命中率】现在 CPU 架构中一般设计了多级的高速缓存。我们需要利用局部性原理（时间局部性、空间局部性）来书写贴近高速缓存的代码。这里面会涉及到一些重要的概念
    - S 高速缓存器组
    - E 每个组有多少行缓存块
    - B 每个缓存块的大小
    - m 地址位，从左到右分为三段
        - t 标记位，当确定了组、行的信息后，根据t标记位来确定缓存是否命中
        - s，用来识别组信息。一般用地址为的中间部分来表示。这样使得连续地址的信息能够均匀分布在整个高速缓存里
        - b，块偏移信息。用来标记访问块的哪一部分。（因为缓存间的数据传递是以 块 为基本传输单元。所以每次都是加载了B 大小的数据，而实际上代码访问可能只使用了其中的一小块。之所以加载一大块，是为了尽量减少传输次数）

# 其他的基础概念

1. **信息的表示。**主要是知道了信息的二进制表达，这对后续查看汇编指令很重要。如一些基本概念，尤其是使用数学表达式的方式来进行信息表示，还能够进行推导。真的是即严谨，又深刻！
    1. 补码：补码的英文是 Two's complement。这表示，这个数是由两个部分来进行表示的。其最高位就是负权重。二进制表示（Binary）到补码（T）值运算如下：
        
        $$B2T_w(\vec x) \doteq  - x_{w-1}2^{w-1}+\sum_{i=0}^{w-2} x_i2^i$$
        
    2. 逻辑移位：直接移就完事儿了。
    3. 算术移位：需要考虑，进行最高位保留。如果是负数，需要把最高位的 1 进行保留。
2. 程序的机器级表示。进行汇编代码的了解阅读，对代码的执行底层有了一个大概的了解。也知道了一些概念
    1. 缓存溢出安全。即代码的边界没考虑好，导致后续的数据覆盖了原来的栈保护空间，导致了不可预料的问题。
    2. 更有甚者，重写返回地址，来执行另一个代码片段
    3. 一些寄存器相关内容。尤其是通过二进制炸弹，对一些标号的寄存器印象更加深刻。比如 rax 用来存放返回值、rdi 第一个参数、rsi 第二个参数。
3. 处理器体系结构。着重进行了流水线的设计进化。
    1. SEQ 进行了指令编码的认识，设计了硬件
    2. SEQ+ 将指令获取挪到开始，可以进行指令预测
    3. PIPE- 加入了流水线寄存器
    4. PIPE 增加异常处理等、流水线冒险等
4. 优化程序性能
    1. 消除循环的低效率。增加循环展开、重新结合等
    2. 减少过程调用
    3. 消除不必要的内存引用
5. 存储器的层次结构
    1. 局部性原理
    2. S E B 等概念。各个高速缓存之间使用块作为传输单元。写代码时，可以利用缓存填充的策略，来对程序进行缓存分布调整，从而提高命中率。
        1. 抖动冲突