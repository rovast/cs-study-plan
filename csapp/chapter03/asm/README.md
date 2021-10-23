```shell script
# 生成汇编代码
gcc-Og -S rfact.c

# 反汇编
gcc -Og -c rfact.c # 生成 rfact.o
objdump -d rfact.o
```
