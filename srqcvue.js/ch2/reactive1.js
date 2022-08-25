function defineReactive(data, key, val) {
    let dep = []

    Object.defineProperty(data, key, {
        enumerable: true,
        configurable: true,
        get: function() {
            dep.push(window.target) // 假设依赖是一个函数，并且放置到 window.target 上

            return val
        },
        set: function(newVal) {
            if(newVal === val) return

            dep.forEach(d => d(newVal, val))

            val = newVal
        }
    })
}
