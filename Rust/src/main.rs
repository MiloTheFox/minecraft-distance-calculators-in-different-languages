use std::io::{self, BufRead, Write};

#[derive(Copy, Clone, Debug)]
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
    if let Ok((point1, point2)) = read_two_points() {
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
            Err(_) => eprintln!("Invalid choice. Please select 1 or 2."),
        }
    } else {
        eprintln!("Failed to get points. Please enter valid numbers.");
    }
}

fn read_two_points() -> Result<(Point, Point), io::Error> {
    let point1 = get_point("Enter the first point (x1 y1 z1): ")?;
    let point2 = get_point("Enter the second point (x2 y2 z2): ")?;
    Ok((point1, point2))
}

fn get_point(prompt: &str) -> Result<Point, io::Error> {
    let stdin = io::stdin();
    let mut input = String::new();

    loop {
        print!("{}\n", prompt);
        io::stdout().flush()?;
        input.clear();
        stdin.lock().read_line(&mut input)?;

        let numbers: Result<Vec<f64>, _> = input.split_whitespace().map(str::parse).collect();
        if let Ok(coords) = numbers {
            if coords.len() == 3 {
                return Ok(Point { x: coords[0], y: coords[1], z: coords[2] });
            }
        }
        eprintln!("Invalid input. Please enter three valid numbers separated by spaces.");
    }
}

fn get_distance_calculation_choice() -> Result<DistanceMethod, io::Error> {
    let stdin = io::stdin();
    let mut input = String::new();

    loop {
        print!("{}\n", PROMPT_CHOICE);
        io::stdout().flush()?;
        input.clear();
        stdin.lock().read_line(&mut input)?;

        match input.trim().parse::<u32>() {
            Ok(1) => return Ok(DistanceMethod::Euclidean),
            Ok(2) => return Ok(DistanceMethod::Manhattan),
            _ => eprintln!("Invalid choice. Please select 1 or 2."),
        }
    }
}

fn distance<F>(point1: &Point, point2: &Point, operation: F) -> f64
where
    F: Fn(f64, f64) -> f64,
{
    let Point { x: x1, y: y1, z: z1 } = point1;
    let Point { x: x2, y: y2, z: z2 } = point2;
    operation(*x1, *x2) + operation(*y1, *y2) + operation(*z1, *z2)
}

fn euclidean_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x1, x2| (x2 - x1).powi(2)).sqrt()
}

fn manhattan_distance(point1: &Point, point2: &Point) -> f64 {
    distance(point1, point2, |x1, x2| (x2 - x1).abs())
}
