/**
* @author LunaTheFox20
* @license MIT
* @version v1.5
*/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip> // Include the <iomanip> library

struct Point
{
    double x, y, z;
};

void printErrorMessage(const std::string &message)
{
    std::cerr << message << std::endl;
}

bool parseDouble(const std::string &str, double &value)
{
    std::istringstream iss(str);
    return (iss >> value) && iss.eof();
}

bool validateAndParsePoint(const std::string &input, Point &point)
{
    std::istringstream iss(input);
    return (iss >> point.x >> point.y >> point.z) && iss.eof();
}

std::string toLower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
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

        printErrorMessage("Invalid input. Please enter three valid numbers only.");
    }
}

enum class Method
{
    EUCLIDEAN,
    MANHATTAN
};

Method readMethod()
{
    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::string method;
        std::cin >> method;

        if (toLower(method) == "euclidean")
            return Method::EUCLIDEAN;
        if (toLower(method) == "manhattan")
            return Method::MANHATTAN;

        printErrorMessage("Invalid method. Please enter 'euclidean' or 'manhattan'.");
    }
}

double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    
    return std::round(std::sqrt(dx * dx + dy * dy + dz * dz));
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
    std::cout << "The " << (method == Method::EUCLIDEAN ? "euclidean" : "manhattan") << " distance between the two points is: ";
    std::cout << std::fixed << std::setprecision(2) << distance << std::endl;

    return 0;
}