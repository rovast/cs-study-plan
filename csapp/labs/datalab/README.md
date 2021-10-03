# 环境准备

如果是 64bits 的机器，需要安装下面的库，否则 `make btest` 会报错 `bits/libc-header-start.h: No such file or directory`
```shell script
sudo apt-get install gcc-multilib
```

# 指令说明

```shell script
# 检查操作合不合法，有没有使用不允许的操作符
./dlc -e bits.c

# 检查结果是否正确
make btest && ./btest
```
