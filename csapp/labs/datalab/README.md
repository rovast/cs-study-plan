# 环境准备

如果是 64bits 的机器，需要安装下面的库，否则 `make btest` 会报错 `bits/libc-header-start.h: No such file or directory`
```shell script
sudo apt-get install gcc-multilib
```

# 目标要求

在指定的操作符和操作个数下，完成函数。具体的操作数和操作符在函数中皆有定义。

```c
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB) LSB(Least Significant Bit)最低有效位 MSB(Most Significant Bit)最高有效位
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 * 
 * 从 x 里取出第 n 个字节的值，下标是 0~3(最多4个字节，32位)
 */
int getByte(int x, int n)
{
  // 1. 右移 8n 位，得到需要获取字节的最高位
  int y = x >> (n << 3);
  // printf("%x >> %d = %x\n", x, n << 3, y);
  // printf("%x \& 0xff = %x\n", y, y & 0xff);

  // 2. 只取最低两位
  return y & 0xff;
}
```

# 指令说明

```shell script
# 检查操作合不合法，有没有使用不允许的操作符
./dlc -e bits.c

dlc:bits.c:162:bitAnd: 4 operators
dlc:bits.c:182:getByte: 3 operators
dlc:bits.c:206:logicalShift: 6 operators
dlc:bits.c:241:bitCount: 36 operators
dlc:bits.c:267:bang: 12 operators
dlc:bits.c:280:tmin: 1 operators
dlc:bits.c:305:fitsBits: 7 operators
dlc:bits.c:321:divpwr2: 7 operators
dlc:bits.c:332:negate: 2 operators
dlc:bits.c:347:isPositive: 6 operators
dlc:bits.c:363:isLessOrEqual: 15 operators
dlc:bits.c:406:ilog2: 48 operators
dlc:bits.c:426:float_neg: 6 operators
dlc:bits.c:477:float_i2f: 28 operators
dlc:bits.c:501:float_twice: 16 operators

# 检查结果是否正确
make btest && ./btest

Score   Rating  Errors  Function
 1      1       0       bitAnd
 2      2       0       getByte
 3      3       0       logicalShift
 4      4       0       bitCount
 4      4       0       bang
 1      1       0       tmin
 2      2       0       fitsBits
 2      2       0       divpwr2
 2      2       0       negate
 3      3       0       isPositive
 3      3       0       isLessOrEqual
 4      4       0       ilog2
 2      2       0       float_neg
 4      4       0       float_i2f
 4      4       0       float_twice
Total points: 41/41
```
