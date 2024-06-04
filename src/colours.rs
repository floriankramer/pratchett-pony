use rand::Rng;

/// takes a string and inserts ansi escape codes for rainbow colours
pub fn colourize(input: &str) -> String {
    let mut col = 0;
    let mut row = 0;

    let mut output = String::new();
    // We need 21 bytes per input character
    output.reserve(input.len() * 21);

    let offset = rand::thread_rng().gen::<f32>() * 2.0 * std::f32::consts::PI / FREQUENCY;

    for char in input.chars() {
        let hue = offset + (col as f32 + row as f32).sqrt();
        let color = rainbow(hue);

        output.push_str("\x1b[38;2;");
        output.push_str(&color.0.to_string());
        output.push(';');
        output.push_str(&color.1.to_string());
        output.push(';');
        output.push_str(&color.2.to_string());
        output.push('m');
        output.push(char);

        if char == '\n' {
            col = 0;
            row += 1;
        } else {
            col += 1;
        }
    }

    output.push_str("\x1b[0m");

    output
}

const FREQUENCY: f32 = 0.4;

const BASE: u32 = 20;
const DYNAMIC: f32 = 255.0 - BASE as f32;

fn rainbow(pos: f32) -> (u32, u32, u32) {
    (
        ((pos * FREQUENCY).sin() * (DYNAMIC - 70.0)) as u32 + (BASE + 70),
        ((pos * FREQUENCY + 2.0 * std::f32::consts::PI / 3.0).sin() * (DYNAMIC - 40.0)) as u32 + (BASE + 40),
        ((pos * FREQUENCY + 4.0 * std::f32::consts::PI / 3.0).sin() * DYNAMIC) as u32 + BASE,
    )
}
