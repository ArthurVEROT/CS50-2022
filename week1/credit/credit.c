#include <cs50.h>
#include <stdio.h>
#include <math.h>

int WhatDigit(long number, int n);

int main(void)
{
    // Credit card number
    long cardNumber = get_long("What is the card number you want to check ?: ");
    printf("Number : %li\n", cardNumber);

    //Total number of digit
    double cardLength = trunc(log10(cardNumber) + 1);

    //First digit
    int first = WhatDigit(cardNumber, cardLength - 1);

    //First 2 digit
    int first2 = cardNumber / pow(10, cardLength - 2);

    // Luhn’s Algorithm
    // Every two digit from the second last digit
    int EveryTwox2 = 0;
    int SumEveryTwox2 = 0;
    long cardLengthTrunc = trunc(cardLength / 2);
    for (int i = 0, x = 1; i < cardLengthTrunc; ++i, x = x + 2)
    {
        EveryTwox2 = (WhatDigit(cardNumber, x)) * 2;

        if (EveryTwox2 < 10)
        {
            SumEveryTwox2 = SumEveryTwox2 + EveryTwox2;
        }
        else
        {
            int UnitsDigit = WhatDigit(EveryTwox2, 0);
            int SmallSum = 1 + UnitsDigit;

            SumEveryTwox2 = SumEveryTwox2 + SmallSum;
        }
    }

    // Every two digit from the last digit
    int EveryOtherTwo = 0;
    int SumEveryOtherTwo = 0;
    long cardLengthCeil = ceil(cardLength / 2);
    for (int j = 0, y = 0; j < cardLengthCeil; ++j, y = y + 2)
    {
        EveryOtherTwo = WhatDigit(cardNumber, y);
        SumEveryOtherTwo = SumEveryOtherTwo + EveryOtherTwo;
    }

    // Add the two sums from the Luhn’s Algorithm
    int VerifyNumber = SumEveryTwox2 + SumEveryOtherTwo;

    // Condition if card number is valid, AMEX, Mastercard or Visa
    if ((VerifyNumber % 10) != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // Conditions : AMEX or Mastercard or Visa
        if (cardLength == 15 && (first2 == 34 || first2 == 37))
        {
            printf("AMEX\n");
        }
        else if (cardLength == 16 && (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((cardLength == 13 || cardLength == 16) && first == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

//Function : Get a specific digit from an number (0 = last number, 0+1 = second last, etc)
int WhatDigit(long number, int n)
{
    long removeN = trunc(number / pow(10, n));
    int selectDigit = removeN % (10);
    return selectDigit;
}