struct ImportantExerpt<'a> {
    part: &'a str,
}

fn main() {
    let novel = String::from("Call me Ishmael, Some years ago...");
    let first_sentense = novel.split('.').next().expect("Could not find a '.'");
    let i = ImportantExerpt {
        part: first_sentense,
    };
}
