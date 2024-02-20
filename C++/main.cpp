/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.8
 */

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <algorithm>
#include <limits> // For numeric_limits

struct Point
{
    double x, y, z;
};

using DistanceCalculator = double (*)(const Point &, const Point &);

double calculateEuclideanDistance(const Point &p1, const Point &p2)
{
    return std::hypot(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

double calculateManhattanDistance(const Point &p1, const Point &p2)
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return std::abs(dx) + std::abs(dy) + std::abs(dz);
}

std::optional<Point> readPoint(const std::string &prompt)
{
    std::cout << prompt;
    std::string line;
    if (std::getline(std::cin, line))
    {
        double x, y, z;
        std::stringstream iss(line);
        if (iss >> x >> y >> z && iss.eof())
        {
            return Point{x, y, z};
        }
        else
        {
            std::cerr << "Invalid input. Please enter three valid numbers only.\n";
            return std::nullopt;
        }
    }
    else
    {
        std::cerr << "Failed to read input.\n";
        return std::nullopt;
    }
}

DistanceCalculator readMethod()
{
    std::map<std::string, DistanceCalculator> methods = {
        {"euclidean", calculateEuclideanDistance},
        {"manhattan", calculateManhattanDistance}};
    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::string method;
        if (!(std::cin >> method))
        {
            std::cerr << "Failed to read input.\n";
            return nullptr;
        }
        auto it = methods.find(method);
        if (it != methods.end())
        {
            return it->second;
        }
        std::cerr << "Invalid method. Please enter 'euclidean' or 'manhattan'.\n";
    }
}

int main()
{
    auto point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    if (!point1.has_value())
    {
        return 1;
    }
    auto point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");
    if (!point2.has_value())
    {
        return 1;
    }
    auto method = readMethod();
    if (!method)
    {
        std::cerr << "Failed to find valid distance calculation method.\n";
        return 1;
    }
    double distance = method(*point1, *point2);
    std::cout << "The distance between the two points is: ";
    std::cout << std::fixed << std::setprecision(2) << distance << '\n';
    return 0;
}
