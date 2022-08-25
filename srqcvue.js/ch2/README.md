# Object 的变化侦测

假设我们定义一个 Object
```js
const person = {
    name: 'Jack',
    age: 13
}
```

和一个模板，那么当 `person.name` 发生变化时候，页面怎么实时响应呢？
```html
<template><p>{{ person.name }}</p></template>
```

涉及到下面的问题
- 需要有种办法来监听 person 属性的变化
- 当监听到变化的时候，需要通知引用方，去更新


在 JS 中，我们可以使用 `Object.defineProperty` 来讲对象的属性变换为 setter getter 的形式，这样就能在更新和访问对象
属性时，加入自己的一些逻辑。

应用到我们举的这个例子，就是

- 在 `getter` 中收集依赖。我们的 template 文件中，读取 person.name，其实意味着”模板“依赖”person.name“
- 在 `setter` 中触发依赖的更新。当我们修改 person.name 的值，就需要通知模板来重新渲染 p 标签里面的 innerText

---

为了更好维护，这里抽象了几个类。

**Dep**

收集的依赖需要有个存储的地方，所以有了个 Dep class。主要用于：新增依赖、删除依赖、向依赖发送消息。

**Watcher**

作为具体依赖项，被保存在 Dep 中。


**Observer**

把一个 object 的所有数据转换成响应式的。



---

Data 通过 Observer 转换成了 setter/getter 的形式来追踪变化。

当外界通过 watcher 读取数据时，会触发 getter 从而将 watcher 添加到依赖 Dep 中。

当数据发生变化时，会触发 setter，从向 Dep 发送通知。(`dep.notify`)

watcher 收到通知后，调用 update，进而和外界取得联系，可能是触发视图，也可能时调用函数。
