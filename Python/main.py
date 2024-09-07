import math
from typing import Tuple, List

# Constants
METHODS = {
    "euclidean": "euclidean",
    "manhattan": "manhattan"
}

def manhattan_distance(point1: Tuple[float, ...], point2: Tuple[float, ...]) -> float:
    """Calculate Manhattan distance between two points."""
    return sum(abs(a - b) for a, b in zip(point1, point2))

def get_point_input(prompt: str) -> Tuple[float, ...]:
    """Get a point (x, y, z) as input from the user."""
    while True:
        try:
            return tuple(map(float, input(prompt).split()))
        except ValueError:
            print("Invalid input. Please enter valid floating-point coordinates (x y z).")

def distance_function(
    point1: Tuple[float, ...], point2: Tuple[float, ...], method: str
) -> float:
    """Compute the distance between two points based on the specified method."""
    if method == METHODS["euclidean"]:
        return round(math.dist(point1, point2), 2)
    elif method == METHODS["manhattan"]:
        return round(manhattan_distance(point1, point2), 2)
    else:
        raise ValueError(f"Unknown method: {method}")

def get_method_input(prompt: str) -> str:
    """Prompt the user for a valid distance method."""
    while True:
        method = input(prompt).lower()
        if method in METHODS:
            return method
        print("Invalid method. Please enter 'euclidean' or 'manhattan'.")

def main():
    """Main function to compute the distance between two points based on user input."""
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")
        method = get_method_input("Enter the distance method (euclidean/manhattan): ")
        distance = distance_function(point1, point2, method)
        print(f"{method.capitalize()} Distance: {distance}")
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
