#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX_USERS 10

int i,j;
struct FitnessRecord {
    int userID;
    char userName[100];
    float dailyCalories;
    float totalCalories;
    int exerciseDuration; // in minutes
};
struct FitnessRecord records[MAX_USERS]; // Instance

int main(void){
    gotoxy(50,3);
    for(i =0;i < 26;i++){
        printf("%c",219);
    }
    gotoxy(50,4);
    printf("%c                        %c",219,219);
    gotoxy(50,5);
    printf("%c Fitness Tracker System %c",219,219);
    gotoxy(50,6);
    printf("%c                        %c",219,219);
    gotoxy(50,7);
    for(i =0;i < 26;i++){
        printf("%c",219);
    }
    gotoxy(49,10);
    printf("Press Enter to Continue...");
    getch();
    loading();
    mainMenu();
    return 0;
}

bool isValidIntInput(int *value,struct FitnessRecord records[MAX_USERS], int numUsers) {
    if (scanf("%d", value) == 1) {
        // Integer input, clear the input buffer
        while (getchar() != '\n');
        for (i = 0; i < numUsers; i++) {
            if (*value == records[i].userID) {
                printf("User with ID %d already exists. Please enter a different ID.\n", *value);
                return false;
            }
        }
        return true;
    } else {
        // Invalid input, clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a valid integer.\n");
        return false;
    }
}

bool isValidFloatInput(float *value) {
    if (scanf("%f", value) == 1) {
        // Float input, clear the input buffer
        while (getchar() != '\n');
        return true;
    } else {
        // Invalid input, clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a valid float.\n");
        return false;
    }
}

bool isValidStringInput(char *value, int maxLength) {
    if (scanf("%s", value) == 1) {
        // String input, clear the input buffer
        while (getchar() != '\n');
        return true;
    } else {
        // Invalid input, clear the input buffer
        while (getchar() != '\n');
        printf("Invalid input. Please enter a valid string.\n");
        return false;
    }
}

// Function to input daily exercise
void inputDailyExercise(struct FitnessRecord records[MAX_USERS], int *numUsers) {
    system("cls");
    printf("Enter userID: ");
    while (!isValidIntInput(&(records[*numUsers].userID),records,*numUsers)) {
        printf("Enter userID: ");
    }

    printf("Enter userName: ");
    while (!isValidStringInput(records[*numUsers].userName, sizeof(records[*numUsers].userName))) {
        printf("Enter userName: ");
    }

    printf("Enter dailyCalories: ");
    while (!isValidFloatInput(&(records[*numUsers].dailyCalories))) {
        printf("Enter dailyCalories: ");
    }

    printf("Enter exerciseDuration (in minutes): ");
    while (!isValidIntInput(&(records[*numUsers].exerciseDuration),records,*numUsers)) {
        printf("Enter exerciseDuration: ");
    }

    // Initialize total calories to 0
    records[*numUsers].totalCalories = 0;

    // Update total calories
    records[*numUsers].totalCalories += records[*numUsers].dailyCalories;

    (*numUsers)++;
    printf("Record Added\n");
    printf("\nPress Enter to go back...");
    getch();
    loading();

}

// Function to view fitness statistics
void viewFitnessStatistics(struct FitnessRecord records[MAX_USERS], int numUsers) {
    gotoxy(1,1);
    printf("\nFitness Statistics\n\n");

    printf("%-10s  %-20s  %-15s  %-10s \n", "UserID", "UserName", "Total Calories", "Duration");


    for (int i = 0; i < numUsers; i++) {
        printf(" %-10d  %-20s  %-15.2f  %-10d \n", records[i].userID, records[i].userName, records[i].totalCalories, records[i].exerciseDuration);
    }
    printf("\n\nPress Enter to go back....");
    getch();
    system("cls");
}

// Function to read fitness records from file
int readFitnessRecords(struct FitnessRecord records[MAX_USERS]) {
    FILE *file = fopen("fitness_records.bin", "rb");
    if (file == NULL) {
        // File does not exist or cannot be opened
        return 0;
    }

    int numUsers;
    fread(&numUsers, sizeof(int), 1, file);

    fread(records, sizeof(struct FitnessRecord), numUsers, file);

    fclose(file);
    return numUsers;
}

// Function to write fitness records to file
void writeFitnessRecords(struct FitnessRecord records[MAX_USERS], int numUsers) {
    FILE *file = fopen("fitness_records.bin", "wb");
    if (file == NULL) {
        // Cannot create or write to the file
        printf("Error: Unable to write to the file.\n");
        return;
    }

    fwrite(&numUsers, sizeof(int), 1, file);
    fwrite(records, sizeof(struct FitnessRecord), numUsers, file);

    fclose(file);
}

// using sleep to for loading
void loading(){
    gotoxy(60,15);
    printf("Loading");
    gotoxy(50,17);
    for (i = 0;i < 30;i++){
        Sleep(30);
        printf("%c",219);
    }
    system("cls");
}

// Show exit
void quit(){
    system("cls");

    printf("Saved\n");
    printf("Exited Successfully\n");
    exit(1);
}


// Main Menu
void mainMenu(){
    system("cls");
    int choice, numUsers = 0;
    numUsers = readFitnessRecords(records);
    while(1){
        gotoxy(50,3);
        for(i =0;i < 30;i++){
            printf("%c",219);
        }
        gotoxy(50,4);
        printf("%c                            %c",219,219);
        gotoxy(50,5);
        printf("%c 1. Input Daily Exercise    %c",219,219);
        gotoxy(50,6);
        printf("%c 2. View Fitness Statistics %c",219,219);
        gotoxy(50,7);
        printf("%c 3. Exit                    %c",219,219);
        gotoxy(50,8);
        printf("%c    Option:                 %c",219,219);
        gotoxy(50,9);
        printf("%c                            %c",219,219);
        gotoxy(50,10);
        for(i =0;i < 30;i++){
            printf("%c",219);
        }
        gotoxy(63,8);

        scanf("%d",&choice);
        switch(choice){
            case 1:{
                loading();
                inputDailyExercise(&records, &numUsers);//Input function
                break;
            }
            case 2:{
                loading();
                viewFitnessStatistics(records, numUsers);//Fitness Stats
                break;
            }
            case 3:{
                writeFitnessRecords(records, numUsers);
                quit();
            }
            default:{
                printf("Invalid Input");
            }
        }
    }
}

// moving cursor
void gotoxy(int x,int y){
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

