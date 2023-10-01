import math

# Constants
EUCLIDEAN_METHOD = "euclidean"
MANHATTAN_METHOD = "manhattan"

def manhattan_distance(point1, point2):
    """
    Calculate the Manhattan distance between two 3D points.

    Args:
    point1 (tuple): A tuple containing (x, y, z) coordinates of the first point.
    point2 (tuple): A tuple containing (x, y, z) coordinates of the second point.

    Returns:
    float: The Manhattan distance between the two points.
    """
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    dx, dy, dz = abs(x2 - x1), abs(y2 - y1), abs(z2 - z1)
    return dx + dy + dz

distance_functions = {
    """
    Calculate the Euclidean distance between two 3D points.

    Args:
    point1 (tuple): A tuple containing (x, y, z) coordinates of the first point.
    point2 (tuple): A tuple containing (x, y, z) coordinates of the second point.

    Returns:
    float: The Euclidean distance between the two points.
    """
    EUCLIDEAN_METHOD: lambda point1, point2: round(math.dist(point1, point2)),
    MANHATTAN_METHOD: manhattan_distance
}

def get_point_input(prompt):
    input_str = input(prompt)
    x, y, z = map(float, input_str.split())
    return (x, y, z)

while True:
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")

        method = input("Enter the distance method to be used (euclidean/manhattan): ").lower()
        
        try:
            distance_function = distance_functions[method]
        except KeyError:
            print("Invalid distance method. Please enter 'euclidean' or 'manhattan'.")
        else:
            distance = distance_function(point1, point2)
            print(f"{method.capitalize()} Distance: {distance}")
            break

    except ValueError:
        print("Invalid input. Please enter valid floating-point coordinates.")
