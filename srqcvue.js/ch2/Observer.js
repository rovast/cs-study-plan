import Dep from "./Dep.js";

// Observer 将一个正常的 object 转换为一个可以被检测的 object
// 也就是说，我们给 observer 传递一个普通的 object，他就会变成一个响应式的 object
export class Observer {
  constructor(value) {
    this.value = value;

    if (!Array.isArray(value)) {
      this.walk(value);
    }
  }

  walk(obj) {
    Object.keys(obj).forEach((k) => {
      defineReactive(obj, k, obj[k]);
    });
  }
}

function defineReactive(data, key, val) {
  if (typeof val === "object") {
    new Observer(val);
  }

  let dep = new Dep();
  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      dep.depend();

      return val;
    },
    set: function (newVal) {
      if (val === newVal) {
        return;
      }

      newVal = val;
      dep.notify();
    },
  });
}
