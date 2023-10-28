/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.6
 */

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

struct Point
{
    double x, y, z;
};

const std::string INVALID_INPUT_ERROR = "Invalid input. Please enter three valid numbers only.";
const std::string INVALID_METHOD_ERROR = "Invalid method. Please enter 'euclidean' or 'manhattan'.";

void printErrorMessage(const std::string &message)
{
    std::cerr << message << '\n';
}

bool validateAndParsePoint(const std::string &input, Point &point)
{
    std::istringstream iss(input);
    char extra;
    return (iss >> point.x >> point.y >> point.z) && !(iss >> extra);
}

Point readPoint(const std::string &prompt)
{
    Point point;
    std::string input;

    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, input);

        if (validateAndParsePoint(input, point))
            return point;

        printErrorMessage(INVALID_INPUT_ERROR);
    }
}

enum class Method
{
    EUCLIDEAN,
    MANHATTAN
};

Method readMethod()
{
    std::unordered_map<std::string, Method> methods = {{"euclidean", Method::EUCLIDEAN}, {"manhattan", Method::MANHATTAN}};

    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::string method;
        std::cin >> method;

        if (methods.count(method) > 0)
            return methods[method];

        printErrorMessage(INVALID_METHOD_ERROR);
    }
}

double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

int main()
{
    Point point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    Point point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");

    Method method = readMethod();

    double distance = 0;

    switch (method)
    {
    case Method::EUCLIDEAN:
        distance = calculateEuclideanDistance(point1, point2);
        break;
    case Method::MANHATTAN:
        distance = calculateManhattanDistance(point1, point2);
        break;
    default:
        printErrorMessage("Invalid method.");
        return 1;
    }

    // Use std::fixed and std::setprecision to format the output with 2 digits after the decimal point
    const std::string methodName = (method == Method::EUCLIDEAN) ? "euclidean" : "manhattan";

    std::cout << "The " << methodName << " distance between the two points is: ";
    std::cout << std::fixed << std::setprecision(2) << distance << '\n';

    return 0;
}
