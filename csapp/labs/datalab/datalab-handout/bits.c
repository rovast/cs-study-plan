/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully. 首先，认真阅读下面的东西
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES: 整数的编码规则
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style: 把 return 语句改成你的实现
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
    整数范围是 0~255，不允许使用大数如 0xffffffff
  2. Function arguments and local variables (no global variables).
    函数擦书和局部变量（不能使用全局变量）
  3. Unary integer operations ! ~
    整数一元运算符 !~
  4. Binary integer operations & ^ | + << >>
    二进制整数运算符 & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.
  有些问题进一步限制了可以使用的操作，每个 "Exprt" 可能由多个运算组成。每行不限制一个操作。

  You are expressly forbidden to: 不准用
  1. Use any control constructs such as if, do, while, for, switch, etc.
    不能用任何控制类语句，比如 if do while for switch 等等
  2. Define or use any macros.
    不能定义宏
  3. Define any additional functions in this file.
    不能定义额外的函数
  4. Call any functions.
    不能调用函数
  5. Use any other operations, such as &&, ||, -, or ?:
    不能好用其他的操作，比如 && || - ?
  6. Use any form of casting.
    不能用其他形式的 casting
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.
    不能用除了 int 之外的数据类型，比如 array, structs, unions
 
  You may assume that your machine: 你可以假定机器
  1. Uses 2s complement, 32-bit representations of integers.
    使用补码表示整形，且是 32位字长的机器
  2. Performs right shifts arithmetically.
    向右移位是算术右移
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.
    当移动超过一个字长时，结果是不可预测的

EXAMPLES OF ACCEPTABLE CODING STYLE: 示例
  /*
   * 我们看到下面的函数，仅仅用了移位和加法，便完成了函数
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES 浮点数的编码规则

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. 
浮点数的约束相对比较宽松一点。你可以使用循环语句或者条件语句，并且你还可以使用 int 和 unsigned。你可以使用任意大小的整数。

You are expressly forbidden to: 你不可以
  1. Define or use any macros. 定义宏
  2. Define any additional functions in this file. 定义额外函数
  3. Call any functions. 调用任何函数
  4. Use any form of casting. 任何形式的hack
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions. 不能使用除了 int 和 unsigned 之外的数据类型
  6. Use any floating point data types, operations, or constants. 使用浮点数的类型、操作或常量


NOTES: 说明
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions. 使用 dlc 编译器来检查你的解法对不对
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty. 每个函数的操作是被计数的，不同的操作数对应不同分数
  3. Use the btest test harness to check your functions for correctness. 使用 btest 来测试你的解法正确性
  4. Use the BDD checker to formally verify your functions 使用 BDD 检查格式对不对
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source. 最大操作数在函数前面会说明，如果有不一致，检查下文件来源对不对。

/*
 * STEP 2: Modify the following functions according the coding rules. 接下来，根据上面的编码规则来修改函数吧！
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES: 重要！为了避免意外
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules. 使用 dlc 编译器来检查解法是不是按指定规则来的
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers. 使用 BDD 来检查解法是否正确
 */

#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 * 
 * 按位与，如 6&5(D)=0110&0101(B)=0100(B)=4(D)
 * 只能使用 ~|
 */
int bitAnd(int x, int y)
{
  return ~(~x | ~y);
}
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
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 * 
 * 1. 默认的右移是算术右移(补齐最高位)，比如移动4位，得到 0xf8765432
 * 2. 本题就是要最高位补0
 * 
 * 0x1<<31得到 0x800000000 即：最高位是1，其他都是0， 10000000000
 * 右移 (n-1) 位得到 0x1111110000000
 * 取反得到 0x0000000ffffffffff
 * 
 * 然后把高位都截取掉即可
 * 
 */
