/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : ILHYUN CHO
Student ID#: 116342221
Email      : icho8@myseneca.ca
Section    : ZCC

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "core.h"

// Clear the standard input buffer
void clearInputBuffer(void)// Clear the standard input buffer
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

void suspend(void)// Wait for user to input the "enter" key to continue
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

int inputInt(void)// This function guarantees that an integer value is entered and returned. If an invalid value is entered, an error message would be displayed.
{
    char cha;
    int value;
    int repeat = 0;

    do
    {
        repeat = 0;
        scanf("%d%c", &value, &cha);

        if (cha != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
            repeat = 1;
        }
    } while (repeat);

    return value;
}

int inputIntPositive(void)// This function guarantees a positive integer value is entered and returned. If a zero or a negative value in entered, an error message would be displayed.
{
    int value = 0;
    int repeat = 0;

    do
    {
        repeat = 0;
        value = inputInt();

        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
            repeat = 1;
        }
    } while (repeat);

    return value;
}

int inputIntRange(int lowerRange, int upperRange)// This function guarantees that an integer value is entered within the range (inclusive) and returned. If a value from outside the range is entered, display an error message and continue to prompt until a value in the given range is entered.
{
    int value = 0;
    int repeat = 0;

    do
    {
        repeat = 0;
        value = inputInt();

        if (value < lowerRange || value > upperRange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerRange, upperRange);
            repeat = 1;
        }
    } while (repeat);
   
    return value;
}

char inputCharOption(char options[])// This function guarantees a single character value is entered within the list of valid characters and returned. If an entered character is not in the list of valid characters, display an error message and prompt again.

{
    char cha;
    int count = 0;
    int i;
    int repeat = 0;

    do
    {
        repeat = 0;
        scanf(" %c", &cha);

        for (i = 0; options[i] != '\0'; i++)
        {

            if (cha == options[i])
            {
                count++;
            }
        }

        if (count ==0)
        {
            printf("ERROR: Character must be one of [%s]: ", options);
            clearInputBuffer();
            repeat = 1;
        }
    } while (repeat);

    return cha;
}

void inputCString(char* str, int minChar, int maxChar)// This function guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments.
{
    int repeat;
    int i;
    int count;

    //local Cstring Array needs.
    char string[777 + 1] = { 0 };

    do
    {
        repeat = 0;
        clearInputBuffer();
        scanf("%777[^\n]", string);
        count = 0;
        for (i = 0; string[i] != '\0'; i++)
        {
            count++;
        }

        if (minChar == maxChar && (count < minChar || count >maxChar))
        {
            printf("ERROR: String length must be exactly %d chars: ", minChar);
            repeat = 1;
        }
        else if ((minChar != maxChar) && count < minChar)
        {
            printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
            repeat = 1;
        }
        else if ((minChar != maxChar) && count > maxChar)
        {
            printf("ERROR: String length must be no more than %d chars: ", maxChar);
            repeat = 1;
        }
        else
        {
            for (i = 0; i < count; i++)
            {
                str[i] = string[i];
            }
        }
        string[0] = '\0';// array initializing

    } while (repeat);

}

void displayFormattedPhone(const char* number)// The purpose of this function is to display an array of 10-character digits as a formatted phone number.
{
    int len = 0;
    int i;

    while (number != '\0' && isdigit(number[len]))
    {
        len++;
    }

    if (len == 10)
    {
        i = 0;
        printf("(");
        while (i < 3)
        {
            printf("%c", number[i]);
            i++;
        }
        printf(")");
        while (i < 6)
        {
            printf("%c", number[i]);
            i++;
        }
        printf("-");
        while (i < 10)
        {
            printf("%c", number[i]);
            i++;
        }
    }
    else
    {
        printf("(___)___-____");
    }
}
