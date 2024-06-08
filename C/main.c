#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_LEN 100
#define METHOD_MAX_LEN 20
#define EUCLIDEAN_METHOD "euclidean"
#define MANHATTAN_METHOD "manhattan"
#define NUM_COORDS 3

enum Method
{
    EUCLIDEAN,
    MANHATTAN,
    INVALID
};

struct Point
{
    double x, y, z;
};

enum Method parseMethod(const char *method)
{
    if (strcasecmp(method, EUCLIDEAN_METHOD) == 0)
    {
        return EUCLIDEAN;
    }
    else if (strcasecmp(method, MANHATTAN_METHOD) == 0)
    {
        return MANHATTAN;
    }
    else
    {
        return INVALID;
    }
}

void safeInput(char *buffer, size_t bufferSize)
{
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
}

void inputAndValidatePoint(struct Point *point, const char *prompt)
{
    char inputBuffer[MAX_INPUT_LEN];

    while (1)
    {
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
        if (sscanf(inputBuffer, "%lf %lf %lf", &point->x, &point->y, &point->z) == NUM_COORDS)
        {
            break;
        }
        fprintf(stderr, "Invalid input. Please enter three valid numbers.\n");
    }
}

double calculateDistance(const struct Point *point1, const struct Point *point2, enum Method method)
{
    double dx = point2->x - point1->x;
    double dy = point2->y - point1->y;
    double dz = point2->z - point1->z;

    if (method == EUCLIDEAN)
    {
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    else if (method == MANHATTAN)
    {
        return fabs(dx) + fabs(dy) + fabs(dz);
    }
    else
    {
        return -1;
    }
}

int main()
{
    struct Point point1, point2;
    char methodStr[METHOD_MAX_LEN];

    inputAndValidatePoint(&point1, "Enter coordinates for Point 1 (x y z): ");
    inputAndValidatePoint(&point2, "Enter coordinates for Point 2 (x y z): ");

    printf("Enter the distance calculation method (euclidean or manhattan): ");
    safeInput(methodStr, sizeof(methodStr));

    enum Method method = parseMethod(methodStr);

    if (method != INVALID)
    {
        double distance = calculateDistance(&point1, &point2, method);
        printf("The %s distance between the two points is: %.2lf\n", methodStr, distance);
    }
    else
    {
        fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
    }

    return 0;
}
