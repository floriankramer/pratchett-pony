use rand::Rng;

use crate::ponies;

pub fn ponysay(text: &str) -> String {
    let raw_pony = ponies::PONIES[rand::thread_rng().gen_range(0..ponies::PONIES.len())];

    // parse the pony
    let start = raw_pony.rfind("$$$").unwrap_or(0);

    let art = &raw_pony[start..].to_string();

    // Extract the APPEARANCE string
    let appeareance_start = raw_pony.find("APPEARANCE:").unwrap_or(0) + "APPEARANCE:".len();
    let appeareance_end =
        raw_pony[appeareance_start..].find('\n').unwrap_or(0) + appeareance_start + 1;
    let appearance = raw_pony[appeareance_start..appeareance_end]
        .trim()
        .to_string();

    let balloon_start = art.find("$balloon").unwrap_or(0);
    let balloon_end = art[balloon_start..].find('\n').unwrap_or(0) + balloon_start + 1;

    let art = art[0..balloon_start].to_string()
        + text
        + "\n"
        + &art[balloon_end..]
        + "\n"
        + if appeareance_start > 11 && !appearance.contains("http") {
            &appearance
        } else {
            ""
        };

    art.replace('$', " ")
}

pub fn balloon(text: &str) -> String {
    let mut width = 0;
    let mut height = 0;

    for line in text.lines() {
        width = width.max(line.len());
        height += 1;
    }

    let mut res = String::new();
    res.reserve((width + 4) * (height + 2));

    // Top bar
    res.push('\u{250c}');
    for _ in 0..width + 2 {
        res.push('\u{2500}');
    }
    res.push('\u{2510}');
    res.push('\n');

    // lines
    for line in text.lines() {
        res.push('\u{2502}');
        res.push(' ');
        res.push_str(line);
        for _ in 0..width - line.len() {
            res.push(' ');
        }
        res.push(' ');
        res.push('\u{2502}');
        res.push('\n');
    }

    // Bottom
    res.push('\u{2514}');
    for _ in 0..width + 2 {
        res.push('\u{2500}');
    }
    res.push('\u{2518}');

    res
}
