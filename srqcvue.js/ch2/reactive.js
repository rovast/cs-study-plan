import Dep from "./Dep";

function defineReactive(data, key, val) {
  let dep = new Dep();

  Object.defineProperty(data, key, {
    enumerable: true,
    configurable: true,
    get: function () {
      dep.depend();

      return val;
    },
    set: function (newVal) {
      if (newVal === val) return;

      val = newVal;

      dep.notify();
    },
  });
}
