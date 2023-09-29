/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.0 Beta, 09/30/2023 - 01:28AM GMT+1
 */

// UNTESTED CODE

#include <iostream>
#include <cmath>
#include <string>
#include <cctype>

struct Point {
    double x, y, z;
};

void safeInput(std::string &input) {
    std::getline(std::cin, input);
}

bool validateDoubleInput(const std::string &input) {
    if (input.empty()) {
        return false;
    }

    int count = 0;
    size_t pos = 0;
    while (pos < input.length()) {
        try {
            std::stod(input.substr(pos), &pos);
            count++;
        } catch (...) {
            return false;
        }
    }

    return (count == 3);
}

int main() {
    Point point1, point2;
    std::string input;
    std::string method;

    // Input for Point 1
    std::cout << "Enter coordinates for Point 1 in the format 'x y z': ";
    safeInput(input);

    while (!validateDoubleInput(input)) {
        std::cerr << "Invalid input. Please enter three valid numbers only." << std::endl;
        std::cout << "Enter coordinates for Point 1 in the format 'x y z': ";
        safeInput(input);
    }

    sscanf(input.c_str(), "%lf %lf %lf", &point1.x, &point1.y, &point1.z);

    // Input for Point 2
    std::cout << "Enter coordinates for Point 2 in the format 'x y z': ";
    safeInput(input);

    while (!validateDoubleInput(input)) {
        std::cerr << "Invalid input. Please enter three valid numbers only." << std::endl;
        std::cout << "Enter coordinates for Point 2 in the format 'x y z': ";
        safeInput(input);
    }

    sscanf(input.c_str(), "%lf %lf %lf", &point2.x, &point2.y, &point2.z);

    // Input for Method
    std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
    safeInput(method);

    for (char &c : method) {
        c = std::tolower(c);
    }

    while (method != "euclidean" && method != "manhattan") {
        std::cerr << "Invalid method. Please enter 'euclidean' or 'manhattan'." << std::endl;
        std::cout << "Enter the distance calculation method (euclidean or manhattan): ";
        safeInput(method);

        for (char &c : method) {
            c = std::tolower(c);
        }
    }

    // Calculate and print the distance
    double distance;
    if (method == "euclidean") {
        distance = std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2) + std::pow(point2.z - point1.z, 2));
    } else if (method == "manhattan") {
        distance = std::fabs(point2.x - point1.x) + std::fabs(point2.y - point1.y) + std::fabs(point2.z - point1.z);
    }

    std::cout << "The " << method << " distance between the two points is: " << distance << std::endl;

    return 0;
}
