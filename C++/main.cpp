/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.7
 */

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <algorithm>

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
    return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

std::optional<Point> readPoint(const std::string &prompt)
{
    std::cout << prompt;
    std::string line;
    if (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        Point point;
        char extra;
        if ((iss >> point.x >> point.y >> point.z) && !(iss >> extra))
            return point;
        else
        {
            std::cerr << "Invalid input. Please enter three valid numbers only.\n";
            return std::nullopt;
        }
    }
    else
    {
        std::cerr << "Failed to read input.\n";
        std::exit(1);
    }
}

DistanceCalculator readMethod()
{
    std::pair<std::string, DistanceCalculator> methods[] = {
        {"euclidean", calculateEuclideanDistance},
        {"manhattan", calculateManhattanDistance}};
    while (true)
    {
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        std::string method;
        if (!(std::cin >> method))
        {
            std::cerr << "Failed to read input.\n";
            std::exit(1);
        }
        auto it = std::find_if(
            std::begin(methods), std::end(methods),
            [&](const auto &m)
            { return m.first == method; });
        if (it != std::end(methods))
            return it->second;
        std::cerr << "Invalid method. Please enter 'euclidean' or 'manhattan'.\n";
    }
}

int main()
{
    auto point1 = readPoint("Enter coordinates for Point 1 in the format 'x y z': ");
    if (!point1.has_value())
        return 1;
    auto point2 = readPoint("Enter coordinates for Point 2 in the format 'x y z': ");
    if (!point2.has_value())
        return 1;
    auto method = readMethod();
    double distance = method(*point1, *point2);
    std::cout << "The distance between the two points is: ";
    std::cout << std::fixed << std::setprecision(2) << distance << '\n';
    return 0;
}
