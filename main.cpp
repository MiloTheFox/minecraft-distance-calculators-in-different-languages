#include <iostream>
#include <cmath>
#include <string>
#include <algorithm> // for std::transform

// Define a struct to represent a point
struct Point {
    double x, y, z;
};

// Function to calculate Euclidean distance
double calculateEuclideanDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2) + std::pow(p2.z - p1.z, 2));
}

// Function to calculate Manhattan distance
double calculateManhattanDistance(const Point& p1, const Point& p2) {
    return std::abs(p2.x - p1.x) + std::abs(p2.y - p1.y) + std::abs(p2.z - p1.z);
}

int main() {
    Point point1, point2;
    std::string method;

    try {
        std::cout << "Enter coordinates for Point 1 (x y z): ";
        std::cin >> point1.x >> point1.y >> point1.z;
        if (!std::cin) {
            throw std::invalid_argument("Invalid input. Please enter numbers only.");
        }

        std::cout << "Enter coordinates for Point 2 (x y z): ";
        std::cin >> point2.x >> point2.y >> point2.z;
        if (!std::cin) {
            throw std::invalid_argument("Invalid input. Please enter numbers only.");
        }

        std::cout << "Enter the distance calculation method (euclidean/manhattan): ";
        std::cin >> method;

        // Convert both 'method' and expected method names to lowercase
        std::transform(method.begin(), method.end(), method.begin(), ::tolower);

        if (method == "euclidean") {
            double euclideanDistance = calculateEuclideanDistance(point1, point2);
            std::cout << "The Euclidean distance between the two points is: " << euclideanDistance << std::endl;
        } else if (method == "manhattan") {
            double manhattanDistance = calculateManhattanDistance(point1, point2);
            std::cout << "The Manhattan distance between the two points is: " << manhattanDistance << std::endl;
        } else {
            throw std::invalid_argument("Invalid method. Please enter 'euclidean' or 'manhattan'.");
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    return 0;
}