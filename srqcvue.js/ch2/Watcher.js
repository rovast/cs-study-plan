// 被收集的项，当 Objec.defineProperty 中的 setter 中 dep.notify 时，就是 watch.update
export default class Watcher {
  // 在声明的时候，实例化 watch，同时收集依赖
  constructor(vm, expOrFn, cb) {
    this.vm = vm;

    this.getter = parsePath(expOrFn);
    this.cb = cb;
    this.value = this.get();
  }

  // 获取当前表达式或者函数的值
  get() {
    window.target = this;
    // 执行 getter 的时候，同时也触发了 Object.defineProperty 的 getter，进而收集了 window.target 作为依赖
    // 其实就是收集了自己(watcher)作为依赖
    let value = this.getter.call(this.vm, this.vm);
    window.target = undefined;

    return value;
  }

  // setter 中触发 dep.update()，其执行的上下文是 vm，参数是新值、旧值，即 dep.update(newVal, oldVal)
  update() {
    const oldValue = this.value;
    this.value = this.get();
    this.cb.call(this.vm, this.value, oldValue);
  }
}

const bailRE = /[^\W.$]/;
export function parsePath(path) {
  //   if (bailRE.test(path)) return;

  // data.a.b.c
  const segments = path.split(".");
  return function (obj) {
    for (let i = 0; i < segments.length; i++) {
      if (!obj) return;
      obj = obj[segments[i]];
    }

    return obj;
  };
}
