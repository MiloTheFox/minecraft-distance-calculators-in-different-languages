use std::io::{self};

const PROMPT_POINT_1: &str = "Enter the first point (x1 y1 z1): ";
const PROMPT_POINT_2: &str = "Enter the second point (x2 y2 z2): ";
const PROMPT_CHOICE: &str = "Enter your choice: ";

fn main() {
    // Input coordinates
    let (x1, y1, z1) = get_coordinates(PROMPT_POINT_1).unwrap();
    let (x2, y2, z2) = get_coordinates(PROMPT_POINT_2).unwrap();
    // Prompt the user for the distance calculation method
    println!("1. Euclidean Distance");
    println!("2. Manhattan Distance");
    let choice = get_distance_calculation_choice().unwrap();
    // Calculate and display the selected distance
    match choice {
        1 => {
            let euclidean_distance = euclidean_distance(x1, y1, z1, x2, y2, z2);
            println!("Euclidean Distance: {:.2}", euclidean_distance)
        }
        2 => {
            let manhattan_distance = manhattan_distance(x1, y1, z1, x2, y2, z2);
            println!("Manhattan Distance: {:.2}", manhattan_distance)
        }
        _ => println!("Invalid choice. Please select 1 or 2."),
    }
}

fn get_coordinates(prompt: &str) -> io::Result<(f64, f64, f64)> {
    loop {
        print!("{}", prompt);
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        let coordinates: Result<Vec<f64>, _> = input
            .split_whitespace()
            .map(|s| s.trim().parse())
            .collect();
        match coordinates {
            Ok(coords) if coords.len() == 3 => return Ok((coords[0], coords[1], coords[2])),
            _ => println!("Invalid input. Please enter three numbers separated by spaces."),
        }
    }
}

fn get_distance_calculation_choice() -> io::Result<u32> {
    loop {
        print!("{}", PROMPT_CHOICE);
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        match input.trim().parse() {
            Ok(1) | Ok(2) => return Ok(input.trim().parse().unwrap()),
            _ => println!("Invalid choice. Please select 1 or 2."),
        }
    }
}

fn euclidean_distance(x1: f64, y1: f64, z1: f64, x2: f64, y2: f64, z2: f64) -> f64 {
    [(x1, x2), (y1, y2), (z1, z2)]
    .iter()
    .map(|(a, b)| (b - a).powi(2))
    .sum::<f64>()
    .sqrt()
}

fn manhattan_distance(x1: f64, y1: f64, z1: f64, x2: f64, y2: f64, z2: f64) -> f64 {
    [(x1, x2), (y1, y2), (z1, z2)]
    .iter()
    .map(|(a, b)| (b - a).abs())
    .sum::<f64>()
}