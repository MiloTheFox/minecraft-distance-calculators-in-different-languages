/**
 * @author Tooth-Fox11
 * @license MIT
 * @version v1.0 Beta, 09/15/2023 - 08:12AM GMT+1
 */

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm> // for std::transform

// Define a struct to represent a point
struct Point
{
    double x, y, z;
};

// Function to calculate Euclidean distance
double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2));
}

// Function to calculate Manhattan distance
double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

double calculateDistance(const Point &p1, const Point &p2, const std::string &method)
{
    if (method == "euclidean")
    {
        return calculateEuclideanDistance(p1, p2);
    }
    else if (method == "manhattan")
    {
        return calculateManhattanDistance(p1, p2);
    }
    else
    {
        throw std::invalid_argument("Invalid method. Please enter 'euclidean' or 'manhattan'.");
    }
}

int main()
{
    Point point1, point2;
    std::string method;

    try
    {
        std::cout << "Enter coordinates for Point 1 in the format 'x y z': ";
        if (!(std::cin >> point1.x >> point1.y >> point1.z))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Invalid input. Please enter three numbers only.");
        }

        std::cout << "Enter coordinates for Point 2 in the format 'x y z': ";
        if (!(std::cin >> point2.x >> point2.y >> point2.z))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Invalid input. Please enter three numbers only.");
        }

        std::cout << "Enter the distance calculation method (euclidean/manhattan): ";
        std::cin >> method;

        // Convert both 'method' and expected method names to lowercase to prevent input errors
        std::transform(method.begin(), method.end(), method.begin(), ::tolower);

        double distance = calculateDistance(point1, point2, method);
        std::cout << "The " << method << " distance between the two points is: " << distance << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    return 0;
}
