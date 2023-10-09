#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 100
#define METHOD_MAX_LENGTH 20
#define EUCLIDEAN_METHOD "euclidean"
#define MANHATTAN_METHOD "manhattan"

struct Point
{
    double x, y, z;
};

void safeInput(char *buffer, size_t bufferSize)
{
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

int inputAndValidatePoint(struct Point *point, const char *prompt)
{
    char inputBuffer[MAX_INPUT_LENGTH];

    printf("%s", prompt);
    safeInput(inputBuffer, sizeof(inputBuffer));

    while (sscanf(inputBuffer, "%lf %lf %lf", &point->x, &point->y, &point->z) != 3)
    {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
    }

    return 0; // Return 0 for success
}

double calculateDistance(const struct Point *point1, const struct Point *point2, const char *method)
{
    if (strcmp(method, EUCLIDEAN_METHOD) == 0)
    {
        double dx = point2->x - point1->x;
        double dy = point2->y - point1->y;
        double dz = point2->z - point1->z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    else if (strcmp(method, MANHATTAN_METHOD) == 0)
    {
        return fabs(point2->x - point1->x) + fabs(point2->y - point1->y) + fabs(point2->z - point1->z);
    }
    else
    {
        fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
        return -1; // Indicate error
    }
}

int main()
{
    struct Point point1, point2;
    char method[METHOD_MAX_LENGTH];

    inputAndValidatePoint(&point1, "Enter coordinates for Point 1 in the format 'x y z': ");
    inputAndValidatePoint(&point2, "Enter coordinates for Point 2 in the format 'x y z': ");

    printf("Enter the distance calculation method (euclidean or manhattan): ");
    safeInput(method, sizeof(method));

    for (int i = 0; method[i]; i++)
    {
        method[i] = tolower(method[i]);
    }

    double distance = calculateDistance(&point1, &point2, method);
    if (distance >= 0)
    {
        printf("The %s distance between the two points is: %lf\n", method, distance);
    }

    return 0;
}
