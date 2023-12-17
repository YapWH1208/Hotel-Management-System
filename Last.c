#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

// Define the username and password
#define USERNAME "user"
#define PASSWORD "123456"

//Define the folder and files' name
#define FOLDER_NAME "data_folder"
#define FILE_NAME "customer_data.txt"
#define ROOM_FILE_NAME "roominfo.txt"
#define EMP_FILE_NAME "empinfo.txt"

#define MAX_CUSTOMERS 100 // Create 100 customers available
#define MAX_ROOMS 100 // Create 100 rooms available
#define MAX_EMPLOYEES 100 // Create 100 employees available
#define MAX_INFO_LENGTH 50
#define MAX_LINE_LENGTH 1024

// Enum for system states
enum SystemState {
    LOGIN,
    MAIN_PANEL,
    ADMIN,
    RECEPTION,
    EXIT
};


// Customer structure to store customer information
typedef struct {
    char idType[20];
    int idNumber;
    char name[50];
    char gender[10];
    char country[50];
    int roomNumber;
    char checkInDateTime[20];
    char checkOutDateTime[20];
    int stayingDays;
    double totalAmount;
    double initialPayment;
    double pendingAmount;
    double deposit;
    int receiptNumber;
} Customer;


// Employee structure to store employee information
typedef struct {
    int ID;
    char Name[MAX_INFO_LENGTH];
    int Age;
    char Gender[MAX_INFO_LENGTH];
    char Job[MAX_INFO_LENGTH];
    char Salary[MAX_INFO_LENGTH];
    char Phone[MAX_INFO_LENGTH];
    char Address[MAX_INFO_LENGTH];
    char Email[MAX_INFO_LENGTH];
} Employee;


// Room structure to store room information
typedef struct {
    int roomNumber;
    char status[MAX_INFO_LENGTH];
    char cleaningStatus[MAX_INFO_LENGTH];
    float price;
    char bedType[MAX_INFO_LENGTH];
    float discount;
} Room;

// Function declarations
void login(enum SystemState *currentState);
void showMainPanel(enum SystemState *currentState);
void adminLogin();
void receptionLogin();
Customer createNewCustomer();
double calculatePendingAmount(double totalAmount, double initialPayment);
void saveToFile(Customer customers);
void createFolderAndFileIfNotExists();
void readFromFile(Customer customers[MAX_CUSTOMERS], int *numCustomers);
void readFromRoomFile(Room rooms[MAX_ROOMS], int *numRooms);
void printCustomerInfo(const Customer *customers);
void printRoomInfo(const Room *rooms);
void searchCustomerRoomNo(Customer customers[MAX_CUSTOMERS], int numCustomers);
void updateRoomStatus(Room rooms[MAX_ROOMS], int numRooms);
void updateStatus(Room rooms[MAX_ROOMS], int numRooms);
void updateCustomerInformation(Customer customers[MAX_CUSTOMERS], int numCustomers);
void deleteCustomers(Customer customers[MAX_CUSTOMERS], int numCustomers);
void printCheckoutForm(Customer customers[MAX_CUSTOMERS], int numCustomers, Room rooms[MAX_ROOMS], int numRooms);
void printInvoice(Customer customers[MAX_CUSTOMERS], int numCustomers, Room rooms[MAX_ROOMS], int numRooms);
int binarySearchCustomerID(int num, Customer customers[MAX_CUSTOMERS], int low, int high);
int binarySearchCRoomNo(int num, Customer customers[MAX_CUSTOMERS], int low, int high);
int binarySearchRRoomNo(int num, Room rooms[MAX_ROOMS], int low, int high) ;
void maxmin(Room rooms[], int i, int j, float *maxPrice, float *minPrice) ;
void selectionSortRoomPrice(Room rooms[MAX_ROOMS], int numRooms);
void selectionSortRoomNo(Room rooms[MAX_ROOMS], int numRooms);
void selectionSortCustomerID(Customer customers[MAX_CUSTOMERS], int numCustomers);
void selectionSortCustomerRNo(Customer customers[MAX_CUSTOMERS], int numCustomers);
void printAvailableRooms(Room rooms[MAX_ROOMS], int numRooms);
void merge(Room rooms[MAX_ROOMS], int left, int mid, int right);
void mergeSort(Room rooms[MAX_ROOMS], int left, int right);
void showSingleBedRoomsSortedByPrice(Room rooms[MAX_ROOMS], int numRooms);
void bubbleSort(Room rooms[MAX_ROOMS], int numRooms);
void showDoubleBedRoomsSortedByPrice(Room rooms[MAX_ROOMS], int numRooms);
int linearSearchCustomerByID(int num, Customer customers[MAX_CUSTOMERS], int numCustomers);
void searchCustomerByID(Customer customers[MAX_CUSTOMERS], int numCustomers);
void ede();
void dle();
void edr();
void bse();
void empinfo();
void roominfo();
void displayRoom(Room room);
void showAllRooms();
void showAllRoomsbyNumber();
void showAllRoomsbyPrice();
void showAllBookings();
void searchBooking();
void totalIncomePerDay();
void printReceipt();


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
            case RECEPTION:
                receptionLogin();
                printf("\nTask Finshed!\n");
                printf("\n1.Back to Main panel\n");
                printf("2.EXIT");
                printf("\nEnter your choice: ");
                scanf("%d", &cho);
                if(cho == 1)
                    currentState = MAIN_PANEL; // Go back to the main panel after reception tasks
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
    system("cls");
    char username[20];
    char password[20];

    printf("\n=== Admin Login Block ===\n");
    printf("Enter Admin username: ");
    scanf("%s", username);

    printf("Enter Admin password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Admin Login successful!\n");
        printf("The admin management page will appear.\n");
        sleep(3);

    } else {
        printf("Admin Login failed. Incorrect Admin username or password.\n");
        exit(1);
    }

    int choice;
    system("cls");
    printf("****** Dear admin, welcome to the Management page! ******\n");
    printf("\n=== Admin Panel ===\n");
    printf("Logged in to Admin.\nPerforming admin tasks:\n");
    printf("1. Show Employees' information and add new employee if needed\n"
           "2. Show Room information and add new room if needed\n"
           "3. Search The Employee\n"
           "4. Edit Employee data\n"
           "5. Delete Employee\n"
           "6. Edit the Room Information\n"
           "7. Show all Rooms\n"
           "8. Show all Rooms by number\n"
           "9. Show all Rooms by price\n"
           "10. All Booking Operations\n"
           "11. Search Booking\n"
           "12. Total Income per day\n"
           "13. Receipts\n"
           "14. Exit Admin Panel\n");
    printf("Enter your task to be chosen: ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            empinfo();
            break;
        case 2:
            roominfo();
            break;
        case 3:
            bse();
            break;
        case 4:
            ede();
            break;
        case 5:
            dle();
            break;
        case 6:
            edr();
            break;
        case 7:
            showAllRooms();
            break;
        case 8:
            showAllRoomsbyNumber();
            break;
        case 9:
            showAllRoomsbyPrice();
            break;
        case 10:
            showAllBookings();
            break;
        case 11:
            searchBooking();
            break;
        case 12:
            totalIncomePerDay();
            break;
        case 13:
            printReceipt();
            break;
        case 14:
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
    }
}


