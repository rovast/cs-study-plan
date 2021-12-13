```shell script
➜  chapter10 git:(main) ✗ gcc statcheck.c csapp.c
➜  chapter10 git:(main) ✗ ./a.out 
Stat error: Bad address
➜  chapter10 git:(main) ✗ ./a.out baz.txt
type: regular, read: yes
➜  chapter10 git:(main) ✗ ./a.out ./
type: directory, read: yes
➜  chapter10 git:(main) ✗ 
```
通过 stat 来读取当前文件的状态信息。
