use std::io::{self, Write};

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
    match (
        get_point("Enter the first point (x1 y1 z1): "),
        get_point("Enter the second point (x2 y2 z2): "),
    ) {
        (Ok(point1), Ok(point2)) => match get_distance_calculation_choice() {
            Ok(DistanceMethod::Euclidean) => {
                let euclidean_distance = euclidean_distance(&point1, &point2);
                println!("Euclidean Distance: {:.2}", euclidean_distance);
            }
            Ok(DistanceMethod::Manhattan) => {
                let manhattan_distance = manhattan_distance(&point1, &point2);
                println!("Manhattan Distance: {:.2}", manhattan_distance);
            }
            _ => println!("Invalid choice. Please select 1 or 2."),
        },
        _ => println!("Failed to get points. Please enter valid numbers."),
    }
}

fn get_point(prompt: &str) -> Result<Point, io::Error> {
    loop {
        print!("{}", prompt);
        io::stdout()
            .flush()
            .unwrap_or_else(|_| panic!("Failed to flush stdout"));

        let mut input = String::new();
        io::stdin().read_line(&mut input)?;

        let mut iter = input.trim().split_whitespace().map(|s| s.parse());
        match (iter.next(), iter.next(), iter.next(), iter.next()) {
            (Some(Ok(x)), Some(Ok(y)), Some(Ok(z)), None) => {
                return Ok(Point { x, y, z });
            }
            (None, None, None, None) => {
                println!("No input. Please enter three valid numbers separated by spaces.");
            }
            _ => {
                println!("Invalid input. Please enter three valid numbers separated by spaces.");
            }
        }
    }
}

fn get_distance_calculation_choice() -> io::Result<DistanceMethod> {
    loop {
        print!("{}", PROMPT_CHOICE);
        io::stdout()
            .flush()
            .unwrap_or_else(|_| panic!("Failed to flush stdout"));

        let mut input = String::new();
        io::stdin().read_line(&mut input)?;

        return Ok(match input.trim().parse::<u32>().unwrap_or(0) {
            1 => DistanceMethod::Euclidean,
            2 => DistanceMethod::Manhattan,
            _ => {
                println!("Invalid choice. Please select 1 or 2.");
                continue;
            }
        });
    }
}

fn distance<F>(point1: &Point, point2: &Point, operation: F) -> f64
where
    F: Fn(f64, f64) -> f64,
{
    [point1.x, point1.y, point1.z]
        .iter()
        .zip([point2.x, point2.y, point2.z].iter())
        .map(|(&x1, &x2)| operation(x2, x1))
        .sum()
}

fn euclidean_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x2, x1| (x2 - x1).powi(2)).sqrt()
}

fn manhattan_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x2, x1| (x2 - x1).abs())
}
