#include <stdio.h>
#include <math.h>

#define WELCOME_MESSAGE "Welcome to the Triangle Properties Calculator App!"
#define MIN_SIDE_LENGTH 0.001
#define MAX_SIDE_LENGTH 1000
#define MIN_DECIMAL_PLACES 0
#define MAX_DECIMAL_PLACES 12

enum TriangleSides {
    SIDE_A,
    SIDE_B,
    SIDE_C
};

int validateTriangleSide(double sideLength);
int validateDecimalPlaces(int decimalPlaces);
int validateTriangleSides(double a, double b, double c);
int readAndValidateSide(char sideName, double *side);

double calculatePerimeter(double a, double b, double c);
double calculateArea(double a, double b, double c, double semiPerimeter);
double calculateHeight(double a, double b, double c, double area, enum TriangleSides heightOnSide);
double calculateMedian(double a, double b, double c, enum TriangleSides medianOnSide);
double calculateBisector(double a, double b, double c, double semiPerimeter, enum TriangleSides bisectorOnSide);

double truncateNumber(double value, int decimalPlaces);

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    double semiPerimeter = 0.0, perimeter = 0.0;
    short int decimalPlaces = 0;
    const char sideNames[] = {'a', 'b', 'c'};

    printf(WELCOME_MESSAGE "\n\n");

    if (readAndValidateSide('a', &a) == -1) return -1;
    if (readAndValidateSide('b', &b) == -1) return -1;
    if (readAndValidateSide('c', &c) == -1) return -1;

    if (validateTriangleSides(a, b, c) == -1) {
        return -1;
    }

    printf("Enter the number of decimal places (from %d to %d): ", MIN_DECIMAL_PLACES, MAX_DECIMAL_PLACES);
    scanf("%hd", &decimalPlaces);
    fflush(stdin);
    if (validateDecimalPlaces(decimalPlaces) == -1) {
        return -1;
    }

    perimeter = calculatePerimeter(a, b, c);
    printf("\nPerimeter: %.*e\n", decimalPlaces, truncateNumber(perimeter, decimalPlaces));

    semiPerimeter = perimeter / 2.0;

    const double area = calculateArea(a, b, c, semiPerimeter);
    printf("Area: %.*e\n", decimalPlaces, truncateNumber(area, decimalPlaces));

    for (int i = 0; i < 3; i++) {
        printf("Height to side '%c' (truncated): %.*e\n",
            sideNames[i],
            decimalPlaces,
            truncateNumber(calculateHeight(a, b, c, area, i), decimalPlaces)
        );
    }

    for (int i = 0; i < 3; i++) {
        printf("Median to side '%c' (truncated): %.*e\n",
            sideNames[i],
            decimalPlaces,
            truncateNumber(calculateMedian(a, b, c, i), decimalPlaces)
        );
    }

    for (int i = 0; i < 3; i++) {
        printf("Bisector to side '%c' (truncated): %.*e\n",
            sideNames[i],
            decimalPlaces,
            truncateNumber(calculateBisector(a, b, c, semiPerimeter, i), decimalPlaces)
        );
    }

    return 0;
}

int validateTriangleSide(const double sideLength) {
    if (sideLength < MIN_SIDE_LENGTH || sideLength > MAX_SIDE_LENGTH) {
        printf("Side cannot be less than %.3f and cannot be greater than %d!\n", MIN_SIDE_LENGTH, MAX_SIDE_LENGTH);

        return -1;
    }

    return 0;
}

int readAndValidateSide(const char sideName, double *side) {
    char extraChar;

    printf("Enter the length of side '%c' (from %.3f to %d): ", sideName, MIN_SIDE_LENGTH, MAX_SIDE_LENGTH);

    if (scanf("%lf%c", side, &extraChar) != 2 || extraChar != '\n') {
        printf("Invalid input! Please enter a valid number without extra characters.\n");
        return -1;
    }

    fflush(stdin);
    if (validateTriangleSide(*side) == -1) {
        return -1;
    }

    return 0;
}

int validateDecimalPlaces(const int decimalPlaces) {
    if (decimalPlaces < MIN_DECIMAL_PLACES || decimalPlaces > MAX_DECIMAL_PLACES) {
        printf("Decimal places must be between %d and %d.\n", MIN_DECIMAL_PLACES, MAX_DECIMAL_PLACES);

        return -1;
    }

    return 0;
}

int validateTriangleSides(const double a, const double b, const double c) {
    if ((a + b) <= c || (a + c) <= b || (b + c) <= a) {
        printf("Triangle with provided sides doesn't exist.\n");

        return -1;
    }

    return 0;
}

double calculatePerimeter(const double a, const double b, const double c) {
    return a + b + c;
}

double calculateArea(const double a, const double b, const double c, const double semiPerimeter) {
    return sqrt(semiPerimeter * (semiPerimeter - a) * (semiPerimeter - b) * (semiPerimeter - c));
}

double calculateHeight(const double a, const double b, const double c, const double area, const enum TriangleSides heightOnSide) {
    switch (heightOnSide) {
        case SIDE_A: return (2.0 * area) / a;
        case SIDE_B: return (2.0 * area) / b;
        case SIDE_C: return (2.0 * area) / c;
        default:
            printf("Invalid side for height calculation.\n");

            return -1;
    }
}

double calculateMedian(const double a, const double b, const double c, const enum TriangleSides medianOnSide) {
    switch (medianOnSide) {
        case SIDE_A: return 0.5 * sqrt(2.0 * b * b + 2.0 * c * c - a * a);
        case SIDE_B: return 0.5 * sqrt(2.0 * a * a + 2.0 * c * c - b * b);
        case SIDE_C: return 0.5 * sqrt(2.0 * a * a + 2.0 * b * b - c * c);
        default:
            printf("Invalid side for median calculation.\n");

            return -1;
    }
}

double calculateBisector(const double a, const double b, const double c, const double semiPerimeter, const enum TriangleSides bisectorOnSide) {
    switch (bisectorOnSide) {
        case SIDE_A: return (2.0 / (b + c)) * sqrt(b * c * semiPerimeter * (semiPerimeter - a));
        case SIDE_B: return (2.0 / (a + c)) * sqrt(a * c * semiPerimeter * (semiPerimeter - b));
        case SIDE_C: return (2.0 / (a + b)) * sqrt(a * b * semiPerimeter * (semiPerimeter - c));
        default:
            printf("Invalid side for bisector calculation.\n");

            return -1;
    }
}

double truncateNumber(const double value, const int decimalPlaces) {
    const double factor = pow(10, decimalPlaces);

    return trunc(value * factor) / factor;
}