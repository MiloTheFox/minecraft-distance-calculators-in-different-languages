import math

# Constants
EUCLIDEAN_METHOD = "euclidean"
MANHATTAN_METHOD = "manhattan"


def manhattan_distance(point1, point2):
    return sum(abs(a - b) for a, b in zip(point1, point2))


def get_point_input(prompt):
    while True:
        try:
            return tuple(map(float, input(prompt).split()))
        except ValueError:
            print("Invalid input. Please enter valid floating-point coordinates.")


def distance_function(point1, point2, method):
    if method == EUCLIDEAN_METHOD:
        return round(math.dist(point1, point2), 2)
    elif method == MANHATTAN_METHOD:
        return round(manhattan_distance(point1, point2), 2)


def get_method_input(prompt):
    while True:
        method = input(prompt).lower()
        if method in [EUCLIDEAN_METHOD, MANHATTAN_METHOD]:
            return method
        print("Invalid method. Please enter 'euclidean' or 'manhattan'.")


while True:
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")
        method = get_method_input("Enter the distance method to be used (euclidean/manhattan): ")
        distance = distance_function(point1, point2, method)
        print(f"{method.capitalize()} Distance: {distance}")
        break
    except ValueError as e:
        print(e)
