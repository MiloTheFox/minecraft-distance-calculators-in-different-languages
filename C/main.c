#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>

#define MAX_INPUT_LEN 100
#define METHOD_MAX_LEN 20
#define EUCLIDEAN_METHOD "euclidean"
#define MANHATTAN_METHOD "manhattan"
#define NUM_COORDS 3

enum Method { EUCLIDEAN, MANHATTAN, INVALID };

struct Point {
    double x, y, z;
};

enum Method parseMethod(const char *const method) {
    char methodCopy[METHOD_MAX_LEN];
    snprintf(methodCopy, METHOD_MAX_LEN, "%s", method);

    for (int i = 0; methodCopy[i]; i++) {
        methodCopy[i] = tolower((unsigned char)methodCopy[i]);
    }

    enum Method result;
    if (strcmp(methodCopy, EUCLIDEAN_METHOD) == 0) {
        result = EUCLIDEAN;
    }
    else if (strcmp(methodCopy, MANHATTAN_METHOD) == 0) {
        result = MANHATTAN;
    }
    else {
        result = INVALID;
    }

    return result;
}

void safeInput(char *buffer, size_t bufferSize) {
    if (fgets(buffer, bufferSize, stdin) == NULL) {
        fprintf(stderr, "Error reading input: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

int inputAndValidatePoint(struct Point *point, const char *prompt) {
    char inputBuffer[MAX_INPUT_LEN];

    printf("%s", prompt);
    safeInput(inputBuffer, sizeof(inputBuffer));

    while (sscanf(inputBuffer, "%lf %lf %lf", &point->x, &point->y, &point->z) != NUM_COORDS) {
        fprintf(stderr, "Invalid input. Please enter three valid numbers only.\n");
        printf("%s", prompt);
        safeInput(inputBuffer, sizeof(inputBuffer));
    }

    return 0; // Return 0 for success
}

double calculateDistance(const struct Point *point1, const struct Point *point2, enum Method method) {
    switch (method) {
        case EUCLIDEAN: {
            double dx = point2->x - point1->x;
            double dy = point2->y - point1->y;
            double dz = point2->z - point1->z;
            return (sqrt(dx * dx + dy * dy + dz * dz));
        }
        case MANHATTAN:
            return (fabs(point2->x - point1->x) + fabs(point2->y - point1->y) + fabs(point2->z - point1->z));
        default:
            fprintf(stderr, "Invalid method. Please enter 'euclidean' or 'manhattan'.\n");
            return -1; // Indicate error
    }
}

int main() {
    struct Point point1, point2;
    char methodStr[METHOD_MAX_LEN];

    inputAndValidatePoint(&point1, "Enter coordinates for Point 1 in the format 'x y z': ");
    inputAndValidatePoint(&point2, "Enter coordinates for Point 2 in the format 'x y z': ");

    printf("Enter the distance calculation method (euclidean or manhattan): ");
    safeInput(methodStr, sizeof(methodStr));

    enum Method method = parseMethod(methodStr);

    if (method != INVALID) {
        double distance = calculateDistance(&point1, &point2, method);
        printf("The %s distance between the two points is: %.2lf\n", methodStr, distance);
    }
    return 0;
}