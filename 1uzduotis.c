/*
Gustas Griežė Programų sistemos 1 grupė 1 pogrupis
Užduotis:
    Įvesti sveiką skaičių G.
    Įvesti sveikų skaičių seką, kurios pabaiga žymima skaičiumi G.
    Išvesti visų įvestų narių skaičių, teigiamų narių skaičių ir neigiamų narių sumą bei
    sandaugą (arba atitinkamą pranešimą, jeigu tokių nėra)
*/

#include <stdio.h>

int main()
{
    double G_double, tempNum;
    int G, number;
    int totalCount = 0, positiveCount = 0, negativeSum = 0, negativeProduct = 1;
    int inputValid, hasNegative = 0, hasPositive = 0;

    printf("In this program you enter an integer, then you will enter a sequence of integers, the end of which is marked with the number you entered at the beginning.\n");
    printf("Then it will:\n1. Output the number of all entered members\n2. Number of positive members\n3. Sum of negative members\n4. The product of negative\n\n");

    printf("Enter an integer: ");
    while(scanf("%lf", &G_double) != 1 || G_double != (int)G_double)
    {
        printf("Invalid input. Please enter an integer: ");
        while(getchar() != '\n'); // Clear input
    }
    printf("\nThe number has been successfully entered!\n");
    G = (int) G_double;

    printf("\nEnter a sequence of integers ending with %d: ", G);
    while(1)
    {
        if(scanf("%lf", &tempNum) != 1 || tempNum != (int)tempNum)
        {
            printf("Invalid input. Please enter an integer: ");
            while(getchar() != '\n'); // Clear input
            continue;
        }
        number = (int) tempNum;
        printf("\nThe number %d has been successfully entered!\n", number);

        totalCount++;

        if(number > 0)
        {
            hasPositive = 1;
            positiveCount++;
        }
        else if(number < 0)
        {
            hasNegative = 1;
            negativeSum += number;
            negativeProduct *= number;
        }

        if(number == G)
        {
            break;
        }
        printf("Enter the next integer: ");
    }

    printf("\n--------Results--------");
    printf("\nNumber of all entered members: %d\n", totalCount);

    if(hasPositive)
    {
        printf("Number of positive members: %d\n", positiveCount);
    }
    else
    {
        printf("There were no positive integers entered.\n");
    }

    if(hasNegative)
    {
        printf("Sum of negative members: %d\n", negativeSum);
        printf("Product of negative members: %d\n", negativeProduct);
    }
    else
    {
        printf("There where no negative numbers entered, as a result there they don't have a sum or a product.\n");
    }

    return 0;
}
