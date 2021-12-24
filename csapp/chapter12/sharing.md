线程间共享变量。可共享虚拟内存，不可共享寄存器。

```shell script
➜  chapter12 git:(main) ✗ gcc -pthread sharing.c csapp.c
➜  chapter12 git:(main) ✗ ./a.out 
[0]: Hello from foo (cnt=1)
[1]: Hello from bar (cnt=2)
```


另外，在之前 csapp 的原版本基础上进行了部分修改。在转整形类型时使用了 `intptr_t` 来表明 int 类型指针的长度。
这个也是书中提到了，类型指针的长度不一定和类型相等。也就是说 int 和 `intptr_t` 不一定相等。指针可能会保存其他额外的信息。

> csapp 3rd 中文本。p610
>
> 9.11.4 假设指针和他们指向的对象是相同大小的。这个假设不一定成立，因为涉及到内存分配，指针对象中可能存在”已分配块的边界标记脚部“。这个”脚部“是为了维护
> 动态内存分配时的”隐式空闲链表“而存在的。<书中 p592>。简单的理解就是为了提高内存使用率，减少碎片等的一种具体分配方案实现。

参考：

https://stackoverflow.com/questions/21323628/warning-cast-to-from-pointer-from-to-integer-of-different-size
