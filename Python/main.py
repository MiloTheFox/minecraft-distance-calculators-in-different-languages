import math
from typing import Tuple

# Constants
EUCLIDEAN_METHOD = "euclidean"
MANHATTAN_METHOD = "manhattan"


def manhattan_distance(
    point1: Tuple[float, float, float], point2: Tuple[float, float, float]
) -> float:
    return sum(abs(a - b) for a, b in zip(point1, point2))


def get_point_input(prompt: str) -> Tuple[float, float, float]:
    while True:
        try:
            return tuple(map(float, input(prompt).split()))
        except ValueError:
            print("Invalid input. Please enter valid floating-point coordinates.")


def distance_function(
    point1: Tuple[float, float, float], point2: Tuple[float, float, float], method: str
) -> float:
    if method == EUCLIDEAN_METHOD:
        return round(math.dist(point1, point2), 2)
    elif method == MANHATTAN_METHOD:
        return round(manhattan_distance(point1, point2), 2)
    else:
        raise ValueError(f"Unknown method: {method}")


def get_method_input(prompt: str) -> str:
    while True:
        method = input(prompt).lower()
        if method in [EUCLIDEAN_METHOD, MANHATTAN_METHOD]:
            return method
        print("Invalid method. Please enter 'euclidean' or 'manhattan'.")


def main():
    while True:
        try:
            point1 = get_point_input("Enter Point 1 (x y z): ")
            point2 = get_point_input("Enter Point 2 (x y z): ")
            method = get_method_input(
                "Enter the distance method to be used (euclidean/manhattan): "
            )
            distance = distance_function(point1, point2, method)
            print(f"{method.capitalize()} Distance: {distance}")
            break
        except ValueError as e:
            print(e)


if __name__ == "__main__":
    main()
