use rand::Rng;

pub fn get_quote() -> String {
    let raw = include_str!("../pratchett/pqf");
    let mut count = 1;
    let raw_bytes = raw.as_bytes();
    for i in 0..raw.len() - 3 {
        if raw_bytes[i] == b'\n' && raw_bytes[i + 1] == b'\n' && raw_bytes[i + 2] == b'\n' {
            count += 1;
        }
    }

    let mut quotes = raw.split("\n\n\n");
    quotes
        .nth(rand::thread_rng().gen_range(0..count))
        .unwrap()
        .trim()
        .to_string()
}
