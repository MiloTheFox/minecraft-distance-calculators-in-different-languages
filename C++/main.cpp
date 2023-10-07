/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.0 Beta, 10/07/2023 - 01:08PM GMT+1
 */

#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <sstream>

struct Point
{
    double x, y, z;
};

bool validateDoubleInput(const std::string &input, Point &point)
{
    std::istringstream iss(input);
    return (iss >> point.x >> point.y >> point.z) && iss.eof();
}


std::string toLower(const std::string &str)
{
    std::string lowerStr = str;
    for (char &c : lowerStr)
    {
        c = std::tolower(c);
    }
    return lowerStr;
}

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

double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    return std::round(std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2)));
}

double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    return std::fabs(p2.x - p1.x) + std::fabs(p2.y - p1.y) + std::fabs(p2.z - p1.z);
}

int main()
{
    Point point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    Point point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");
    std::string method = readMethod();

    double distance;
    if (method == "euclidean")
    {
        distance = calculateEuclideanDistance(point1, point2);
    }
    else if (method == "manhattan")
    {
        distance = calculateManhattanDistance(point1, point2);
    }

    std::cout << "The " << method << " distance between the two points is: " << distance << std::endl;

    return 0;
}
