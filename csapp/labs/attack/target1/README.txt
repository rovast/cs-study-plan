This file contains materials for one instance of the attacklab.
攻击实验需要的材料

Files:

    ctarget  （包含代码注入漏洞的二进制文件。用来完成 1-3 任务）

Linux binary with code-injection vulnerability.  To be used for phases
1-3 of the assignment.



    rtarget  （包含返回值漏洞的二进制文件，完成 4-5 任务）

Linux binary with return-oriented programming vulnerability.  To be
used for phases 4-5 of the assignment.

     cookie.txt  （包含4字节签名的文件）

Text file containing 4-byte signature required for this lab instance.

     farm.c   （rtarget的源码。你可以使用 gcc 来编译和反编译）

Source code for gadget farm present in this instance of rtarget.  You
can compile (use flag -Og) and disassemble it to look for gadgets.

     hex2raw    （用来生成字节序列的程序）

Utility program to generate byte sequences.  See documentation in lab
handout.

