/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.1, 10/07/2023 - 01:15PM GMT+1
 */

#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <sstream>

// Define a struct to represent a 3D point with x, y, and z coordinates
struct Point
{
    double x, y, z;
};

// Function to validate and parse a string as three double values into a Point struct
bool validateDoubleInput(const std::string &input, Point &point)
{
    std::istringstream iss(input);
    return (iss >> point.x >> point.y >> point.z) && iss.eof();
}

// Function to convert a string to lowercase
std::string toLower(const std::string &str)
{
    std::string lowerStr = str;
    for (char &c : lowerStr)
    {
        c = std::tolower(c);
    }
    return lowerStr;
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
        std::cerr << "Invalid input. Please enter three valid numbers only." << std::endl;
        std::cout << prompt;
    }

    return point;
}

// Function to read the distance calculation method from user input
std::string readMethod()
{
    std::string method;

    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::cin >> method;
        method = toLower(method);

        if (method == "euclidean" || method == "manhattan")
        {
            return method;
        }

        std::cerr << "Invalid method. Please enter 'euclidean' or 'manhattan'." << std::endl;
    }
}

// Function to calculate Euclidean distance between two points
double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    return std::round(std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2)));
}

// Function to calculate Manhattan distance between two points
double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    return std::fabs(p2.x - p1.x) + std::fabs(p2.y - p1.y) + std::fabs(p2.z - p1.z);
}

int main()
{
    // Read and validate coordinates for Point 1 and Point 2
    Point point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    Point point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");
    
    // Read the distance calculation method
    std::string method = readMethod();

    double distance;

    // Calculate the distance based on the chosen method
    if (method == "euclidean")
    {
        distance = calculateEuclideanDistance(point1, point2);
    }
    else if (method == "manhattan")
    {
        distance = calculateManhattanDistance(point1, point2);
    }

    // Display the calculated distance
    std::cout << "The " << method << " distance between the two points is: " << distance << std::endl;

    return 0;
}
