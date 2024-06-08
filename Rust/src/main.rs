use std::io::{self, BufRead, Write};

#[derive(Copy, Clone)]
#[repr(C)]
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
    if let (Ok(point1), Ok(point2)) = (
        get_point("Enter the first point (x1 y1 z1): "),
        get_point("Enter the second point (x2 y2 z2): "),
    ) {
        match get_distance_calculation_choice() {
            Ok(DistanceMethod::Euclidean) => {
                println!(
                    "Euclidean Distance: {:.2}",
                    euclidean_distance(&point1, &point2)
                );
            }
            Ok(DistanceMethod::Manhattan) => {
                println!(
                    "Manhattan Distance: {:.2}",
                    manhattan_distance(&point1, &point2)
                );
            }
            Err(_) => println!("Invalid choice. Please select 1 or 2."),
        }
    } else {
        println!("Failed to get points. Please enter valid numbers.");
    }
}

fn get_point(prompt: &str) -> Result<Point, io::Error> {
    let stdin = io::stdin();
    let mut input = String::new();
    loop {
        print!("{}", prompt);
        io::stdout().flush()?;
        input.clear();
        stdin.lock().read_line(&mut input)?;

        let mut values = input.split_whitespace().map(str::parse);
        if let (Some(Ok(x)), Some(Ok(y)), Some(Ok(z)), None) =
            (values.next(), values.next(), values.next(), values.next())
        {
            return Ok(Point { x, y, z });
        }
        println!("Invalid input. Please enter three valid numbers separated by spaces.");
    }
}

fn get_distance_calculation_choice() -> Result<DistanceMethod, io::Error> {
    let stdin = io::stdin();
    let mut input = String::new();
    loop {
        print!("{}", PROMPT_CHOICE);
        io::stdout().flush()?;
        input.clear();
        stdin.lock().read_line(&mut input)?;

        match input.trim().parse::<u32>() {
            Ok(1) => return Ok(DistanceMethod::Euclidean),
            Ok(2) => return Ok(DistanceMethod::Manhattan),
            _ => println!("Invalid choice. Please select 1 or 2."),
        }
    }
}

fn distance<F>(point1: &Point, point2: &Point, operation: F) -> f64
where
    F: Fn(f64, f64) -> f64,
{
    [point1.x, point1.y, point1.z]
        .iter()
        .zip(&[point2.x, point2.y, point2.z])
        .map(|(&x1, &x2)| operation(x1, x2))
        .sum()
}

fn euclidean_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x1, x2| (x2 - x1).powi(2)).sqrt()
}

fn manhattan_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x1, x2| (x2 - x1).abs())
}