// Reception staff login function
void receptionLogin() {
    system("cls");

    char username2[20];
    char password2[20];

    printf("\n=== Reception Login Block ===\n");
    printf("Enter username: ");
    scanf("%s", username2);

    printf("Enter password: ");
    scanf("%s", password2);

    // Validate username and password
    if (strcmp(username2, USERNAME) == 0 && strcmp(password2, PASSWORD) == 0) {
        printf("Login successful!\n");
        printf("The reception control panel will appear.\n");
        sleep(3);
    } else {
        printf("Login failed. Incorrect username or password.\n");
        printf("Exiting the system.\n");
        exit(1);
    }
    // Create the customer data folder and file if they don't exist
    createFolderAndFileIfNotExists();

    // Ask the user if they want to return to the Reception Panel
    int returnToReceptionPanel = 1;
    while(returnToReceptionPanel == 1){

        system("cls");

        // Perform reception staff tasks here
        printf("****** Dear Receptionist, welcome to the Management page! ******\n");
        printf("\n=== Reception Panel ===\n");
        int choice;
        printf("Logged in to Reception.\n");
        printf("Performing reception tasks:\n");
        printf("1. Create a new customer entry\n");
        printf("2. Show all Rooms\n");
        printf("3. Search for the available rooms\n");
        printf("4. Show the single bed Rooms sorted by price\n");
        printf("5. Show the double bed Rooms sorted by price\n");
        printf("6. Show the information of all customers\n");
        printf("7. Search for a customer by ID\n");
        printf("8. Search for a customer by room number\n");
        printf("9. Update room status\n");
        printf("10. Update customer information\n");
        printf("11. Show min and max room prices\n");
        printf("12. Delete customer\n");
        printf("13. Print checkout form\n");
        printf("14. Print invoice\n");
        printf("15. Exit Reception Panel\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        Customer customers[MAX_CUSTOMERS];
        Room rooms[MAX_ROOMS];
        int numCustomers;
        int numRooms;

        // Read customer data from file
        readFromFile(customers, &numCustomers);
        // Read room data from file
        readFromRoomFile(rooms, &numRooms);

        switch (choice) {
        case 1:
            {// Create a new customer entry
            Customer newCustomer = createNewCustomer();

            // Save the customer data to a file
            saveToFile(newCustomer);

            printf("Customer entry saved successfully!\n");
            printf("\nThe random-generated receipt number is %d\n",newCustomer.receiptNumber);
            updateStatus(rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
            }

        case 2:{
            for (int i = 0; i < numRooms; i++) {
                displayRoom(rooms[i]);
                }
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 3:{

            printAvailableRooms(rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 4:{
            showSingleBedRoomsSortedByPrice(rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 5:{
            showDoubleBedRoomsSortedByPrice(rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 6:{
            // Print customer data
            for (int i = 0; i < numCustomers; i++) {
                printCustomerInfo(&customers[i]);
                }
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 7:{
            searchCustomerByID(customers, numCustomers);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 8:{
            // Sort the data based on customer room number before applying binary search
            selectionSortCustomerRNo(customers, numCustomers);

            // Search customer by room number (Binary Search)
            searchCustomerRoomNo(customers, numCustomers);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 9:{
            // Sort the data based on room number before applying binary search
            selectionSortRoomNo(rooms, numRooms);

            // Update the room status and search the room by room number (Binary Search)
            updateRoomStatus(rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 10:{
            // Sort the data based on customer ID number before applying binary search
            selectionSortCustomerID(customers, numCustomers);

            // Update the customers information and search the customer by ID number (Binary Search)
            updateCustomerInformation(customers, numCustomers);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 11:{
            // Show the minimum and maximum room prices
            float maxPrice = rooms[0].price;
            float minPrice = rooms[0].price;
            maxmin(rooms, 0, numRooms - 1, &maxPrice, &minPrice);
            printf("Minimum Price: %.2f\n", minPrice);
            printf("Maximum Price: %.2f\n", maxPrice);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 12:{
            // Sort the data based on customer ID number before applying binary search
            selectionSortCustomerID(customers, numCustomers);

            // Delete the customers information and search the customer by ID number (Binary Search)
            deleteCustomers(customers, numCustomers);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 13:{
            // Sort the data based on customer ID number before applying binary search
            selectionSortCustomerID(customers, numCustomers);

            // Search the customer by ID number (Binary Search) and print the Checkout Form
            printCheckoutForm(customers, numCustomers, rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 14:{
            // Search the customer by ID number (Linear Search) and print the Invoice
            printInvoice(customers, numCustomers, rooms, numRooms);
            printf("\nDo you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
            scanf("%d", &returnToReceptionPanel);
            break;
        }
        case 15:{
             returnToReceptionPanel = 2;
             break;}
        default:{
            printf("Invalid choice\n");
            sleep(3);
            break;
        }

        printf("Do you want to return to the Reception Panel? (1 for yes, 2 to exit): ");
        scanf("%d", &returnToReceptionPanel);
    }

    system("cls");
    }
}


// Function to print all available rooms
void printAvailableRooms(Room rooms[MAX_ROOMS], int numRooms) {
    int availableFound = 0;

    printf("Available Rooms:\n");
    for (int i = 0; i < numRooms; i++) {
        if (strcasecmp(rooms[i].status, "available") == 0) {
            printf("Room %d is available\n", rooms[i].roomNumber);
            printRoomInfo(&rooms[i]);
            availableFound = 1;
        }
    }

    if (!availableFound) {
        printf("No available rooms found.\n");
    }
}


// Merge sort for single bedrooms based on price
void merge(Room rooms[MAX_ROOMS], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Room L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = rooms[left + i];
    for (j = 0; j < n2; j++)
        R[j] = rooms[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price) {
            rooms[k] = L[i];
            i++;
        } else {
            rooms[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        rooms[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        rooms[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(Room rooms[MAX_ROOMS], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(rooms, left, mid);
        mergeSort(rooms, mid + 1, right);

        merge(rooms, left, mid, right);
    }
}


// Function to show single bedrooms sorted by price
void showSingleBedRoomsSortedByPrice(Room rooms[MAX_ROOMS], int numRooms) {
    // Filter single bed rooms
    Room singleBedRooms[MAX_ROOMS];
    int singleBedCount = 0;
    for (int i = 0; i < numRooms; i++) {
        if (strcasecmp(rooms[i].bedType, "single") == 0) {
            singleBedRooms[singleBedCount] = rooms[i];
            singleBedCount++;
        }
    }

    // Apply merge sort
    mergeSort(singleBedRooms, 0, singleBedCount - 1);

    // Print the sorted rooms
    printf("Single Bed Rooms Sorted by Price:\n");
    for (int i = 0; i < singleBedCount; i++) {
        printRoomInfo(&singleBedRooms[i]);
    }
}


// Bubble sort for double bedrooms based on price
void bubbleSort(Room rooms[MAX_ROOMS], int numRooms) {
    for (int i = 0; i < numRooms - 1; i++) {
        for (int j = 0; j < numRooms - i - 1; j++) {
            if (strcasecmp(rooms[j].bedType, "double") == 0 && strcasecmp(rooms[j + 1].bedType, " double")
                == 0 &&
                rooms[j].price > rooms[j + 1].price) {
                // Swap rooms[j] and rooms[j + 1]
                Room temp = rooms[j];
                rooms[j] = rooms[j + 1];
                rooms[j + 1] = temp;
            }
        }
    }
}


// Function to show double bedrooms sorted by price
void showDoubleBedRoomsSortedByPrice(Room rooms[MAX_ROOMS], int numRooms) {
    // Apply bubble sort
    bubbleSort(rooms, numRooms);

    // Print the sorted rooms
    printf("Double Bed Rooms Sorted by Price:\n");
    for (int i = 0; i < numRooms; i++) {
        if (strcasecmp(rooms[i].bedType, "double") == 0) {
            printRoomInfo(&rooms[i]);
        }
    }
}


// Linear search for a customer by ID
int linearSearchCustomerByID(int num, Customer customers[MAX_CUSTOMERS], int numCustomers) {
    for (int i = 0; i < numCustomers; ++i) {
        if (customers[i].idNumber == num) {
            return i; // return the index if found
        }
    }
    return -1; // Customer not found
}


// Function to search for a customer by ID
void searchCustomerByID(Customer customers[MAX_CUSTOMERS], int numCustomers) {
    int customerID;
    printf("Enter the customer ID to search: ");
    scanf("%d", &customerID);

    int result = linearSearchCustomerByID(customerID, customers, numCustomers);

    if (result == -1) {
        printf("Customer ID %d is not found.\n", customerID);
    } else {
        printf("Customer ID is found:\n");
        printCustomerInfo(&customers[result]);
    }
}


// Function to create a new customer entry
Customer createNewCustomer() {
    Customer newCustomer;

    printf("Customer ID type: ");
    scanf("%s", newCustomer.idType);

    printf("ID number: ");
    scanf("%d", &newCustomer.idNumber);

    printf("Name: ");
    scanf("%s", newCustomer.name);

    printf("Gender (M/F): ");
    scanf("%s", newCustomer.gender);

    printf("Country: ");
    scanf("%s", newCustomer.country);

    printf("Allocated room number: ");
    scanf("%d", &newCustomer.roomNumber);

    printf("Check-in date and time: ");
    scanf("%s", newCustomer.checkInDateTime);

    printf("Check-out date and time: ");
    scanf("%s", newCustomer.checkOutDateTime);

    printf("Number of staying days: ");
    scanf("%d", &newCustomer.stayingDays);

    printf("Total amount: ");
    scanf("%lf", &newCustomer.totalAmount);

    printf("Initial payment: ");
    scanf("%lf", &newCustomer.initialPayment);

    // Calculate pending amount
    newCustomer.pendingAmount = calculatePendingAmount(newCustomer.totalAmount, newCustomer.initialPayment);

    printf("Deposit: ");
    scanf("%lf", &newCustomer.deposit);

    newCustomer.receiptNumber = rand() % 1000 + 1;

    return newCustomer;
}


// Function to calculate pending amount
double calculatePendingAmount(double totalAmount, double initialPayment) {
    return totalAmount - initialPayment;
}


// Function to save customer data to a file
void saveToFile(Customer customers) {
    createFolderAndFileIfNotExists();

    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s %d %s %s %s %d %s %s %d %.2lf %.2lf %.2lf %.2lf %d %d-%d-%d\n",
            customers.idType, customers.idNumber, customers.name, customers.gender,
            customers.country, customers.roomNumber, customers.checkInDateTime, customers.checkOutDateTime,
            customers.stayingDays, customers.totalAmount, customers.initialPayment,
            customers.pendingAmount, customers.deposit, customers.receiptNumber);

    fclose(file);
}


// Function to create the customer data folder and file if they don't exist
void createFolderAndFileIfNotExists() {
    struct stat st = {0};

    // Check if the folder exists, create it if not
    if (stat(FOLDER_NAME, &st) == -1) {
        // Create the directory
        if (mkdir(FOLDER_NAME) != 0) {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }

        // Set the directory permissions (0700 in octal)
        if (chmod(FOLDER_NAME, 0700) != 0) {
            perror("Error setting directory permissions");
            exit(EXIT_FAILURE);
        }
    }

    // Check if the file exists, create it if not
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
}


// Function to read customer data from a file
void readFromFile(Customer customers[MAX_CUSTOMERS], int *numCustomers) {

    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *numCustomers = 0; // Initialize the number of customers

    while (*numCustomers < MAX_CUSTOMERS &&
           fscanf(file, "%s %d %s %s %s %d %s %s %d %lf %lf %lf %lf %d %d-%d-%d",
                  customers[*numCustomers].idType, &customers[*numCustomers].idNumber,
                  customers[*numCustomers].name, customers[*numCustomers].gender,
                  customers[*numCustomers].country, &customers[*numCustomers].roomNumber,
                  customers[*numCustomers].checkInDateTime,customers[*numCustomers].checkOutDateTime,
                  &customers[*numCustomers].stayingDays, &customers[*numCustomers].totalAmount,
                  &customers[*numCustomers].initialPayment, &customers[*numCustomers].pendingAmount,
                   &customers[*numCustomers].deposit, &customers[*numCustomers].receiptNumber) != EOF) {
        (*numCustomers)++;
    }

    fclose(file);
}


// Function to read rooms information from the file
void readFromRoomFile(Room rooms[MAX_ROOMS], int *numRooms) {
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r"); // Open the file in reading mode

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *numRooms = 0;

    // Read and process the first line
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file); // Read the first line

    // Tokenize the first line and process the header information
    char *token = strtok(line, ",");
    while (token != NULL) {
    // process token as needed
        token = strtok(NULL, ",");
    }

    // Read the information according to the sequence
    while (*numRooms < MAX_ROOMS && fscanf(file, "%d,%[^,],%[^,],%f,%[^,],%f\n",
               &rooms[*numRooms].roomNumber, rooms[*numRooms].status, rooms[*numRooms].cleaningStatus,
               &rooms[*numRooms].price, rooms[*numRooms].bedType, &rooms[*numRooms].discount) != EOF) {
        (*numRooms)++;
    }
    fclose(file);
}


// Display the customers information
void printCustomerInfo(const Customer *customers) {
    printf("Customer ID type: %s\n", customers->idType);
    printf("ID number: %d\n", customers->idNumber);
    printf("Name: %s\n", customers->name);
    printf("Gender: %s\n", customers->gender);
    printf("Country: %s\n", customers->country);
    printf("Room number: %d\n", customers->roomNumber);
    printf("Check-in date and time: %s\n", customers->checkInDateTime);
    printf("Check-out date and time: %s\n", customers->checkOutDateTime);
    printf("Number of staying days: %d\n", customers->stayingDays);
    printf("Total amount: %.2lf\n", customers->totalAmount);
    printf("Initial payment: %.2lf\n", customers->initialPayment);
    printf("Pending amount: %.2lf\n", customers->pendingAmount);
    printf("Deposit: %.2lf\n", customers->deposit);
    printf("Receipt number: %d\n", customers->receiptNumber);
    printf("\n");
}


// Display the customers room information
void printRoomInfo(const Room *rooms) {
    printf("Room Number: %d\tPrice: %.2f \tBed Type: %s\tDiscount: %.2f\n", rooms->roomNumber, rooms->price,
            rooms->bedType, rooms->discount);
    printf("\n");
}


// Search the customer by room number
void searchCustomerRoomNo(Customer customers[], int numCustomers){
    int roomNo;
    printf("Enter the room number to search: ");
    scanf("%d", &roomNo);

    // Search for the room number of customers using Binary Search
    int result = binarySearchCRoomNo(roomNo, customers, 0, numCustomers - 1);
    if (result == -1) {
        printf("Room number %d is not found.\n", roomNo);
    } else {
        printf("Room found:\n");
        printCustomerInfo(&customers[result]);
    }
}


// Update the room Status to available or occupied
void updateRoomStatus(Room rooms[MAX_ROOMS], int numRooms){
    int roomNo;
    printf("Enter the room number to search: ");
    scanf("%d", &roomNo);

    // Search for the room number of rooms using Binary Search
    int result = binarySearchRRoomNo(roomNo, rooms, 0, numRooms - 1);
    if (result == -1) {
        printf("Room number %d is not found.\n", roomNo);
    } else {
        printf("Room is found:\n");
        printRoomInfo(&rooms[result]);
    }

    if (result != -1){
        char selection;
        char choice[MAX_INFO_LENGTH];
        printf("Update room status? (y/n): ");
        scanf(" %c", &selection);

        if (selection == 'y' || selection == 'Y'){
            printf("Update the room status to: occupied or available\nEnter your choice: ");
            scanf(" %s", choice);
            strcpy(rooms[result].status, choice);  // Update room status
             // Update the file after making changes
            char filename[100];
            sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

            FILE *file = fopen(filename, "r+");
            if (file == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            // Rewrite the header
            fprintf(file, "Room number, status (available or occupied), cleaning status (clean or dirty), price, bed type (single or double), discount \n");

            // Rewrite all room records
            for (int i = 0; i < numRooms; ++i) {
                fprintf(file, "%d,%s,%s,%.2f,%s,%.2f\n",
                        rooms[i].roomNumber, rooms[i].status, rooms[i].cleaningStatus,
                        rooms[i].price, rooms[i].bedType, rooms[i].discount);
            }

            fclose(file);
            printf("Room status is updated.\n");}
    }
}


// Update the room status to occupied after a new customer booked the room
void updateStatus(Room rooms[MAX_ROOMS], int numRooms){
    int allocatedRoomNumber;

    printf("Enter the allocated room number: ");
    scanf("%d", &allocatedRoomNumber);

    // Search for the allocated room number in the rooms array
    int roomIndex = -1;
    for (int i = 0; i < numRooms; ++i) {
        if (rooms[i].roomNumber == allocatedRoomNumber) {
            roomIndex = i;
            break;
        }
    }

    if (roomIndex != -1) {
        // Update the room status to "occupied"
        strcpy(rooms[roomIndex].status, " occupied");

         // Update the file after making changes
        char filename[100];
        sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        // Rewrite the header
        fprintf(file, "Room number, status (available or occupied), cleaning status (clean or dirty), price, bed type (single or double), discount \n");

        // Rewrite all room records
        for (int i = 0; i < numRooms; ++i) {
            fprintf(file, "%d,%s,%s,%.2f,%s,%.2f\n",
                    rooms[i].roomNumber, rooms[i].status, rooms[i].cleaningStatus,
                    rooms[i].price, rooms[i].bedType, rooms[i].discount);
        }

        fclose(file);
        printf("Room status updated to 'occupied' for room number %d.\n", allocatedRoomNumber);
    } else {
        printf("Room number %d not found.\n", allocatedRoomNumber);
    }

}


// Update the customers information
void updateCustomerInformation(Customer customers[MAX_CUSTOMERS], int numCustomers){
    int customerID;
    printf("Enter the customer ID to search: ");
    scanf("%d", &customerID);

    // Search for the Customer ID using Binary Search
    int result = binarySearchCustomerID(customerID, customers, 0, numCustomers - 1);
    if (result == -1) {
        printf("Customer ID %d is not found.\n", customerID);
    } else {
        printf("Customer ID is found:\n");
        printCustomerInfo(&customers[result]);
    }

    if (result != -1){
        char selection;
        int choice;
        printf("Update customer information? (y/n): ");
        scanf(" %c", &selection);
        if (selection == 'y' || selection == 'Y'){
            // Choices of which information to update
            printf("Which information do you want to update?\n1. Name\n2. Gender\n3. Country\n");
            printf("4. Room number\n5. Check In Date & Time\n6. Check Out Date & Time\n7. Staying Days\n");
            printf("8. Total Amount\n9. Initial Payment\n10. Pending Amount\n11. Deposit\n");
            printf("Enter Your Choice: ");
            scanf("%d",&choice);

            switch (choice) {
                case 1:{
                    char name[50];
                    printf("Name: "); // Update name
                    scanf("%s",name);
                    strcpy(customers[result].name, name);
                    printf("Name updated to %s\n",customers[result].name);
                    break;}
                case 2:{
                    char gender[10];
                    printf("Gender: "); // Update gender
                    scanf("%s",gender);
                    strcpy(customers[result].gender, gender);
                    printf("Gender updated to %s\n",customers[result].gender);
                    break;}
                case 3:{
                    char country[50];
                    printf("Country: "); // Update country
                    scanf("%s",country);
                    strcpy(customers[result].country, country);
                    printf("Country updated to %s\n",customers[result].country);
                    break;}
                case 4:{
                    int number;
                    printf("Room Number: "); // Update Room Number
                    scanf("%d",&number);
                    customers[result].roomNumber = number;
                    printf("Room number updated to %d\n",customers[result].roomNumber);
                    break;}
                case 5:{
                    char checkInDateTime[20];
                    printf("Check In Date & Time: "); // Update Check In Date & Time
                    scanf("%s",checkInDateTime);
                    strcpy(customers[result].checkInDateTime, checkInDateTime);
                    printf("Check In Date & Time updated to %s\n",customers[result].checkInDateTime);
                    break;}
                case 6:{
                    char checkOutDateTime[20];
                    printf("Check Out Date & Time: "); // Update Check Out Date & Time
                    scanf("%s",checkOutDateTime);
                    strcpy(customers[result].checkOutDateTime, checkOutDateTime);
                    printf("Check In Date & Time updated to %s\n",customers[result].checkOutDateTime);
                    break;}
                case 7:{
                    int stayingDays;
                    printf("Staying Days: "); // Update Staying Days
                    scanf("%d",&stayingDays);
                    customers[result].stayingDays = stayingDays;
                    printf("Staying Days updated to %d\n",customers[result].stayingDays);
                    break;}
                case 8:{
                    double totalAmount;
                    printf("Total Amount: RM"); // Update Total Amount
                    scanf("%lf",&totalAmount);
                    customers[result].totalAmount = totalAmount;
                    printf("Total Amount updated to RM %.2lf\n",customers[result].totalAmount);
                    break;}
                case 9:{
                    double initialPayment;
                    printf("Initial Payment: RM"); // Update Initial Payment
                    scanf("%lf",&initialPayment);
                    customers[result].initialPayment = initialPayment;
                    printf("Initial Payment: updated to RM %.2lf\n",customers[result].initialPayment);
                    break;}
                case 10:{
                    double pendingAmount;
                    printf("Pending Amount: RM"); // Update Pending Amount
                    scanf("%lf",&pendingAmount);
                    customers[result].pendingAmount = pendingAmount;
                    printf("Pending Amount updated to RM %.2lf\n",customers[result].pendingAmount);
                    break;}
                case 11:{
                    double deposit;
                    printf("Deposit: RM"); // Update Deposit
                    scanf("%lf",&deposit);
                    customers[result].deposit = deposit;
                    printf("Deposit updated to RM %.2lf\n",customers[result].deposit);
                    break;}
                default:{
                    printf("Invalid choice.\n");
                    break;}
            }
            // Update the file after making changes
            char filename[100];
            sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

            FILE *file = fopen(filename, "w");
            if (file == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }

            // Rewrite all customers' records
            for (int i = 0; i < numCustomers; ++i) {
                fprintf(file, "%s %d %s %s %s %d %s %s %d %.2lf %.2lf %.2lf %.2lf %d\n",
                    customers[i].idType,customers[i].idNumber,customers[i].name,
                    customers[i].gender,customers[i].country,customers[i].roomNumber,
                    customers[i].checkInDateTime,customers[i].checkOutDateTime,customers[i].stayingDays,
                    customers[i].totalAmount,customers[i].initialPayment,
                    customers[i].pendingAmount,customers[i].deposit,customers[i].receiptNumber);
            }

            fclose(file);
            printf("Customer information updated and saved to file.\n");
        }
    }
}


// Delete the customer information
void deleteCustomers(Customer customers[MAX_CUSTOMERS], int numCustomers){
    int customerID;
    printf("Enter the customer ID to delete: ");
    scanf("%d", &customerID);

    // Search for the Customer ID using Binary Search
    int result = binarySearchCustomerID(customerID, customers, 0, numCustomers - 1);
    if (result == -1) {
        printf("Customer ID %d is not found.\n", customerID);
        return;
    }
    printf("Customer ID is found:\n");
    printCustomerInfo(&customers[result]);

    char selection;
    printf("Do you want to delete this customer information? (y/n): ");
    scanf(" %c", &selection);

    if (selection == 'y' || selection == 'Y'){
        char filename[100];
        sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

        FILE *file = fopen(filename, "w"); // Open file for writing

        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        // Write valid customer entries to the file
        for (int i = 0; i < numCustomers; ++i) {
            if (i == result) {
                continue; // Continue the loop to delete the customer information
            }
            // Write the other customers information excluding the deleted ones
            fprintf(file, "%s %d %s %s %s %d %s %s %d %.2lf %.2lf %.2lf %.2lf %d\n",
                    customers[i].idType,customers[i].idNumber,customers[i].name,
                    customers[i].gender,customers[i].country,customers[i].roomNumber,
                    customers[i].checkInDateTime,customers[i].checkOutDateTime,customers[i].stayingDays,
                    customers[i].totalAmount,customers[i].initialPayment,
                    customers[i].pendingAmount,customers[i].deposit, customers[i].receiptNumber);
        }
        fclose(file);
        printf("Customer information has been deleted.\n");
    }else {
        printf("Customer information was not deleted.\n");
    }
}


// Print the Checkout Form
void printCheckoutForm(Customer customers[MAX_CUSTOMERS], int numCustomers,Room rooms[MAX_ROOMS], int numRooms){
    int customerID;
    printf("Enter the customer ID to print Checkout Form: ");
    scanf("%d", &customerID);

    // Search for the Customer ID using Binary Search
    int result = binarySearchCustomerID(customerID, customers, 0, numCustomers - 1);
    if (result == -1) {
        printf("Customer ID %d is not found.\n", customerID);
    } else {
        printf("Customer ID is found:\n");

        // Print the Checkout Form
        printf("\n===Checkout Form===\n");
        printCustomerInfo(&customers[result]);
        printf("\n");

        // Update Room Status to Available
        char status[20] = "available";
        int index;
        // Search for the room number in the room array
        int roomNo = customers[result].roomNumber;
        for (int i = 0; i < numRooms; ++i){
            if (rooms[i].roomNumber == roomNo){
            index = i;
            break;}
        }
        // Update the room status to "available"
        strcpy(rooms[index].status, status);

         // Update the file after making changes
        char filename[100];
        sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        // Rewrite the header
        fprintf(file, "Room number, status (available or occupied), cleaning status (clean or dirty), price, bed type (single or double), discount \n");

        // Rewrite all room records
        for (int i = 0; i < numRooms; ++i) {
            fprintf(file, "%d,%s,%s,%.2f,%s,%.2f\n",
                    rooms[i].roomNumber, rooms[i].status, rooms[i].cleaningStatus,
                    rooms[i].price, rooms[i].bedType, rooms[i].discount);
        }

        fclose(file);
        printf("Room status updated to available.\n");
    }
}


// Print the invoice
void printInvoice(Customer customers[MAX_CUSTOMERS], int numCustomers, Room rooms[MAX_ROOMS], int numRooms){
    int customerID;
    printf("Enter the customer ID to print Invoice: ");
    scanf("%d", &customerID);

    // Search for the Customer ID using Linear Search
    int result = -1;
    for (int i = 0; i < numCustomers; ++i) {
        if (customers[i].idNumber == customerID){
            result = i;
            break;}
    }
    if (result == -1) {
        printf("Customer ID %d is not found.\n", customerID);
    } else {
        printf("Customer ID is found:\n");
        // Print the invoice
        printf("\n===Invoice===\n");
        printf("ID number: %d\n", customers[result].idNumber);
        printf("Name: %s\n", customers[result].name);
        printf("Gender: %s\n", customers[result].gender);

        // Count the number of rooms the customer has booked
        // Calculate the total pending amount of all the rooms booked by the customer
        int count = 0;
        double payment = 0;
        double totalPrice = 0;
        double initialPayment = 0;
        int roomNo[MAX_CUSTOMERS];
        for (int i = 0; i < numCustomers; ++i){
            if (strcmp(customers[i].name, customers[result].name) == 0){
                printf("Room %d\n",count + 1);
                printf("Room number: %d\n", customers[i].roomNumber);
                printf("Total amount: %.2lf\n", customers[i].totalAmount);
                printf("Initial payment: %.2lf\n", customers[i].initialPayment);
                printf("Pending amount: %.2lf\n", customers[i].pendingAmount);
                printf("Deposit: %.2lf\n", customers[i].deposit);
                printf("\n");
                roomNo[count] = customers[i].roomNumber;
                count++;
                // Sum out the payment of all rooms
                payment += customers[i].pendingAmount;
                totalPrice += customers[i].totalAmount;
                initialPayment += customers[i].initialPayment;
            }
        }
        // Number of rooms found
        printf("Found %d rooms\n", count);
        printf("Please pay: %.2lf\n", payment);
        double amountReceived = 0;
        double change = 0;
        do {
            printf("Enter the amount tendered: RM ");
            scanf("%lf", &amountReceived);
            // Calculate the change
            if (amountReceived >= payment) {
                change = amountReceived - payment;
                printf("\nThe change is RM %.2lf\n", change);

                // Print the receipt
                printf("Printing Receipt....\n");

                char hotelName[50] = "Deluxe Hotel";

                printf("\n========= Receipt =========\n");
                printf("Receipt Number: %d\n", customers[result].receiptNumber);
                printf("Date: %s\n", customers[result].checkOutDateTime);
                printf("Hotel Name: %s\n", hotelName);
                printf("Customer ID: %d\n", customers[result].idNumber);
                printf("Customer Name: %s\n", customers[result].name);

                // Sort the rooms based on the prices of rooms
                selectionSortRoomPrice(rooms, numRooms);
                int k = 0;
                for (int i = 0; i < numRooms; ++i) {
                for (int j = 0; j < count; ++j) {
                    if (rooms[i].roomNumber == roomNo[j]) {
                        printf("Room %d\n", k+1);
                        // Print the rooms information
                        printRoomInfo(&rooms[i]);
                        printf("\n");
                        k++;
                        }
                    }
                }
                printf("======================================");
                printf("\nTotal Price: %.2lf\n", totalPrice);
                printf("Initial Payment: %.2lf\n", initialPayment);
                printf("Change: %.2lf\n", change);
                break;
            } else {
                // If insufficient amount, ask user to input amount again
                printf("Money not enough, enter sufficient Amount.\n");
            }
        } while (1); // Loop until payment is sufficient
    }
}


// Algorithms
// Binary search using Customer ID Number
int binarySearchCustomerID(int num, Customer customers[MAX_CUSTOMERS], int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (customers[mid].idNumber == num) {
            return mid; // return the index if found
        } else if (customers[mid].idNumber > num) {
            return binarySearchCustomerID(num, customers, low, mid - 1);
        } else {
            return binarySearchCustomerID(num, customers, mid + 1, high);
        }
    }
    return -1;
}


// Binary search using Customer Room Number
int binarySearchCRoomNo(int num, Customer customers[MAX_CUSTOMERS], int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (customers[mid].roomNumber == num) {
            return mid;// return the index if found
        } else if (customers[mid].roomNumber > num) {
            return binarySearchCRoomNo(num, customers, low, mid - 1);
        } else {
            return binarySearchCRoomNo(num, customers, mid + 1, high);
        }
    }
    return -1;
}


// Binary search using Room Number
int binarySearchRRoomNo(int num, Room rooms[MAX_ROOMS], int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (rooms[mid].roomNumber == num) {
            return mid;// return the index if found
        } else if (rooms[mid].roomNumber > num) {
            return binarySearchRRoomNo(num, rooms, low, mid - 1);
        } else {
            return binarySearchRRoomNo(num, rooms, mid + 1, high);
        }
    }
    return -1;
}


// Find the minimum and maximum prices of all rooms
void maxmin(Room rooms[], int i, int j, float *maxPrice, float *minPrice) {
    // Find the minimum and maximum number
    // If the array has only one elements
    if (i == j) {
        *maxPrice = rooms[i].price;
        *minPrice = rooms[i].price;
    }
    // If the array has two elements
    else if (i == j - 1) {
        if (rooms[i].price < rooms[j].price) {
            *maxPrice = rooms[j].price;
            *minPrice = rooms[i].price;
        } else {
            *maxPrice = rooms[i].price;
            *minPrice = rooms[j].price;
        }
    }
    // If the array has more than two elements
    else {
        int mid = (i + j) / 2;
        float max1, min1;
        maxmin(rooms, i, mid, maxPrice, minPrice);
        maxmin(rooms, mid + 1, j, &max1, &min1);

        if (*maxPrice < max1) {
            *maxPrice = max1;
        }
        if (*minPrice > min1) {
            *minPrice = min1;
        }
    }
}


// Selection Sort using Prices of rooms
void selectionSortRoomPrice(Room rooms[MAX_ROOMS], int numRooms){
    int i, j, k;
    // k is the index of minimum number

    for (i = 0; i < numRooms - 1; i++) {
        // Find the minimum element
        k = i;
        for (j = i + 1; j < numRooms; j++)
            if (rooms[j].price < rooms[k].price)
                k = j;

        if(k != j){
            // Swap rooms[k] with rooms[i]
            Room temp = rooms[k];
            rooms[k] = rooms[i];
            rooms[i] = temp;
        }
    }
}


// Selection Sort using Room Number
void selectionSortRoomNo(Room rooms[MAX_ROOMS], int numRooms){
    int i, j, k;
    // k is the index of minimum number

    for (i = 0; i < numRooms - 1; i++) {
        // Find the minimum element
        k = i;
        for (j = i + 1; j < numRooms; j++)
            if (rooms[j].roomNumber < rooms[k].roomNumber)
                k = j;

        if(k != j){
            // Swap rooms[k] with rooms[i]
            Room temp = rooms[k];
            rooms[k] = rooms[i];
            rooms[i] = temp;
        }
    }
}


// Selection Sort using Customer ID Number
void selectionSortCustomerID(Customer customers[MAX_CUSTOMERS], int numCustomers){
    int i, j, k;
    // k is the index of minimum number

    for (i = 0; i < numCustomers - 1; i++) {
        // Find the minimum element
        k = i;
        for (j = i + 1; j < numCustomers; j++)
            if (customers[j].idNumber < customers[k].idNumber)
                k = j;

        if(k != j){
            // Swap rooms[k] with rooms[i]
            Customer temp = customers[k];
            customers[k] = customers[i];
            customers[i] = temp;
        }
    }
}


// Selection Sort using Customer room number
void selectionSortCustomerRNo(Customer customers[MAX_CUSTOMERS], int numCustomers){
    int i, j, k;
    // k is the index of minimum number

    for (i = 0; i < numCustomers - 1; i++) {
        // Find the minimum element
        k = i;
        for (j = i + 1; j < numCustomers; j++)
            if (customers[j].roomNumber < customers[k].roomNumber)
                k = j;

        if(k != j){
            // Swap rooms[k] with rooms[i]
            Customer temp = customers[k];
            customers[k] = customers[i];
            customers[i] = temp;
        }
    }
}


// Admin Panel Functions
// Partitioning employees for quick sort
int partition(Employee employees[], int left, int right) {
    int pivot = employees[right].ID;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (employees[j].ID < pivot) {
            i++;

            Employee temp = employees[i];
            employees[i] = employees[j];
            employees[j] = temp;
        }
    }

    Employee temp = employees[i + 1];
    employees[i + 1] = employees[right];
    employees[right] = temp;

    return i + 1;
}


// Partitioning rooms for quick sort
int partitionRoom(Room rooms[], int left, int right) {
    int pivot = rooms[right].roomNumber;
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (rooms[j].roomNumber < pivot) {
            i++;

            Room temp = rooms[i];
            rooms[i] = rooms[j];
            rooms[j] = temp;
        }
    }

    Room temp = rooms[i + 1];
    rooms[i + 1] = rooms[right];
    rooms[right] = temp;

    return i + 1;
}


// Quick sort for employees
void quickSort(Employee employees[], int left, int right) {
    if (left < right) {
        int pivot = partition(employees, left, right);

        quickSort(employees, left, pivot - 1);
        quickSort(employees, pivot + 1, right);
    }
}


// Quick sort for rooms
void quickSortRoom(Room rooms[], int left, int right) {
    if (left < right) {
        int pivot = partitionRoom(rooms, left, right);

        quickSortRoom(rooms, left, pivot - 1);
        quickSortRoom(rooms, pivot + 1, right);
    }
}


// Display all rooms
void displayRoom(Room room) {
    printf("Room Number: %d\nStatus: %s\nCleaning Status: %s\nPrice: %.2f\nBed Type: %s\nDiscount Percentage: %.2f\n\n",
           room.roomNumber, room.status, room.cleaningStatus, room.price, room.bedType, room.discount);
}


// Display all employees
void displayEmployee(Employee emp) {
    printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nJob: %s\nSalary: %s\nPhone: %s\nAddress: %s\nEmail: %s\n\n",
           emp.ID, emp.Name, emp.Age, emp.Gender, emp.Job, emp.Salary, emp.Phone, emp.Address, emp.Email);
}


// Search for employee by ID
int searchEmployeeByID(Employee employees[], int numEmployees, int targetID) {
    int left = 0;
    int right = numEmployees - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (employees[mid].ID == targetID)
            return mid;

        if (employees[mid].ID > targetID)
            right = mid - 1;

        else
            left = mid + 1;
    }

    return -1;
}


// Search for room by ID
int searchRoomID(Room rooms[], int numRooms, int targetID) {
    int left = 0;
    int right = numRooms - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (rooms[mid].roomNumber == targetID)
            return mid;

        if (rooms[mid].roomNumber > targetID)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}


// Binary search for employee by name
void bse() {
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, EMP_FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address,
               employees[numEmployees].Email);
        numEmployees++;
    }

    fclose(file);

    quickSort(employees, 0, numEmployees - 1);

    int searchID;
    int resultIndex;

    printf("Enter the Employee ID to search: ");
    scanf("%d", &searchID);

    resultIndex = searchEmployeeByID(employees, numEmployees, searchID);

    if (resultIndex != -1) {
        printf("\nEmployee found at index %d:\n", resultIndex);
        displayEmployee(employees[resultIndex]);
    } else {
        printf("Employee with ID %d not found.\n", searchID);
    }
}


// Edit employee information
void ede() {
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, EMP_FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address,
               employees[numEmployees].Email);
        numEmployees++;
    }

    fclose(file);

    quickSort(employees, 0, numEmployees - 1);

    int searchID;
    int resultIndex;

    printf("Enter the Employee ID to edit: ");
    scanf("%d", &searchID);

    resultIndex = searchEmployeeByID(employees, numEmployees, searchID);

    if (resultIndex != -1) {
        printf("Employee found at index %d:\n", resultIndex);
        displayEmployee(employees[resultIndex]);

        printf("\nEnter new information for the employee:\n");
        printf("Name: ");
        scanf("%s", employees[resultIndex].Name);
        printf("Age: ");
        scanf("%d", &employees[resultIndex].Age);
        printf("Gender: ");
        scanf("%s", employees[resultIndex].Gender);
        printf("Job: ");
        scanf("%s", employees[resultIndex].Job);
        printf("Salary: ");
        scanf("%s", employees[resultIndex].Salary);
        printf("Phone: ");
        scanf("%s", employees[resultIndex].Phone);
        printf("Address: ");
        scanf("%s", employees[resultIndex].Address);
        printf("Email: ");
        scanf("%s", employees[resultIndex].Email);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Unable to open file for writing.\n");
            return;
        }

        fprintf(file, "ID,Name,Age,Gender,Job,Salary,Phone,Address,Email\n");
        for (int i = 0; i < numEmployees; i++) {
            fprintf(file, "%d,%s,%d,%s,%s,%s,%s,%s,%s\n",
                    employees[i].ID, employees[i].Name, employees[i].Age,
                    employees[i].Gender, employees[i].Job, employees[i].Salary,
                    employees[i].Phone, employees[i].Address, employees[i].Email);
        }

        fclose(file);

        printf("Employee information updated successfully.\n");
    } else {
        printf("Employee with ID %d not found.\n", searchID);
    }
}


// Delete employee information
void dle() {
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, EMP_FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address,
               employees[numEmployees].Email);
        numEmployees++;
    }

    fclose(file);

    int searchID;
    int found = 0;

    printf("Enter the Employee ID to delete: ");
    scanf("%d", &searchID);

    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].ID == searchID) {

            for (int j = i; j < numEmployees - 1; j++) {
                employees[j] = employees[j + 1];
            }
            numEmployees--;
            found = 1;
            break;
        }
    }

    if (found) {

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Unable to open file for writing.\n");
            return;
        }

        fprintf(file, "ID,Name,Age,Gender,Job,Salary,Phone,Address,Email\n");
        for (int i = 0; i < numEmployees; i++) {
            fprintf(file, "%d,%s,%d,%s,%s,%s,%s,%s,%s\n",
                    employees[i].ID, employees[i].Name, employees[i].Age,
                    employees[i].Gender, employees[i].Job, employees[i].Salary,
                    employees[i].Phone, employees[i].Address, employees[i].Email);
        }

        fclose(file);

        printf("Employee with ID %d deleted successfully.\n", searchID);
    } else {
        printf("Employee with ID %d not found.\n", searchID);
    }
}


// Edit room information
void edr() {
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numRooms < MAX_ROOMS) {
        sscanf(line, "%d,%[^,],%[^,],%f,%[^,],%f",
               &rooms[numRooms].roomNumber, rooms[numRooms].status, rooms[numRooms].cleaningStatus,
               &rooms[numRooms].price, rooms[numRooms].bedType, &rooms[numRooms].discount);
        numRooms++;
    }

    fclose(file);

    quickSortRoom(rooms, 0, numRooms - 1);

    int searchID;
    int resultIndex;
    printf("\n");

    printf("Enter the Room Number to edit: ");
    scanf("%d", &searchID);

    resultIndex = searchRoomID(rooms, numRooms, searchID);

    if (resultIndex != -1) {
        printf("Room with Room Number %d found:\n", searchID);
        displayRoom(rooms[resultIndex]);

        printf("\nEnter new information for the room:\n");
        printf("Status (available or occupied): ");
        scanf("%s", rooms[resultIndex].status);
        printf("Cleaning Status (clean or dirty): ");
        scanf("%s", rooms[resultIndex].cleaningStatus);
        printf("Price: ");
        scanf("%f", &rooms[resultIndex].price);
        printf("Bed Type (single or double): ");
        scanf("%s", rooms[resultIndex].bedType);
        printf("Discount Percentage: ");
        scanf("%f", &rooms[resultIndex].discount);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Unable to open file for writing.\n");
            return;
        }

        fprintf(file, "Room number, status (available or occupied), cleaning status (clean or dirty), price, bed type (single or double), discount percentage\n");
        for (int i = 0; i < numRooms; i++) {
            fprintf(file, "%d,%s,%s,%.2f,%s,%.2f\n",
                    rooms[i].roomNumber, rooms[i].status, rooms[i].cleaningStatus,
                    rooms[i].price, rooms[i].bedType, rooms[i].discount);
        }

        fclose(file);

        printf("Room information updated successfully.\n");
    } else {
        printf("Room with Room Number %d not found.\n", searchID);
    }
}


// Print employee information
void empinfo(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, EMP_FILE_NAME);

    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    char *token;
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    char addNewEmployee;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);
    token = strtok(line, ",");
    while (token != NULL) {

        printf("%s\t", token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address,
               employees[numEmployees].Email);
        displayEmployee(employees[numEmployees]);
        numEmployees++;
    }

    printf("\nDo you want to add a new employee? (Y/N): ");
    scanf(" %c", &addNewEmployee);

    if (addNewEmployee == 'Y' || addNewEmployee == 'y') {
        if (numEmployees < MAX_EMPLOYEES) {
            printf("\nEnter details of the new employee:\n");
            printf("ID: ");
            scanf("%d", &employees[numEmployees].ID);
            printf("Name: ");
            scanf("%s", employees[numEmployees].Name);
            printf("Age: ");
            scanf("%d", &employees[numEmployees].Age);
            printf("Gender: ");
            scanf("%s", employees[numEmployees].Gender);
            printf("Job: ");
            scanf("%s", employees[numEmployees].Job);
            printf("Salary: ");
            scanf("%s", employees[numEmployees].Salary);
            printf("Phone: ");
            scanf("%s", employees[numEmployees].Phone);
            printf("Address: ");
            scanf("%s", employees[numEmployees].Address);
            printf("Email: ");
            scanf("%s", employees[numEmployees].Email);

            numEmployees++;
            printf("New employee added.\n");

            // Rewrite updated employee information to file
            FILE *file = fopen(filename, "w");
            if (file == NULL) {
                printf("Unable to open file for writing.\n");
                return;
            }

            fprintf(file, "ID,Name,Age,Gender,Job,Salary,Phone,Address,Email\n");
            for (int i = 0; i < numEmployees; i++) {
                fprintf(file, "%d,%s,%d,%s,%s,%s,%s,%s,%s\n",
                        employees[i].ID, employees[i].Name, employees[i].Age,
                        employees[i].Gender, employees[i].Job, employees[i].Salary,
                        employees[i].Phone, employees[i].Address, employees[i].Email);
            }

            fclose(file);
        } else {
            printf("Maximum employee limit reached. Cannot add more employees.\n");
        }
    } else {
        printf("No new employees added.\n");
    }

    return;
}


// Print room information
void roominfo(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;
    char addRoomChoice;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);
    token = strtok(line, ",");
    while (token != NULL) {

        printf("%s\t", token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    while (fgets(line, MAX_LINE_LENGTH, file) && numRooms < MAX_ROOMS) {
        sscanf(line, "%d,%[^,],%[^,],%f,%[^,],%f",
               &rooms[numRooms].roomNumber, rooms[numRooms].status, rooms[numRooms].cleaningStatus,
               &rooms[numRooms].price, rooms[numRooms].bedType, &rooms[numRooms].discount);
        displayRoom(rooms[numRooms]);
        numRooms++;
    }

    printf("Do you want to add a room? (Y/N): ");
    scanf(" %c", &addRoomChoice);

    if (addRoomChoice == 'Y' || addRoomChoice == 'y') {
        // Adding room information
        printf("Enter the room number: ");
        scanf("%d", &rooms[numRooms].roomNumber);
        printf("Enter status (available or occupied): ");
        scanf("%s", rooms[numRooms].status);
        printf("Enter cleaning status (clean or dirty): ");
        scanf("%s", rooms[numRooms].cleaningStatus);
        printf("Enter price: ");
        scanf("%f", &rooms[numRooms].price);
        printf("Enter bed type (single or double): ");
        scanf("%s", rooms[numRooms].bedType);
        printf("Enter discount percentage: ");
        scanf("%f", &rooms[numRooms].discount);

        printf("Room information added.\n");

        numRooms++;

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            printf("Unable to open file for writing.\n");
            return;
        }

        fprintf(file, "Room number, status (available or occupied), cleaning status (clean or dirty), price, bed type (single or double), discount percentage\n");
        for (int i = 0; i < numRooms; i++) {
            fprintf(file, "%d,%s,%s,%.2f,%s,%.2f\n",
                    rooms[i].roomNumber, rooms[i].status, rooms[i].cleaningStatus,
                    rooms[i].price, rooms[i].bedType, rooms[i].discount);
        }

        fclose(file);
    } else {
        printf("No room added.\n");
    }

    return;
}


// Function to show all rooms
void showAllRooms(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);
    token = strtok(line, ",");
    while (token != NULL) {

        printf("%s\t", token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    while (fgets(line, MAX_LINE_LENGTH, file) && numRooms < MAX_ROOMS) {
        sscanf(line, "%d,%[^,],%[^,],%f,%[^,],%f",
               &rooms[numRooms].roomNumber, rooms[numRooms].status, rooms[numRooms].cleaningStatus,
               &rooms[numRooms].price, rooms[numRooms].bedType, &rooms[numRooms].discount);
        displayRoom(rooms[numRooms]);
        numRooms++;
    }
}


// Function to show all rooms by number
void showAllRoomsbyNumber(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);
    token = strtok(line, ",");
    while (token != NULL) {

        printf("%s\t", token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    while (fgets(line, MAX_LINE_LENGTH, file) && numRooms < MAX_ROOMS) {
        sscanf(line, "%d,%[^,],%[^,],%f,%[^,],%f",
               &rooms[numRooms].roomNumber, rooms[numRooms].status, rooms[numRooms].cleaningStatus,
               &rooms[numRooms].price, rooms[numRooms].bedType, &rooms[numRooms].discount);
        numRooms++;
    }

    quickSortRoom(rooms, 0, numRooms - 1);
    displayRoom(rooms[numRooms]);

    fclose(file);
}


// Swap two rooms
void swap(Room *a, Room *b) {
    Room temp = *a;
    *a = *b;
    *b = temp;
}


// Function to swap two rooms with bubble sort using discounted price
void bubbleSortRooms(Room arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((arr[j].price)*(1-arr[j].discount) > (arr[j+1].price)*(1-arr[j+1].discount)) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}


// Function to show all rooms by price
void showAllRoomsbyPrice(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, ROOM_FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);
    token = strtok(line, ",");
    while (token != NULL) {

        printf("%s\t", token);
        token = strtok(NULL, ",");
    }
    printf("\n");

    while (fgets(line, MAX_LINE_LENGTH, file) && numRooms < MAX_ROOMS) {
        sscanf(line, "%d,%[^,],%[^,],%f,%[^,],%f",
               &rooms[numRooms].roomNumber, rooms[numRooms].status, rooms[numRooms].cleaningStatus,
               &rooms[numRooms].price, rooms[numRooms].bedType, &rooms[numRooms].discount);
        numRooms++;
    }

    bubbleSortRooms(rooms, numRooms);
    displayRoom(rooms[numRooms]);

    fclose(file);
}


// Function to show all bookings
void showAllBookings(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (numCustomers < MAX_CUSTOMERS && fgets(line, MAX_LINE_LENGTH, file)) {
        sscanf(file, "%s %d %s %s %s %d %s %s %d %lf %lf %lf %lf %d",
               customers[numCustomers].idType, &customers[numCustomers].idNumber,
               customers[numCustomers].name, customers[numCustomers].gender,
               customers[numCustomers].country, &customers[numCustomers].roomNumber,
               customers[numCustomers].checkInDateTime,customers[numCustomers].checkOutDateTime,
               &customers[numCustomers].stayingDays, &customers[numCustomers].totalAmount,
               &customers[numCustomers].initialPayment, &customers[numCustomers].pendingAmount,
               &customers[numCustomers].deposit, &customers[numCustomers].receiptNumber);
        numCustomers++;
    }

    for (int i = 0; i < numCustomers; i++) {
        printCustomerInfo(&customers[i]);
    }
}


// Function to show all bookings by date
int compareDates(char dateA[], char dateB[]) {
    if (strlen(dateA) != strlen(dateB)) {
        printf("Invalid date format.\n");
        exit(0);
    }
    for (int i = 0; i < strlen(dateA); i++) {
        if (dateA[i] < dateB[i]) {
            return -1;
        } else if (dateA[i] > dateB[i]) {
            return 1;
        }
    }

    return 0;
}



// Binary search using Date in customer data
int binarySearchbyDate(Customer customer[], int numDates, char target[]) {
    int low = 0;
    int high = numDates - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int comparison = compareDates(target, customer->checkInDateTime);

        if (comparison == 0) {
            return mid;
        } else if (comparison < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}


// Function to search booking
void searchBooking(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;
    char date[20];

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (numCustomers < MAX_CUSTOMERS && fgets(line, MAX_LINE_LENGTH, file)) {
           sscanf(file, "%s %d %s %s %s %d %s %s %d %lf %lf %lf %lf %d",
                  customers[numCustomers].idType, &customers[numCustomers].idNumber,
                  customers[numCustomers].name, customers[numCustomers].gender,
                  customers[numCustomers].country, &customers[numCustomers].roomNumber,
                  customers[numCustomers].checkInDateTime,customers[numCustomers].checkOutDateTime,
                  &customers[numCustomers].stayingDays, &customers[numCustomers].totalAmount,
                  &customers[numCustomers].initialPayment, &customers[numCustomers].pendingAmount,
                  &customers[numCustomers].deposit, &customers[numCustomers].receiptNumber);
        numCustomers++;
    }

    printf("\nEnter target date (DDMMYY): ");
    scanf("%s", date);
    int ans = binarySearchbyDate(customers, numCustomers, date);
    printCustomerInfo(&customers[ans]);

    fclose(file);
}


// Total income per day
void totalIncomePerDay(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;
    int income;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (numCustomers < MAX_CUSTOMERS && fgets(line, MAX_LINE_LENGTH, file)) {
        sscanf(file, "%s %d %s %s %s %d %s %s %d %lf %lf %lf %lf %d",
               customers[numCustomers].idType, &customers[numCustomers].idNumber,
               customers[numCustomers].name, customers[numCustomers].gender,
               customers[numCustomers].country, &customers[numCustomers].roomNumber,
               customers[numCustomers].checkInDateTime,customers[numCustomers].checkOutDateTime,
               &customers[numCustomers].stayingDays, &customers[numCustomers].totalAmount,
               &customers[numCustomers].initialPayment, &customers[numCustomers].pendingAmount,
               &customers[numCustomers].deposit, &customers[numCustomers].receiptNumber);
        numCustomers++;
    }

    for(int i = 0; i < numCustomers; i++){
        income += customers[i].totalAmount;
    }

    printf("Total income per day: %d\n", income);
}


// print receipt for all bookings
void printReceipt(){
    char filename[100];
    sprintf(filename, "%s/%s", FOLDER_NAME, FILE_NAME);

    FILE *file = fopen(filename, "r");

    char line[MAX_LINE_LENGTH];
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = 0;

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (numCustomers < MAX_CUSTOMERS && fgets(line, MAX_LINE_LENGTH, file)) {
        sscanf(file, "%s %d %s %s %s %d %s %s %d %lf %lf %lf %lf %d",
               customers[numCustomers].idType, &customers[numCustomers].idNumber,
               customers[numCustomers].name, customers[numCustomers].gender,
               customers[numCustomers].country, &customers[numCustomers].roomNumber,
               customers[numCustomers].checkInDateTime,customers[numCustomers].checkOutDateTime,
               &customers[numCustomers].stayingDays, &customers[numCustomers].totalAmount,
               &customers[numCustomers].initialPayment, &customers[numCustomers].pendingAmount,
               &customers[numCustomers].deposit, &customers[numCustomers].receiptNumber);
        numCustomers++;
    }

    for(int i=0; i<numCustomers; i++){
        printCustomerInfo(&customers[i]);
    }
}
