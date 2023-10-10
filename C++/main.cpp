/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.2, 10/10/2023 - 06:26PM GMT+1
 */

#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <sstream>
#include <algorithm>

// Define a struct to represent a 3D point with x, y, and z coordinates
struct Point
{
    double x, y, z;
};

// Function to print an error message using std::cerr
void printErrorMessage(const std::string &message)
{
    std::cerr << message << std::endl;
}

// Function to validate and parse a string as three double values into a Point struct
bool validateDoubleInput(const std::string &input, Point &point)
{
    std::istringstream iss(input);
    return (iss >> point.x >> point.y >> point.z) && !iss.fail();
}

// Function to convert a string to lowercase in place using std::transform
void toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Function to read a Point from user input with validation
Point readPoint(const std::string &prompt)
{
    Point point;
    std::string input;

    std::cout << prompt;
    while (true)
    {
        std::getline(std::cin, input);
        if (validateDoubleInput(input, point))
            break;
        printErrorMessage("Invalid input. Please enter three valid numbers only.");
        std::cout << prompt;
    }

    return point;
}

// Define an enum type for the distance calculation methods
enum Method
{
    EUCLIDEAN,
    MANHATTAN
};

// Function to read the distance calculation method from user input and return the corresponding enum value
Method readMethod()
{
    std::string method;

    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::cin >> method;
        toLower(method);

        if (method == "euclidean")
        {
            return EUCLIDEAN;
        }
        else if (method == "manhattan")
        {
            return MANHATTAN;
        }

        printErrorMessage("Invalid method. Please enter 'euclidean' or 'manhattan'.");
    }
}

// Function to calculate Euclidean distance between two points using std::hypot
double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    return std::round(std::hypot(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z));
}

// Function to calculate Manhattan distance between two points using std::abs
double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

int main()
{
    // Read and validate coordinates for Point 1 and Point 2
    Point point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    Point point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");
    
    // Read the distance calculation method
    Method method = readMethod();

    double distance;

    // Calculate the distance based on the chosen method using switch statement
    switch (method)
    {
    case EUCLIDEAN:
        distance = calculateEuclideanDistance(point1, point2);
        break;
    case MANHATTAN:
        distance = calculateManhattanDistance(point1, point2);
        break;
    default:
        printErrorMessage("Invalid method.");
        return 1;
    }

    // Display the calculated distance
    std::cout << "The " << (method == EUCLIDEAN ? "euclidean" : "manhattan") << " distance between the two points is: " << distance << std::endl;

    return 0;
}