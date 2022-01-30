# cachelab

## 参考链接

- https://zhuanlan.zhihu.com/p/142942823

## 任务

两部分

1. PartA，以 trace 的文件内容作为程序输入，分析其格式，计算命中率


文件说明

| file           | description            |
| -------------- | ---------------------- |
| `./test-csim ` | 测试自己写的 csim 效果 |
| `./driver.py ` | 全量测试               |



## 附录

通过 valgrind 可以分析内存的使用，输出类似 traces 目录下的文件格式。

```shell
apt install valgrind
```
