use std::io::{self, Write};

struct Point {
    x: f64,
    y: f64,
    z: f64,
}

enum DistanceMethod {
    Euclidean,
    Manhattan,
}

const PROMPT_CHOICE: &str = "Enter your choice (1 for Euclidean, 2 for Manhattan): ";

fn main() {
    let point1 = get_point("Enter the first point (x1 y1 z1): ");
    let point2 = get_point("Enter the second point (x2 y2 z2): ");

    match get_distance_calculation_choice() {
        Ok(DistanceMethod::Euclidean) => {
            let euclidean_distance = euclidean_distance(&point1, &point2);
            println!("Euclidean Distance: {:.2}", euclidean_distance);
        }
        Ok(DistanceMethod::Manhattan) => {
            let manhattan_distance = manhattan_distance(&point1, &point2);
            println!("Manhattan Distance: {:.2}", manhattan_distance);
        }
        _ => println!("Invalid choice. Please select 1 or 2."),
    }
}

fn get_point(prompt: &str) -> Point {
    loop {
        print!("{}", prompt);
        io::stdout().flush().expect("Failed to flush stdout");

        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read input");

        let coordinates: Vec<_> = input.trim().split_whitespace().map(|s| s.parse()).collect();

        match coordinates.as_slice() {
            [Ok(x), Ok(y), Ok(z)] => {
                return Point { x: *x, y: *y, z: *z }
            }
            _ => println!("Invalid input. Please enter three numbers separated by spaces."),
        }
    }
}

fn get_distance_calculation_choice() -> io::Result<DistanceMethod> {
    loop {
        print!("{}", PROMPT_CHOICE);
        io::stdout().flush().unwrap();
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;

        match input.trim().parse::<u32>() {
            Ok(1) => return Ok(DistanceMethod::Euclidean),
            Ok(2) => return Ok(DistanceMethod::Manhattan),
            _ => println!("Invalid choice. Please select 1 or 2."),
        }
    }
}

fn calculate_differences(point1: &Point, point2: &Point) -> Point {
    Point {
        x: point2.x - point1.x,
        y: point2.y - point1.y,
        z: point2.z - point1.z,
    }
}

fn euclidean_distance(point1: &Point, point2: &Point) -> f64 {
    let diff = calculate_differences(point1, point2);
    (diff.x.powi(2) + diff.y.powi(2) + diff.z.powi(2)).sqrt()
}

fn manhattan_distance(point1: &Point, point2: &Point) -> f64 {
    let diff = calculate_differences(point1, point2);
    diff.x.abs() + diff.y.abs() + diff.z.abs()
}
