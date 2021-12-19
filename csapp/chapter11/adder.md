```shell script
➜  chapter11 git:(main) ✗ gcc adder.c csapp.c

➜  chapter11 git:(main) ✗ export QUERY_STRING="123&456" 

➜  chapter11 git:(main) ✗ ./a.out 
Connection: close
Content-length: 111
Content-type: text/html
Welcome to add.com: The Internet addition portal.
<p>The answer is: 123 + 456 = 579
<p>Thanks for visiting!
```

两个有意思的点

1. 分割 & 来取整数时的处理方式。先寻找 & 所在的位置，然后使用 '\0' 来替换，这样进行 strcpy 的时候，遇到 '\0' 会自动停止
2. 构造返回体时，使用 `sprintf(content, "%s xxxx", content); ` 来进行字符串的追加。

