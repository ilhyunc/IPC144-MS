/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : ILHYUN CHO
Student ID#: 116342221
Email      : icho8@myseneca.ca
Section    : ZCC
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H// ifndef = if not define
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #1 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

void clearInputBuffer(void);// Clear the standard input buffer

void suspend(void);// Wait for user to input the "enter" key to continue



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt(void);//This function, enter an integer value and return it. If enter an invalid value, an error message is displayed.

int inputIntPositive(void);//This function enter a positive integer value and return it. If enter a zero or a negative value, an error message is displayed.

int inputIntRange(int lowBound, int upBound);//This function enter and return a single character value within the list of valid characters. If entered character is not in the list of valid characters, display an error message and prompt again

char inputCharOption(char str[]);// This function guarantees a single character value is entered within the list of valid characters and returned. If an entered character is not in the list of valid characters, display an error message and prompt again.

void inputCString(char* str, int minChar, int maxChar);// This function guarantees a C string value is entered containing the number of characters within the range specified by the 2nd and 3rd arguments.

void displayFormattedPhone(const char* num);// The purpose of this function is to display an array of 10-character digits as a formatted phone number


// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H