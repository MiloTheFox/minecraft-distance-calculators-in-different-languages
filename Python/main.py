import math

# Constants
EUCLIDEAN_METHOD = "euclidean"
MANHATTAN_METHOD = "manhattan"

def euclidean_distance(point1, point2):
    """
    Calculate the Euclidean distance between two 3D points.

    Args:
    point1 (tuple): A tuple containing (x, y, z) coordinates of the first point.
    point2 (tuple): A tuple containing (x, y, z) coordinates of the second point.

    Returns:
    float: The Euclidean distance between the two points.
    """
    x1, y1, z1 = point1
    x2, y2, z2 = point2
    return math.sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

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
    return abs(x2 - x1) + abs(y2 - y1) + abs(z2 - z1)

def get_point_input(prompt):
    """
    Get 3D point coordinates (x, y, z) from the user.

    Args:
    prompt (str): The input prompt message.

    Returns:
    tuple: A tuple containing (x, y, z) coordinates.
    """
    input_str = input(prompt)
    x, y, z = map(float, input_str.split())
    return (x, y, z)

while True:
    try:
        point1 = get_point_input("Enter Point 1 (x y z): ")
        point2 = get_point_input("Enter Point 2 (x y z): ")

        method = input("Enter the distance method to be used (euclidean/manhattan): ").lower()

        if method == EUCLIDEAN_METHOD:
            distance = euclidean_distance(point1, point2)
        elif method == MANHATTAN_METHOD:
            distance = manhattan_distance(point1, point2)
        else:
            print("Invalid distance method. Please enter 'euclidean' or 'manhattan'.")
            continue  # Repeat the loop to ask for a valid method

        print(f"{method.capitalize()} Distance: {distance:.0f}")
        break  # Exit the loop if everything is successful

    except ValueError:
        print("Invalid input. Please enter valid floating-point coordinates.")