int logicalShift(int x, int n)
{
  int mask = ~(((0x1 << 31) >> n) << 1);
  // printf("n=%d, mask=%x\n", n, mask);
  return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 * @see https://rovast.notion.site/datalab-bitcount-29c858a31c794a48baa26833bae36453
 */
int bitCount(int x)
{
  int count = 0, mask1, mask2, mask3, mask4, mask5;

  // 生成几个所需的 mask
  // mask1 = 0x55555555 =0101...
  int tmp = (0x55) | (0x55 << 8);
  mask1 = tmp | (tmp << 16);
  // mask2 = 0x33333333 = 00110011
  tmp = 0x33 | (0x33 << 8);
  mask2 = tmp | (tmp << 16);
  // mask3 = 0x0f0f0f0f = 00001111
  tmp = 0x0f | (0x0f << 8);
  mask3 = tmp | (tmp << 16);
  // mask4 = 0x00ff00ff = 0000000011111111
  mask4 = 0xff | (0xff << 16);
  // mask5 = 0x0000ffff = 00000000000000001111111111111111
  mask5 = 0xff | (0xff << 8);

  count = (x & mask1) + ((x >> 1) & mask1);
  count = (count & mask2) + ((count >> 2) & mask2);
  count = (count & mask3) + ((count >> 4) & mask3);
  count = (count & mask4) + ((count >> 8) & mask4);
  count = (count & mask5) + ((count >> 16) & mask5);

  return count;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 * 
 * 核心就是 如果 x1|x2 == 0，那么 x1 和 x2 必须都是 0。
 * 对于我们的题目 x，他是 32bits
 * 1. 我们把 32 bits 对折，得到每边 16bits  x |= x>> 16 只要有一边有 1，那么结果一定有 1
 * 2. 再把 16bits 对折，可以获取到整个 16bits 里是否有1
 * 
 * 0000000000000001  00000001     0001  01   1
 * 00000000      =>  0000      => 00 => 0 => 1
 * 00000001          0001         01    1
 */
int bang(int x)
{
  x |= x >> 16;
  x |= x >> 8;
  x |= x >> 4;
  x |= x >> 2;
  x |= x >> 1;

  return (~x) & 0x1;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 * 
 * 返回补码的最小值。
 * 补码的最小值就是最高位是 1，其他位都是 0，即 1000000000
 */
int tmin(void)
{
  return 0x1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 * 
 * 看看 x 能不能被 n 位补码表示
 * fitsBits(5,3)，3位补码的范围是 -4~3,表示不了5
 * fitsBits(-4,3)，3位表示的范围是 -4~3
 */
int fitsBits(int x, int n)
{
  //To see whether the (n-1) bit equals to all MSB (w-n) bits
  x = x >> (n + ~0);
  //(x==0)||(x==-1)
  return (!x) | (!(x + 1));

  // int step = 32 + ~n + 1; // 32-n
  // int tmp = x << step >> step;
  // return !(tmp ^ x);
  // left shift by 32-n then right shift by 32-n, and if tmp equals to x return 1
}

/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n)
{
  int bias = (x >> 31) & ((0x1 << n) + ~0);
  // printf("bias=%x\n", bias);
  // if x is positive, bias is 0. if x is negative, bias is 0...01...1
  return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)
{
  return ~x + 1;
}

/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x)
{
  // x&(1<<31)  is to check if the number is negative.
  // !x         is to check if the number is zero.
  // A number is positive if it's not negative and not zero.
  return !((x & (1 << 31)) >> 31 | !x);
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)
{
  int diff_sgn = !(x >> 31) ^ !(y >> 31);      // is 1 when signs are different
  int a = diff_sgn & (x >> 31);                // diff signs and x is neg, gives 1
  int b = !diff_sgn & !((y + (~x + 1)) >> 31); // same signs and difference is pos or = 0, gives 1
  int f = a | b;
  return f;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x)
{
  // @source: https://stackoverflow.com/questions/21442088/computing-the-floor-of-log-2x-using-only-bitwise-operators-in-c
  int i, j, k, l, m;
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);

  // i = 0x55555555
  i = 0x55 | (0x55 << 8);
  i = i | (i << 16);

  // j = 0x33333333
  j = 0x33 | (0x33 << 8);
  j = j | (j << 16);

  // k = 0x0f0f0f0f
  k = 0x0f | (0x0f << 8);
  k = k | (k << 16);

  // l = 0x00ff00ff
  l = 0xff | (0xff << 16);

  // m = 0x0000ffff
  m = 0xff | (0xff << 8);

  x = (x & i) + ((x >> 1) & i);
  x = (x & j) + ((x >> 2) & j);
  x = (x & k) + ((x >> 4) & k);
  x = (x & l) + ((x >> 8) & l);
  x = (x & m) + ((x >> 16) & m);
  x = x + ~0;
  return x;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf)
{
  int mask = (1 << 31);
  if ((uf & (~mask)) > (0xFF << 23))
  { // 0xFF << 23 = 0 11111111 000...000
    return uf;
  }
  return uf ^ mask; // 0 ^ 1 = 1, 1 ^ 1 = 0
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x)
{
  int sign, exp, frac, bitc, tailb;

  if (x == 0)
    return 0;
  else if (x == 0x80000000)
    return 0xCF000000;

  sign = (x >> 31) & 1;
  if (sign)
    x = -x;

  // count bits to the right of MSB
  bitc = 1;
  while ((x >> bitc) != 0)
    bitc++;
  bitc--;

  exp = bitc + 127;

  x = x << (31 - bitc); // clear all those zeros to the left of MSB
  frac = (x >> 8) & 0x7FFFFF;

  // round to even (nearest)
  if (bitc > 23)
  {
    tailb = x & 0xFF; // byte to round

    if ((tailb > 128) || ((tailb == 128) && (frac & 1)))
    {
      frac += 1;
      if (frac >> 23)
      {
        exp += 1;
        frac = 0;
      }
    }
  }

  return (sign << 31) | (exp << 23) | frac;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf)
{
  int signMask = (1 << 31);
  if ((uf & (~signMask)) >= (0xFF << 23))
  {
    return uf;
  }
  else if ((uf & (0xFF << 23)) == 0)
  {
    return (uf & ~(0x1FF << 23)) << 1 | (uf & signMask);
  }
  return uf + (1 << 23);
}
