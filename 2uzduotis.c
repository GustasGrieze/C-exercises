/*
Gustas Griežė Programų sistemos 1 grupė 1 pogrupis
7. Užduotis:
    Įvesti sveiką skaičių N. Įvesti N sveikų skaičių a1, a2, ... aN. Jeigu tarp jų visi skaičiai
    yra neigiami arba visi neneigiami - išvesti pranešimą. Priešingu atveju apskaičiuoti reiškinį:
    S=x1*y1+x2*y2+...+xp*yp, kur
    xi - neigiami sekos nariai, einantys iš eilės,
    yi - neneigiami sekos nariai, einantys iš eilės,
    p = min(n, t), kur n - neigiamų sekos narių skaičius, o t - neneigiamų sekos narių skaičius.
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Function prototypes
bool areAllNonNegative(int arr[], int n);
bool areAllNegative(int arr[], int n);
int calculateExpression(int arr[], int n);
void clearInputBuffer();

int main() {
    int N;
    int numbers[MAX_SIZE];
    double N_double; // Temporary variable to hold the double input

    printf("This program takes in an integer N (amount of numbers) and then asks you to enter N integers.\nIf all the the entered integers are positive or all the entered integers are negative the program will provide you with a message and end.\nOtherwise it will find the expression:\n\n");
    printf("S=x1*y1+x2*y2+...+xp*yp, where:\nxi - negative consecutive members of the sequence,\nyi - non-negative consecutive members of the sequence,\np = min(n, t), where n is the number of negative terms of the sequence and t is the number of non-negative terms of the sequence.\n\n");

    // Enter the number of integers
    printf("Enter the number of integers N (1 to %d): ", MAX_SIZE);
    while (scanf("%lf", &N_double) != 1 || N_double != (int)N_double || N_double <= 0 || N_double > MAX_SIZE) {
        printf("Invalid input. Please enter a positive integer within the range (1 to %d): ", MAX_SIZE);
        clearInputBuffer();
    }
    N = (int)N_double;
    printf("\nThe number of integers has been successfully entered!\n");

    // Enter N integers
    for (int i = 0; i < N; ++i) {
        printf("Enter integer #%d: ", i + 1);
        while (scanf("%lf", &N_double) != 1 || N_double != (int)N_double) {
            printf("Invalid input. Please enter an integer: ");
            clearInputBuffer();
        }
        numbers[i] = (int)N_double;
        printf("Integer #%d has been successfully entered!\n", i + 1);
    }

    // Check if all numbers are negative or non-negative
    bool allNonNegative = areAllNonNegative(numbers, N);
    bool allNegative = areAllNegative(numbers, N);

    if (allNonNegative || allNegative) {
        printf("All numbers are %s.\n", allNonNegative ? "non-negative" : "negative");
    } else {
        // Calculate and display expression
        int expression = calculateExpression(numbers, N);
        printf("The calculated expression is: %d\n", expression);
    }

    return 0;
}

// Function to check if all elements are non-negative
bool areAllNonNegative(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0){
            return false;
        }
    }
    return true;
}

// Function to check if all elements are negative
bool areAllNegative(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0){
           return false;
        }
    }
    return true;
}

// Function to calculate the expression
int calculateExpression(int arr[], int n) {
    int sum = 0;
    int negCount = 0, nonNegCount = 0;
    int neg[MAX_SIZE] = {0}, nonNeg[MAX_SIZE] = {0};

    // Separate negative and non-negative numbers
    for (int i = 0; i < n; ++i) {
        if (arr[i] < 0) {
            neg[negCount++] = arr[i];
        } else {
            nonNeg[nonNegCount++] = arr[i];
        }
    }

    // Calculate formula up to the minimum of negCount and nonNegCount
    int p = (negCount < nonNegCount) ? negCount : nonNegCount;
    for (int i = 0; i < p; ++i) {
        sum += neg[i] * nonNeg[i];
    }

    return sum;
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
