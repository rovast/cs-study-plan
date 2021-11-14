观察 combine，为什么使用 `long length = vec_length(v)` 暂存数据后，性能得到了大幅提升。

```shell script
gcc -Og -c combine.c
objdump -d combine.o > combine.asm
```
