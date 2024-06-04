pub mod pratchet;
pub mod pony;
pub mod colours;
pub mod ponies;


fn main() {
    println!("{}", pony::ponysay(&colours::colourize(&pony::balloon(&pratchet::get_quote()))));
}
