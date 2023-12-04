#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include "Algorithm/SearchingAlgorithm.h"
#include "Algorithm/SortingAlgorithm.h"


// Define username and password
#define USERNAME "user"
#define PASSWORD "123456"
#define MAX_EMPLOYEES 100
#define MAX_ROOMS 100


// Enum for system states
enum SystemState {
    LOGIN,
    MAIN_PANEL,
    ADMIN,
    RECEPTION,
    EXIT
};

// Structure for Employee
struct Employee {
    int ID;
    char name[50];
    int age;
    char gender[10];
    char job[50];
    float salary;
    char phone[15];
    char address[100];
    char email[50];
};

// Structure for Room
struct Room {
    int roomNumber;
    char status[20]; // available or occupied
    char cleaningStatus[20]; // clean or dirty
    float price;
    char bedType[20]; // single or double
    float discountPercentage;
};


// Function declarations
void login(enum SystemState *currentState);
void showMainPanel(enum SystemState *currentState);
void adminLogin();
void receptionLogin();
void addEmployee();
void addRoom();


int main() {
    printf("***   Welcome to XMUM Hotel!   ***\n");

    enum SystemState currentState = LOGIN;

    // Start the system loop
    while (currentState != EXIT) {
            int cho;
        switch (currentState) {
            case LOGIN:
                login(&currentState);
                break;
            case MAIN_PANEL:
                showMainPanel(&currentState);
                break;
            case ADMIN:
                adminLogin();
                printf("\nTask Finshed!\n");
                printf("\n1.Back to Admin panel\n");
                printf("2.Back to Main panel");
                printf("\n3.EXIT\n");
                printf("\nEnter your choice: ");
                scanf("%d", &cho);

                if(cho == 1)
                    currentState = ADMIN; // Go back to the main panel after admin tasks
                else if(cho == 2)
                    currentState = MAIN_PANEL;
                else if(cho == 3)
                    currentState = EXIT;
                else
                    printf("Invalid choice. Please enter a valid option.\n");
                break;
            case RECEPTION:
                receptionLogin();
                printf("\nTask Finshed!\n");
                printf("\n1.Back to Main panel\n");
                printf("2.EXIT");
                printf("\nEnter your choice: ");
                scanf("%d", &cho);
                if(cho == 1)
                    currentState = MAIN_PANEL; // Go back to the main panel after admin tasks
                else if(cho == 2)
                    currentState = EXIT;
                else
                    printf("Invalid choice. Please enter a valid option.\n");
                break;
            default:
                break;
        }
    }

    printf("\nExiting the system. Goodbye!\n");

    return 0;
}


// User login function
void login(enum SystemState *currentState) {
    char username[20];
    char password[20];

    printf("\n=== User Login ===\n");
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    // Validate username and password
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Login successful!\n");
        *currentState = MAIN_PANEL;  // Set the state to the main panel after successful login
    } else {
        printf("Login failed. Incorrect username or password.\n");
        exit(1);
    }
}


// Display the main control panel
void showMainPanel(enum SystemState *currentState) {
    int choice;
    system("cls");
    // Display options
    printf("\n=== Main Panel ===\n");
    printf("1. Login as Admin\n");
    printf("2. Login as Reception Staff\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    // Perform the corresponding action based on user choice
    switch (choice) {
        case 1:
            *currentState = ADMIN;
            break;
        case 2:
            *currentState = RECEPTION;
            break;
        case 3:
            *currentState = EXIT;
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
    }
}


// Admin login function
void adminLogin() {
    int choice;
    system("cls");
    printf("****** Dear admin, welcome to the management page! ******\n");
    printf("\n=== Admin Panel ===\n");
    printf("Logged in as Admin. Performing admin tasks\n");
    printf("Now the task can be chosen by admin are as follows,\n1. Add Employee.\n2. Add Room.\n");
    printf("Enter your task to be chosen: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            addRoom();
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");

}
}


// Reception staff login function
void receptionLogin() {
    system("cls");
    printf("****** Dear Reception Staff, welcome to the Front Desk Management page! ******\n");
    printf("\n=== Reception Panel ===\n");
    printf("Logged in as Reception Staff. Performing reception tasks...\n");
    // Perform reception staff tasks here
}


void addEmployee() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    char choice;

    do {
        if (numEmployees >= MAX_EMPLOYEES) {
            printf("Maximum number of employees reached.\n");
            break;
        }

        printf("\n=== Add Employee ===\n");
        printf("Enter Employee ID: ");
        scanf("%d", &employees[numEmployees].ID);

        printf("Enter Name: ");
        scanf("%s", employees[numEmployees].name);

        printf("Enter Age: ");
        scanf("%d", &employees[numEmployees].age);

        printf("Enter Gender: ");
        scanf("%s", employees[numEmployees].gender);

        printf("Enter Job: ");
        scanf("%s", employees[numEmployees].job);

        printf("Enter Salary: ");
        scanf("%f", &employees[numEmployees].salary);

        printf("Enter Phone: ");
        scanf("%s", employees[numEmployees].phone);

        printf("Enter Address: ");
        scanf("%s", employees[numEmployees].address);

        printf("Enter Email: ");
        scanf("%s", employees[numEmployees].email);

        numEmployees++; // Increment employee count

        printf("\nEmployee is added successfully!\nDo you want to add another employee? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');

    printf("\nThe whole information of added employees is shown: \n");
    for (int i = 0; i < numEmployees; ++i) {
        printf("\nEmployee %d\n", i + 1);
        printf("Employee ID: %d\n", employees[i].ID);
        printf("Name: %s\n", employees[i].name);
        printf("Age: %d\n", employees[i].age);
        printf("Gender: %s\n", employees[i].gender);
        printf("Job: %s\n", employees[i].job);
        printf("Salary: %.2f\n", employees[i].salary);
        printf("Phone: %s\n", employees[i].phone);
        printf("Address: %s\n", employees[i].address);
        printf("Email: %s\n", employees[i].email);
    }
}


void addRoom() {
    struct Room rooms[MAX_ROOMS];
    int numRooms = 0;
    char choice;

    do {
        if (numRooms >= MAX_ROOMS) {
            printf("Maximum number of rooms reached.\n");
            break;
        }

        printf("\n=== Add Room ===\n");
        printf("Enter Room Number: ");
        scanf("%d", &rooms[numRooms].roomNumber);

        printf("Enter Status (available or occupied): ");
        scanf("%s", rooms[numRooms].status);

        printf("Enter Cleaning Status (clean or dirty): ");
        scanf("%s", rooms[numRooms].cleaningStatus);

        printf("Enter Price: ");
        scanf("%f", &rooms[numRooms].price);

        printf("Enter Bed Type (single or double): ");
        scanf("%s", rooms[numRooms].bedType);

        printf("Enter Discount Percentage: ");
        scanf("%f", &rooms[numRooms].discountPercentage);

        numRooms++; // Increment room count

        printf("\nDo you want to add another room? (Y/N): ");
        scanf(" %c", &choice);
    } while (choice == 'Y' || choice == 'y');


    printf("\nRoom(s) added successfully!\n");
    for (int i = 0; i < numRooms; ++i) {
        printf("\nRoom %d\n", i + 1);
        printf("Room Number: %d\n", rooms[i].roomNumber);
        printf("Status: %s\n", rooms[i].status);
        printf("Cleaning Status: %s\n", rooms[i].cleaningStatus);
        printf("Price: %.2f\n", rooms[i].price);
        printf("Bed Type: %s\n", rooms[i].bedType);
        printf("Discount Percentage: %.2f\n", rooms[i].discountPercentage);
    }

}
