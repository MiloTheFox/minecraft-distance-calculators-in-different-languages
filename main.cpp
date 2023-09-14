#include <iostream>
#include <cmath>
#include <string>

// Function to calculate Euclidean distance
double calculateEuclideanDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
}

// Function to calculate Manhattan distance
double calculateManhattanDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1) + std::abs(z2 - z1);
}

int main() {
    double x1, y1, z1, x2, y2, z2;
    std::string method;

    try {
        std::cout << "Enter coordinates for Point 1 (x y z): ";
        std::cin >> x1 >> y1 >> z1;
        if(!std::cin) {
            throw std::invalid_argument("Invalid input. Please enter numbers only.");
        }

        std::cout << "Enter coordinates for Point 2 (x y z): ";
        std::cin >> x2 >> y2 >> z2;
        if(!std::cin) {
            throw std::invalid_argument("Invalid input. Please enter numbers only.");
        }

        std::cout << "Enter the distance calculation method (euclidean/manhattan): ";
        std::cin >> method;
        if(method != "euclidean" && method != "manhattan") {
            throw std::invalid_argument("Invalid method. Please enter 'euclidean' or 'manhattan'.");
        }

        if(method == "euclidean") {
            double euclideanDistance = calculateEuclideanDistance(x1, y1, z1, x2, y2, z2);
            std::cout << "The Euclidean distance between the two points is: " << euclideanDistance << std::endl;
        } else if(method == "manhattan") {
            double manhattanDistance = calculateManhattanDistance(x1, y1, z1, x2, y2, z2);
            std::cout << "The Manhattan distance between the two points is: " << manhattanDistance << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }

    return 0;
}
