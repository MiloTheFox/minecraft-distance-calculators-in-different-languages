import math

# Constants
EUCLIDEAN_METHOD = "euclidean"
MANHATTAN_METHOD = "manhattan"


def manhattan_distance(point1, point2):
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    dx, dy, dz = abs(x2 - x1), abs(y2 - y1), abs(z2 - z1)
    return dx + dy + dz


def get_point_input(prompt):
    while True:
        try:
            input_str = input(prompt)
            x, y, z = map(float, input_str.split())
            return (x, y, z)
        except ValueError:
            print("Invalid input. Please enter valid floating-point coordinates.")


def distance_function(point1, point2, method):
    if method == EUCLIDEAN_METHOD:
        return math.dist(point1, point2)
    elif method == MANHATTAN_METHOD:
        return round(manhattan_distance(point1, point2))
    else:
        raise ValueError(
            "Invalid distance method. Please enter 'euclidean' or 'manhattan'."
        )


while True:
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")

        method = input(
            "Enter the distance method to be used (euclidean/manhattan): "
        ).lower()
        if method not in [EUCLIDEAN_METHOD, MANHATTAN_METHOD]:
            print("Invalid method. Please enter 'euclidean' or 'manhattan'.")
            continue

        distance = distance_function(point1, point2, method)
        print(f"{method.capitalize()} Distance: {distance}")
        break

    except ValueError as e:
        print(e)
