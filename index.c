// PASSED

#include <stdio.h>
#include <math.h>

#define WELCOME_MESSAGE "Welcome to the Triangle Properties Calculator App!"
#define MIN_SIDE_LENGTH 0.00001
#define MAX_SIDE_LENGTH 100000
#define MIN_DECIMAL_PLACES 0
#define MAX_DECIMAL_PLACES 24

enum TriangleSides {
    SIDE_A,
    SIDE_B,
    SIDE_C
};

void readAndValidateSide(char sideName, double *side);
void readAndValidateDecimalPlaces(int *decimalPlaces);
int validateTriangleSides(double a, double b, double c);

double calculatePerimeter(double a, double b, double c);
double calculateArea(double a, double b, double c, double semiPerimeter);
double calculateHeight(double a, double b, double c, double area, enum TriangleSides heightOnSide);
double calculateMedian(double a, double b, double c, enum TriangleSides medianOnSide);
double calculateBisector(double a, double b, double c, double semiPerimeter, enum TriangleSides bisectorOnSide);

double truncateNumber(double value, int decimalPlaces);
void printNumber(double value, int decimalPlaces);

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    double semiPerimeter = 0.0, perimeter = 0.0;
    int decimalPlaces = 0;
    const char sideNames[] = {'a', 'b', 'c'};

    printf("%s\n\n", WELCOME_MESSAGE);

    readAndValidateSide('a', &a);
    readAndValidateSide('b', &b);
    readAndValidateSide('c', &c);

    if (validateTriangleSides(a, b, c) == -1) {
        return -1;
    }

    readAndValidateDecimalPlaces(&decimalPlaces);

    perimeter = calculatePerimeter(a, b, c);
    printf("\nPerimeter: ");
    printNumber(perimeter, decimalPlaces);

    semiPerimeter = perimeter / 2.0;

    const double area = calculateArea(a, b, c, semiPerimeter);
    printf("Area: ");
    printNumber(area, decimalPlaces);

    for (int i = 0; i < 3; i++) {
        printf("Height to side '%c': ", sideNames[i]);
        printNumber(calculateHeight(a, b, c, area, i), decimalPlaces);
    }

    for (int i = 0; i < 3; i++) {
        printf("Median to side '%c': ", sideNames[i]);
        printNumber(calculateMedian(a, b, c, i), decimalPlaces);
    }

    for (int i = 0; i < 3; i++) {
        printf("Bisector to side '%c': ", sideNames[i]);
        printNumber(calculateBisector(a, b, c, semiPerimeter, i), decimalPlaces);
    }

    return 0;
}

void readAndValidateSide(const char sideName, double *side) {
    int validInput = 0;
    char extraChar;

    do {
        printf("Enter the length of side '%c' (from %.5f to %d): ", sideName, MIN_SIDE_LENGTH, MAX_SIDE_LENGTH);

        if (scanf("%lf%c", side, &extraChar) != 2 || extraChar != '\n') {
            printf("Invalid input! Please enter a number without extra characters.\n");
        } else if (*side < MIN_SIDE_LENGTH || *side > MAX_SIDE_LENGTH) {
            printf("The side length cannot be less than %.5f and greater than %d!\n", MIN_SIDE_LENGTH, MAX_SIDE_LENGTH);
        } else {
            validInput = 1;
        }

        while (extraChar != '\n' && extraChar != EOF) {
            extraChar = getchar();
        }
    } while (!validInput);
}

void readAndValidateDecimalPlaces(int *decimalPlaces) {
    int validInput = 0;
    char extraChar;

    do {
        printf("Enter the number of decimal places (from %d to %d): ", MIN_DECIMAL_PLACES, MAX_DECIMAL_PLACES);

        if (scanf("%d%c", decimalPlaces, &extraChar) != 2 || extraChar != '\n') {
            printf("Invalid input! Please enter an integer without extra characters.\n");
        } else if (*decimalPlaces < MIN_DECIMAL_PLACES || *decimalPlaces > MAX_DECIMAL_PLACES) {
            printf("The number of decimal places must be between %d and %d.\n", MIN_DECIMAL_PLACES, MAX_DECIMAL_PLACES);
        } else {
            validInput = 1;
        }

        while (extraChar != '\n' && extraChar != EOF) {
            extraChar = getchar();
        }
    } while (!validInput);
}

int validateTriangleSides(const double a, const double b, const double c) {
    if ((a + b) <= c || (a + c) <= b || (b + c) <= a) {
        printf("A triangle with the given sides does not exist.\n");

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
    const double factor = pow(10.0, (double) decimalPlaces);

    return trunc(value * factor) / factor;
}

void printNumber(const double value, const int decimalPlaces) {
    const double truncatedValue = truncateNumber(value, decimalPlaces);

    if (truncatedValue != 0.0) {
        printf("%.*f\n", decimalPlaces, truncatedValue);
    } else {
        if (value == 0.0) {
            printf("0e+00\n");
        } else {
            const int exponent = (int)floor(log10(fabs(value)));
            double mantissa = value / pow(10.0, (double) exponent);
            mantissa = trunc(mantissa * 10.0) / 10.0;

            printf("%.1fe%+03d (auto modified)\n", mantissa, exponent);
        }
    }
}