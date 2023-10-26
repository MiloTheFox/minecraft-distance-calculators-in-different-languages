use std::io;

struct Point {
    x: f64,
    y: f64,
    z: f64,
}

const PROMPT_CHOICE: &str = "Enter your choice (1 for Euclidean, 2 for Manhattan): ";

fn main() {
    let point1 = get_coordinates("Enter the first point (x1 y1 z1): ").unwrap();
    let point2 = get_coordinates("Enter the second point (x2 y2 z2): ").unwrap();

    match get_distance_calculation_choice().unwrap() {
        1 => {
            let euclidean_distance = euclidean_distance(&point1, &point2);
            println!("Euclidean Distance: {:.2}", euclidean_distance);
        }
        2 => {
            let manhattan_distance = manhattan_distance(&point1, &point2);
            println!("Manhattan Distance: {:.2}", manhattan_distance);
        }
        _ => println!("Invalid choice. Please select 1 or 2."),
    }
}

fn get_coordinates(prompt: &str) -> io::Result<Point> {
    loop {
        print!("{}", prompt);
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;

        let coordinates: Result<Vec<f64>, _> = input
            .split_whitespace()
            .map(|s| s.trim().parse())
            .collect();

        match coordinates {
            Ok(coords) if coords.len() == 3 => {
                return Ok(Point {
                    x: coords[0],
                    y: coords[1],
                    z: coords[2],
                });
            }
            _ => println!("Invalid input. Please enter three numbers separated by spaces."),
        }
    }
}


fn get_distance_calculation_choice() -> io::Result<u32> {
    loop {
        print!("{}", PROMPT_CHOICE);
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;

        if let Ok(choice) = input.trim().parse() {
            if choice == 1 || choice == 2 {
                return Ok(choice);
            }
        }

        println!("Invalid choice. Please select 1 or 2.");
    }
}

fn euclidean_distance(point1: &Point, point2: &Point) -> f64 {
    [(point1.x, point2.x), (point1.y, point2.y), (point1.z, point2.z)]
        .iter()
        .map(|(a, b)| (b - a).powi(2))
        .sum::<f64>()
        .sqrt()
}

fn manhattan_distance(point1: &Point, point2: &Point) -> f64 {
    [(point1.x, point2.x), (point1.y, point2.y), (point1.z, point2.z)]
        .iter()
        .map(|(a, b)| (b - a).abs())
        .sum::<f64>()
}