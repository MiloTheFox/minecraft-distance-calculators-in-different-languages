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
    EUCLIDEAN_METHOD: math.dist,
    MANHATTAN_METHOD: manhattan_distance
}

def get_point_input(prompt):
    input_str = input(prompt)
    x, y, z = map(float, input_str.split())
    return (x, y, z)

def distance_function(point1, point2, method, distance_functions):
    """
    Calculate the distance between two 3D points using a given method.

    Args:
    point1 (tuple): A tuple containing (x, y, z) coordinates of the first point.
    point2 (tuple): A tuple containing (x, y, z) coordinates of the second point.
    method (str): The name of the distance method to be used.
    distance_functions (dict): A dictionary mapping distance methods to functions.

    Returns:
    float: The distance between the two points using the given method.
    """
    
    try:
        distance_function = distance_functions[method]
        return round(distance_function(point1, point2))
    except KeyError:
        print("Invalid distance method. Please enter 'euclidean' or 'manhattan'.")
        return None

while True:
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")

        method = input("Enter the distance method to be used (euclidean/manhattan): ").lower()
        
        distance = distance_function(point1, point2, method, distance_functions)
        if distance is not None:
            print(f"{method.capitalize()} Distance: {distance}")
            break

    except ValueError:
        print("Invalid input. Please enter valid floating-point coordinates.")