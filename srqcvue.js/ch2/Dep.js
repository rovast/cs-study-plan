// 依赖收集，在 Object.defineProperty 中收集(depend)和通知(notify)
export default class Dep {
  constructor() {
    this.subs = [];
  }

  addSub(sub) {
    this.subs.push(sub);
  }

  removeSub(sub) {
    remove(this.subs, sub);
  }

  // 依赖收集
  depend() {
    if (window.target) {
      this.addSub(window.target);
    }
  }

  // 通知
  notify() {
    const subs = this.subs.slice();

    subs.forEach((s) => s.update());
  }
}

function remove(arr, item) {
  if (!arr.length) return;

  const index = arr.indexOf(item);
  if (index > -1) {
    arr.splice(index, 1);
  }
}
