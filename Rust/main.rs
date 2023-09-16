use std::io::{self, Write};

fn main() {
    // Input coordinates
    let (x1, y1, z1) = get_coordinates("Enter the first point (x1 y1 z1): ");
    let (x2, y2, z2) = get_coordinates("Enter the second point (x2 y2 z2): ");

    // Prompt the user for the distance calculation method
    println!("1. Euclidean Distance");
    println!("2. Manhattan Distance");

    let choice = get_distance_calculation_choice();

    // Calculate and display the selected distance
    match choice {
        1 => {
            let euclidean_distance = euclidean_distance(x1, y1, z1, x2, y2, z2);
            println!("Euclidean Distance: {:.2}", euclidean_distance);
        }
        2 => {
            let manhattan_distance = manhattan_distance(x1, y1, z1, x2, y2, z2);
            println!("Manhattan Distance: {:.2}", manhattan_distance);
        }
        _ => println!("Invalid choice. Please select 1 or 2."),
    }
    io::stdout().flush().unwrap();
}

fn get_coordinates(prompt: &str) -> (f64, f64, f64) {
    loop {
        io::stdout().flush().unwrap();
        print!("{}", prompt);
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        let coordinates: Vec<f64> = input
            .split_whitespace()
            .map(|s| {
                s.trim()
                    .parse()
                    .expect("Invalid input. Please enter numbers.")
            })
            .collect();

        if coordinates.len() != 3 {
            println!("Invalid input. Please enter three numbers separated by spaces.");
            continue;
        }

        return (coordinates[0], coordinates[1], coordinates[2]);
    }
}

fn get_distance_calculation_choice() -> u32 {
    loop {
        io::stdout().flush().unwrap();
        print!("Enter your choice: "); // Print a prompt for the choice
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read line");

        let choice: Result<u32, _> = input.trim().parse();

        match choice {
            Ok(1) | Ok(2) => return choice.unwrap(),
            _ => println!("Invalid choice. Please select 1 or 2."),
        }
    }
}

fn euclidean_distance(x1: f64, y1: f64, z1: f64, x2: f64, y2: f64, z2: f64) -> f64 {
    ((x2 - x1).powi(2) + (y2 - y1).powi(2) + (z2 - z1).powi(2))
        .sqrt()
        .round()
}

fn manhattan_distance(x1: f64, y1: f64, z1: f64, x2: f64, y2: f64, z2: f64) -> f64 {
    ((x2 - x1).abs() + (y2 - y1).abs() + (z2 - z1).abs()).round()
}
