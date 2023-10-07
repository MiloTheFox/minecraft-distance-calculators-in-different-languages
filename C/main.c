/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.1, 10/07/2023 - 12:45PM GMT+1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Define prompt messages for user input
#define PROMPT_POINT1 "Enter coordinates for Point 1 in the format 'x y z': "
#define PROMPT_POINT2 "Enter coordinates for Point 2 in the format 'x y z': "
#define PROMPT_METHOD "Enter the distance calculation method (euclidean or manhattan): "

// Define a struct to represent a 3D point with x, y, and z coordinates
struct Point
{
    double x, y, z;
};

// Function to safely read a line of input from the user
void safeInput(char *buffer, size_t bufferSize)
{
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    // Remove the newline character if it exists at the end of the input
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Function to input and validate a 3D point from the user
void inputAndValidatePoint(struct Point *point, const char *prompt)
{
    char inputBuffer[100];

    printf("%s", prompt);
    safeInput(inputBuffer, sizeof(inputBuffer));

    // Continue prompting until three valid numbers are entered
    while (sscanf(inputBuffer, "%lf %lf %lf", &point -> x, &point -> y, &point -> z) != 3)
    {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
    }
}

// Function to calculate the distance between two points using the specified method
double calculateDistance(const struct Point *point1, const struct Point *point2, const char *method)
{
    if (strcmp(method, "euclidean") == 0)
    {
        // Calculate Euclidean distance
        double dx = point2 -> x - point1 -> x;
        double dy = point2 -> y - point1 -> y;
        double dz = point2 -> z - point1 -> z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    else if (strcmp(method, "manhattan") == 0)
    {
        // Calculate Manhattan distance
        return fabs(point2 -> x - point1 -> x) + fabs(point2 -> y - point1 -> y) + fabs(point2 -> z - point1 -> z);
    }
    else
    {
        fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    // Declare variables to store two 3D points and the distance calculation method
    struct Point point1, point2;
    char method[20];

    // Input and validate the coordinates for Point 1 and Point 2
    inputAndValidatePoint(&point1, PROMPT_POINT1);
    inputAndValidatePoint(&point2, PROMPT_POINT2);

    // Prompt the user for the distance calculation method
    printf("%s", PROMPT_METHOD);
    safeInput(method, sizeof(method));

    // Convert the method to lowercase for case-insensitive comparison
    for (int i = 0; method[i]; i++)
    {
        method[i] = tolower(method[i]);
    }

    // Calculate and display the distance between the two points using the specified method
    double distance = calculateDistance(&point1, &point2, method);
    printf("The %s distance between the two points is: %lf\n", method, distance);

    return 0;
}
