# lab2

- 实验地址： https://sp19.datastructur.es/materials/lab/lab2/lab2
- 收获：配置 IntelliJ，进行 SDK 导入和调试相关练习。

## Step Over and Step Out

通过断点调试，发现 arrayMax 函数中的 max 函数返回有问题。我们直接使用 Math.max 替换即可。

```java
public static int[] arrayMax(int[] a, int[] b) {
    if (a.length != b.length) {
        System.out.println("ERROR! Arrays don't match");
        return null;
    }
    int[] returnArray = new int[a.length];
    for (int i = 0; i < a.length; i += 1) {
//            int biggerValue = max(a[i], b[i]);
        int biggerValue = Math.max(a[i], b[i]);
        returnArray[i] = biggerValue;
    }

    return returnArray;
}
```

## Conditional Breakpoints and Resume

右键断点地方，可以输入条件(condition box)，输入 `newTotal < 0` 后，重新 debug 程序，会在满足条件时暂停。

根据 vendor 和 food 当前的值，定位到是 csv 文件里有一行是负值。

```
kroger turnip 0.45 -387128732
```
