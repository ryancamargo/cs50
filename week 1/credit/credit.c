#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    long card = get_long("Number: ");
    int count = 0;
    count = (card == 0) ? 1 : log10(card) + 1;
    printf("Number of digits: %d\n", count);

    long a1 = card / 10;
    long b1 = card % 10; // The "b" are the remaining \o/

    long a2 = a1 / 10;
    long b2 = a1 % 10;

    long a3 = a2 / 10;
    long b3 = a2 % 10;

    long a4 = a3 / 10;
    long b4 = a3 % 10;

    long a5 = a4 / 10;
    long b5 = a4 % 10;

    long a6 = a5 / 10;
    long b6 = a5 % 10;

    long a7 = a6 / 10;
    long b7 = a6 % 10;

    long a8 = a7 / 10;
    long b8 = a7 % 10;

    long a9 = a8 / 10;
    long b9 = a8 % 10;

    long a10 = a9 / 10;
    long b10 = a9 % 10;

    long a11 = a10 / 10;
    long b11 = a10 % 10;

    long a12 = a11 / 10;
    long b12 = a11 % 10;

    long a13 = a12 / 10;
    long b13 = a12 % 10;

    long a14 = a13 / 10;
    long b14 = a13 % 10;

    long a15 = a14 / 10;
    long b15 = a14 % 10;

    long a16 = a15 / 10;
    long b16 = a15 % 10;

    /* funcionou para 16 digitos    printf("%li\n", a14);

       funcionou para 15 digitos    printf("%li\n", a13);

       funcionou para 14 digitos    printf("%li\n", a12);

       funcionou para 13 digitos    printf("%li\n", a11); */

    // First: to get every other digit, starting with the number's second-to-last digit ---> the "b" that are PAR

    // Second: to multiply each of those digits by 2

    long x1 = b2 * 2;
    long x2 = b4 * 2;
    long x3 = b6 * 2;
    long x4 = b8 * 2;
    long x5 = b10 * 2;
    long x6 = b12 * 2;
    long x7 = b14 * 2;
    long x8 = b16 * 2;

    // Third: to add those products DIGITS (not the products themselves) together

    long d1 = x1 / 10;
    long d2 = x1 % 10;
    long d3 = x2 / 10;
    long d4 = x2 % 10;
    long d5 = x3 / 10;
    long d6 = x3 % 10;
    long d7 = x4 / 10;
    long d8 = x4 % 10;
    long d9 = x5 / 10;
    long d10 = x5 % 10;
    long d11 = x6 / 10;
    long d12 = x6 % 10;
    long d13 = x7 / 10;
    long d14 = x7 % 10;
    long d15 = x8 / 10;
    long d16 = x8 % 10;

    long sum = d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8 + d9 + d10 + d11 + d12 + d13 + d14 + d15 + d16;

    // Fourth: add that sum to the sum of the digits that weren't multiplied by 2 (starting from the end)

    long result = sum + b1 + b3 + b5 + b7 + b9 + b11 + b13 + b15;

    // printf("result: %li\n", result);

    // Fifth: the final result should have 0 as a remaining of modulo 10 -> result % 10 = 0 -> VALID card

    if (result % 10 == 0 && count >= 13)
    {
        // VISA -> all start with 4 and have 13 and 16-digit numbers
        if (b16 == 4 || b13 == 4)
        {
            printf("VISA\n");
        }

        // AMEX -> starts with 34 or 37 and have 15-digit numbers
        else if (a13 == 37 || a13 == 34)
        {
            printf("AMEX\n");
        }

        // MASTERCARD -> starts with 51,52,53,54,55 and have 16-digit numbers
        else if (a14 == 51 || a14 == 52 || a14 == 53 || a14 == 54 || a14 == 55 || a14 == 22 || a14 == 23)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // INVALID -> when the credit card desobeys the Luhn Algorithm
    else
    {
        printf("INVALID\n");
    }
}