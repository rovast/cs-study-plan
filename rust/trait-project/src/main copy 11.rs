fn main() {
    let string1 = String::from("long string is long");
    let result;

    {
        let string2 = String::from("xyz");

        result = longest(string1.as_str(), string2.as_str());
    }
    println!("The longest string is {}", result);
}

// 这段代码的函数签名向Rust表明，
// 函数所获取的两个字符串切片参数的存活时间，必须不短于给定的生命周期'a。
// 这个函数签名同时也意味着，从这个函数返回的字符串切片也可以获得不短于'a的生命周期。
fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
