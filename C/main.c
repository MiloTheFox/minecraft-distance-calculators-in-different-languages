#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

enum Method parseMethod(const char *const method)
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

static void safeInput(char *const buffer, const size_t bufferSize)
{
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    const size_t len = strlen(buffer);

    if (buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
    }
}

int inputAndValidatePoint(struct Point *const point, const char *const prompt)
{
    char inputBuffer[MAX_INPUT_LEN];

    printf("%s", prompt);
    safeInput(inputBuffer, sizeof(inputBuffer));

    while (sscanf(inputBuffer, "%lf %lf %lf", &point->x, &point->y, &point->z) != NUM_COORDS)
    {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
    }
    return 0;
}

double calculateDistance(const struct Point *const point1, const struct Point *const point2, const enum Method method)
{
    const double dx = point2->x - point1->x;
    const double dy = point2->y - point1->y;
    const double dz = point2->z - point1->z;

    switch (method)
    {
    case EUCLIDEAN:
        return (sqrt(dx * dx + dy * dy + dz * dz));
    case MANHATTAN:
        return (fabs(dx) + fabs(dy) + fabs(dz));
    default:
        return -1;
    }
}

int main()
{
    struct Point point1, point2;
    char methodStr[METHOD_MAX_LEN];

    inputAndValidatePoint(&point1, "Enter coordinates for Point 1 in the format 'x y z': ");
    inputAndValidatePoint(&point2, "Enter coordinates for Point 2 in the format 'x y z': ");

    printf("Enter the distance calculation method (euclidean or manhattan): ");
    safeInput(methodStr, sizeof(methodStr));

    const enum Method method = parseMethod(methodStr);

    if (method != INVALID)
    {
        const double distance = calculateDistance(&point1, &point2, method);
        if (distance != -1)
        {
            printf("The %s distance between the two points is: %.2lf\n", methodStr, distance);
        }
        else
        {
            fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
    }

    return 0;
}
