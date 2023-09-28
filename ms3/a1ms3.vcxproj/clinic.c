/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : ilhyun cho
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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int flag = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            displayPatientData(&patient[i], fmt);
            flag++;
        }
    }

    if (flag == 0)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int option;

    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &option);
        clearInputBuffer();

        switch (option)
        {
        case 1: searchPatientByPatientNumber(patient, max);
            suspend();
            break;
        case 2: searchPatientByPhoneNumber(patient, max);
            suspend();
            break;
        }
    } while (option != 0);
    printf("\n");
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int room = -1;
    int i;

    for (i = 0; i < max; i++)
    {
        if (room == -1 && patient[i].patientNumber == 0)
        {
            room = i;
        }
    }

    if (room != -1)
    {
        patient[room].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[room]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int patientNum;
    int index;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);
    printf("\n");

    if (index != -1)
    {
        menuPatientEdit(&patient[index]);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");;
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int patientNum;
    char aswer;
    int index;

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index == -1)
    {
        printf("\n");
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        printf("\n");
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        aswer = inputCharOption("yn");

        if (aswer == 'y')
        {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    int allRecs = 1;
    int includeDateField = 1;
    int i;
    int index;

    displayScheduleTableHeader(&data->appointments->date, allRecs);

    bubbleSort(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);

            if (index >= 0)
            {
                displayScheduleData(&data->patients[index], &data->appointments[i], includeDateField);
            }
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int allRecs = 0;
    int includeDateField = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    struct Date date = { 0 };
    int i;
    int index;

    printf("Year        : ");
    year = inputIntPositive();
    printf("Month (%d-%d): ", JAN, DEC);
    month = inputIntRange(JAN, DEC);

    if (month == 2)
    {

        if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0)
        {
            printf("Day (1-29)  : ");
            day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            day = inputIntRange(1, 28);
        }
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        printf("Day (1-31)  : ");
        day = inputIntRange(1, 31);
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        printf("Day (1-30)  : ");
        day = inputIntRange(1, 30);
    }
    printf("\n");

    date.year = year;
    date.month = month;
    date.day = day;

    displayScheduleTableHeader(&date, allRecs);

    bubbleSort(data->appointments, data->maxAppointments);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0 &&
            data->appointments[i].date.year == year &&
            data->appointments[i].date.month == month &&
            data->appointments[i].date.day == day)
        {
            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[index], &data->appointments[i], includeDateField);
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appoint, int maxApp, struct Patient* pat, int maxPat)
{
    int input = 0;
    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int min = 0;
    int flag1, flag2;
    int hourToMin = 0;
    int i;

    printf("Patient Number: ");
    input = inputIntPositive();
    do
    {
        flag1 = 0;
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (%d-%d): ", JAN, DEC);
        month = inputIntRange(JAN, DEC);
        if (month == 2)
        {

            if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0)
            {
                printf("Day (1-29)  : ");
                day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                day = inputIntRange(1, 28);
            }
        }
        else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            printf("Day (1-31)  : ");
            day = inputIntRange(1, 31);
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            printf("Day (1-30)  : ");
            day = inputIntRange(1, 30);
        }

        do
        {
            flag2 = 0;
            printf("Hour (%d-%2d)  : ", TIME_START, HOUR_END);
            hour = inputIntRange(TIME_START, HOUR_END);
            printf("Minute (%d-%2d): ", TIME_START, MIN_END);
            min = inputIntRange(TIME_START, MIN_END);
            for (i = 0; i < maxApp; i++)
            {
                if (appoint[i].patientNumber != 0)
                {
                    if (appoint[i].date.year == year && appoint[i].date.month == month && appoint[i].date.day == day &&
                        appoint[i].time.hour == hour && appoint[i].time.min == min)
                    {
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        flag1 = 1;
                    }
                }
            }

            hourToMin = hour * 60 + min;
            if (hourToMin % INTERVAL != 0 || hourToMin < START * 60 || hourToMin > END * 60)
            {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in %d minute intervals.\n\n", START, END, INTERVAL);
                flag2 = 1;
            }
        } while (flag2);
    } while (flag1);

    for (i = 0; i < maxApp && flag1 == 0; i++)
    {
        if (appoint[i].patientNumber < 1)
        {
            appoint[i].patientNumber = input;
            appoint[i].date.year = year;
            appoint[i].date.month = month;
            appoint[i].date.day = day;
            appoint[i].time.hour = hour;
            appoint[i].time.min = min;
            flag1 = 1;
        }
    }
    printf("\n*** Appointment scheduled! ***\n\n");
}


// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoint, int maxApp, struct Patient* pat, int maxPat)
{
    int input;
    int index;
    int answer;
    int i;
    int number;
    int year = 0;
    int month = 0;
    int day = 0;

    printf("Patient Number: ");
    input = inputIntPositive();
    index = findPatientIndexByPatientNum(input, pat, maxPat);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (%d-%d): ", JAN, DEC);
        month = inputIntRange(JAN, DEC);

        if (month == 2)
        {

            if (((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0)
            {
                printf("Day (1-29)  : ");
                day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                day = inputIntRange(1, 28);
            }
        }
        else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            printf("Day (1-31)  : ");
            day = inputIntRange(1, 31);
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            printf("Day (1-30)  : ");
            day = inputIntRange(1, 30);
        }

        printf("\n");
        printf("Name  : %s\n", pat[index].name);
        printf("Number: %05d\n", pat[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(pat[index].phone.number);
        printf(" (%s)\n", pat[index].phone.description);
        number = pat[index].patientNumber;
        printf("Are you sure you want to remove this appointment (y,n): ");
        answer = inputCharOption("yn");
        if (answer == 'y')
        {
            for (i = 0; i < maxApp; i++)
            {
                if (appoint[i].patientNumber == number && appoint[i].date.year == year && appoint[i].date.month == month && appoint[i].date.day == day)
                {
                    appoint[i].patientNumber = 0;
                }
            }
            printf("\nAppointment record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)//------------------------------------------------
{
    int patientNum;
    int index;

    printf("\n");
    printf("Search by patient number: ");
    patientNum = inputIntPositive();// 0
    printf("\n");
    index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
    }
    else
    {
        printf("*** No records found ***\n\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    char phoneNum[PHONE_LEN + 1];
    int flag = 0;

    printf("\n");
    printf("Search by phone number: ");
    inputCString(phoneNum, PHONE_LEN, PHONE_LEN);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(phoneNum, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            flag++;
        }
    }

    if (!flag)
    {
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int maxNum = 0;

    for (i = 0; i < max; i++)
    {
        if (maxNum < patient[i].patientNumber)
        {
            maxNum = patient[i].patientNumber;
        }
    }
    return maxNum + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;
    int index = -1;

    for (i = 0; i < max; i++)
    {

        if (patient[i].patientNumber == patientNumber)
        {
            index = i;
        }
    }
    return index;
}


//////////////////////////////////////
// MY FUNCTIONS
//////////////////////////////////////
void userInputPhone(char* num)
{
    char input[777 + 1] = { 0 };
    int repeat;
    size_t count = 0;

    do
    {
        repeat = 0;
        scanf("%s", input);
        clearInputBuffer();
        count = strlen(input);

        if (count != 10)
        {
            printf("Invalid %d-digit number! Number: ", PHONE_LEN);
            repeat = 1;
        }
    } while (repeat);
    strcpy(num, input);
}

void swap(struct Appointment* a, struct Appointment* b)
{
    struct Appointment temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(struct Appointment* app, int appCount)
{
    int i;
    int j;

    for (i = 0; i < appCount - 1; i++)
    {
        for (j = 0; j < appCount - i - 1; j++)
        {
            if (app[j].date.year > app[j + 1].date.year)
            {
                swap(&app[j], &app[j + 1]);
            }

            if (app[j].date.year == app[j + 1].date.year && app[j].date.month > app[j + 1].date.month)
            {
                swap(&app[j], &app[j + 1]);
            }

            if (app[j].date.year == app[j + 1].date.year && app[j].date.month == app[j + 1].date.month && app[j].date.day > app[j + 1].date.day)
            {
                swap(&app[j], &app[j + 1]);
            }

            if (app[j].date.year == app[j + 1].date.year && app[j].date.month == app[j + 1].date.month && app[j].date.day == app[j + 1].date.day &&
                app[j].time.hour > app[j + 1].time.hour)
            {
                swap(&app[j], &app[j + 1]);
            }

            if (app[j].date.year == app[j + 1].date.year && app[j].date.month == app[j + 1].date.month && app[j].date.day == app[j + 1].date.day &&
                app[j].time.hour == app[j + 1].time.hour && app[j].time.min > app[j + 1].time.min)
            {
                swap(&app[j], &app[j + 1]);
            }
        }
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)0
void inputPhoneData(struct Phone* phone)
{
    int option;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    option = inputIntRange(1, 4);


    switch (option)
    {
    case 1: strcpy(phone->description, "CELL");
        break;

    case 2: strcpy(phone->description, "HOME");
        break;

    case 3: strcpy(phone->description, "WORK");
        break;

    case 4: strcpy(phone->description, "TBD");
        break;
    }

    if (option != 4)
    {
        printf("\n");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        userInputPhone(phone->number);
        printf("\n");
    }
    else
    {
        printf("\n");
    }
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    struct Patient pat = { 0 };

    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &pat.patientNumber, pat.name, pat.phone.description, pat.phone.number) >= 3)
        {
            if (strcmp(pat.phone.description, "TBD") == 0)
            {
                pat.phone.number[0] = '\0';
            }

            patients[i] = pat;
            i++;

        }
        if (fclose(fp) == EOF)
        {
            printf("*** ERROR : Fail to file close ***\n\n");
        }
    }

    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
    }
    return i;
}// C string array 초기화 하려면, 0번째 index에 '\0' or 0을 넣어준다.


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;
    struct Appointment app = { 0 };

    FILE* fp = NULL;
    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d", &app.patientNumber, &app.date.year, &app.date.month, &app.date.day, &app.time.hour, &app.time.min) == 6)
        {
            appoints[i] = app;
            i++;
        }
        if (fclose(fp) == EOF)
        {
            printf("*** ERROR : Fail to file close ***\n\n");
        }
    }
    else
    {
        printf("Failed to open file %s!!!\n", datafile);
        printf("Program is exiting...\n");
    }
    return i;
}