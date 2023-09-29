/**
 * @author LunaTheFox20
 * @license MIT
 * @version v1.0, 09/30/2023 - 01:31AM GMT+1
 */

// UNTESTED CODE

// Import the necessary Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Define a struct to represent a point
struct Point
{
    double x, y, z;
};

// Function to read a line of input and remove the newline character
void safeInput(char *buffer, size_t bufferSize)
{
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    // Remove the trailing newline character, if present (to prevent buffer overflows)
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Function to validate a double input
int validateDoubleInput(const char *input)
{
    if (input == NULL || *input == '\0')
        return 0;

    int count = 0; // Number of valid doubles found
    char *endptr;

    // Loop through the input, attempting to parse doubles
    while (*input)
    {
        strtod(input, &endptr);

        // If the entire string was not consumed, it's not a valid double
        if (endptr == input)
            return 0;

        count++;
        input = endptr; // Move the input pointer to the next position

        // Skip whitespace characters
        while (isspace(*input))
            input++;
    }

    // Check if exactly three valid doubles were found
    return (count == 3);
}

int main()
{
    struct Point point1, point2;
    char inputBuffer[100];
    char method[20];

    // Input for Point 1
    printf("Enter coordinates for Point 1 in the format 'x y z': ");
    safeInput(inputBuffer, sizeof(inputBuffer));

    // Checking the input if it has 3 valid numbers or not
    while (sscanf(inputBuffer, "%lf %lf %lf", &point1.x, &point1.y, &point1.z) != 3 || !validateDoubleInput(inputBuffer))
    {
        // If there are no 3 valid numbers, the program will reprompt the user for
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("Enter coordinates for Point 1 in the format 'x y z': ");
        safeInput(inputBuffer, sizeof(inputBuffer));
    }

    // Input for Point 2
    printf("Enter coordinates for Point 2 in the format 'x y z': ");
    safeInput(inputBuffer, sizeof(inputBuffer));

    // Same logic for line 76 and 78
    while (sscanf(inputBuffer, "%lf %lf %lf", &point2.x, &point2.y, &point2.z) != 3 || !validateDoubleInput(inputBuffer))
    {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("Enter coordinates for Point 2 in the format 'x y z': ");
        safeInput(inputBuffer, sizeof(inputBuffer));
    }

    // Input for Method
    printf("Enter the distance calculation method (euclidean or manhattan): ");
    safeInput(method, sizeof(method));

    // Convert method to lowercase and validate
    for (int i = 0; method[i]; i++)
    {
        method[i] = tolower(method[i]);
    }

    while (strcmp(method, "euclidean") != 0 && strcmp(method, "manhattan") != 0)
    {
        fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
        printf("Enter the distance calculation method (euclidean or manhattan): ");
        safeInput(method, sizeof(method));
    }

    // Calculate and print the distance
    double distance;
    if (strcmp(method, "euclidean") == 0)
    {
        distance = round(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) + pow(point2.z - point1.z, 2));
    }
    else if (strcmp(method, "manhattan") == 0)
    {
        distance = fabs(point2.x - point1.x) + fabs(point2.y - point1.y) + fabs(point2.z - point1.z);
    }

    printf("The %s distance between the two points is: %lf\n", method, distance);

    return 0;
}
