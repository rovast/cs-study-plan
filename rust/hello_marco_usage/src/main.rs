use hello_marco::HelloMacro;
use hello_marco_derive::HelloMacro;

#[derive(HelloMacro)]
struct Pancakes;

// impl HelloMacro for Pancakes {
//     fn hello_macro() {
//         println!("Hello, Marco! My name is Pancakes");
//     }
// }

fn main() {
    Pancakes::hello_macro();
}
