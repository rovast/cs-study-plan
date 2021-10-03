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
 */
int logicalShift(int x, int n)
{
  return 2;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)
{
  return 2;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
  return 2;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)
{
  return 2;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)
{
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
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
  return 2;
}
