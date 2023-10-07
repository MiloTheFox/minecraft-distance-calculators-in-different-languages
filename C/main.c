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

#define PROMPT_POINT1 "Enter coordinates for Point 1 in the format 'x y z': "
#define PROMPT_POINT2 "Enter coordinates for Point 2 in the format 'x y z': "
#define PROMPT_METHOD "Enter the distance calculation method (euclidean or manhattan): "

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

void inputAndValidatePoint(struct Point *point, const char *prompt)
{
    char inputBuffer[100];

    printf("%s", prompt);
    safeInput(inputBuffer, sizeof(inputBuffer));

    while (sscanf(inputBuffer, "%lf %lf %lf", &point -> x, &point -> y, &point -> z) != 3)
    {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
    }
}

double calculateDistance(const struct Point *point1, const struct Point *point2, const char *method)
{
    if (strcmp(method, "euclidean") == 0)
    {
        double dx = point2 -> x - point1 -> x;
        double dy = point2 -> y - point1 -> y;
        double dz = point2 -> z - point1 -> z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    else if (strcmp(method, "manhattan") == 0)
    {
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
    struct Point point1, point2;
    char method[20];

    inputAndValidatePoint(&point1, PROMPT_POINT1);
    inputAndValidatePoint(&point2, PROMPT_POINT2);

    printf("%s", PROMPT_METHOD);
    safeInput(method, sizeof(method));

    for (int i = 0; method[i]; i++)
    {
        method[i] = tolower(method[i]);
    }

    double distance = calculateDistance(&point1, &point2, method);
    printf("The %s distance between the two points is: %lf\n", method, distance);

    return 0;
}
