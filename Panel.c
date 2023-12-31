#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "windows.h"

// Define username and password
#define USERNAME "user"
#define PASSWORD "123456"
#define MAX_EMPLOYEES 100
#define MAX_ROOMS 100
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


// Structure for Employee
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


typedef struct {
    int roomNumber;
    char status[MAX_INFO_LENGTH];
    char cleaningStatus[MAX_INFO_LENGTH];
    float price;
    char bedType[MAX_INFO_LENGTH];
    float discount;
} Room;


typedef struct {
    int bookingID;
    Room room;
    char customerName[MAX_INFO_LENGTH];
    char customerPhone[MAX_INFO_LENGTH];
    char customerEmail[MAX_INFO_LENGTH];
    char customerAddress[MAX_INFO_LENGTH];
    char checkInDate[MAX_INFO_LENGTH];
    char checkOutDate[MAX_INFO_LENGTH];
    int numberOfAdults;
    int numberOfChildren;
    float totalAmount;
} Booking;


// Function declarations
void login(enum SystemState *currentState);
void showMainPanel(enum SystemState *currentState);
void adminLogin();
void receptionLogin();
void addEmployee();
void addRoom();
void displayEmployee();
void displayRoom();
void roominfo();
void addemp();
void quickSort();
int partition();
int searchEmployeeByID();
int searchRoomID();
void ede();
void dle();
void edr();
void bse();
void empinfo();
void quickSortRoom();
int partitionRoom();
void showAllRooms();
void showAllRoomsbyNumber();
void showAllRoomsbyPrice();

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
    system("cls");
    char username[20];
    char password[20];

    printf("\n=== Admin Login Block===\n");
    printf("Enter Admin username: ");
    scanf("%s", username);

    printf("Enter Admin password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Admin Login successful!\n");

    } else {
        printf("Admin Login failed. Incorrect Admin username or password.\n");
        exit(1);
    }

    int choice;
    system("cls");
    printf("****** Dear admin, welcome to the management page! ******\n");
    printf("\n=== Admin Panel ===\n");
    printf("Logged in as Admin. Performing admin tasks\n");
    printf("Now the task can be chosen by admin are as follows,\n"
           "1. Show Employees' information and add new employee if you wish.\n"
           "2. Show Room information and add new room if you wish.\n"
           "3. Search The Employee.\n"
           "4. Edit Employee data.\n"
           "5. Delete Employee.\n"
           "6. Edit the Room Information.\n"
           "7. Show all Rooms.\n"
           "8. Show all Rooms by number.\n"
           "9. Show all Rooms by price.\n"
           "10. All Booking Operations.\n"
           "11. Search Booking.\n"
           "12. Total Income per day.\n"
           "13. Receipts.\n"
           "14. Exit Admin Panel.\n");
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
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
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
    printf("****** Dear Reception Staff, welcome to the Front Desk Management page! ******\n");
    printf("\n=== Reception Panel ===\n");
    printf("Logged in as Reception Staff. Performing reception tasks...\n");
    // Perform reception staff tasks here
}


void displayEmployee(Employee emp) {
    printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nJob: %s\nSalary: %s\nPhone: %s\nAddress: %s\nEmail: %s\n\n",
           emp.ID, emp.Name, emp.Age, emp.Gender, emp.Job, emp.Salary, emp.Phone, emp.Address, emp.Email);
}


void empinfo(){
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    char addNewEmployee;

    file = fopen("empinfo.txt", "r");
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
               employees[numEmployees].Phone, employees[numEmployees].Address, employees[numEmployees].Email);
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
            file = fopen("empinfo.txt", "w");
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


void displayRoom(Room room) {
    printf("Room Number: %d\nStatus: %s\nCleaning Status: %s\nPrice: %.2f\nBed Type: %s\nDiscount Percentage: %.2f\n\n",
           room.roomNumber, room.status, room.cleaningStatus, room.price, room.bedType, room.discount);
}


void roominfo(){
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;
    char addRoomChoice;

    file = fopen("roominfo.txt", "r");
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

        file = fopen("roominfo.txt", "w");
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


void quickSort(Employee employees[], int left, int right) {
    if (left < right) {
        int pivot = partition(employees, left, right);

        quickSort(employees, left, pivot - 1);

        quickSort(employees, pivot + 1, right);
    }
}


void quickSortRoom(Room rooms[], int left, int right) {
    if (left < right) {
        int pivot = partitionRoom(rooms, left, right);

        quickSortRoom(rooms, left, pivot - 1);

        quickSortRoom(rooms, pivot + 1, right);
    }
}


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


void bse() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    file = fopen("empinfo.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address, employees[numEmployees].Email);
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


void ede() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    file = fopen("empinfo.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address, employees[numEmployees].Email);
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

        file = fopen("empinfo.txt", "w");
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


void dle() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    file = fopen("empinfo.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file) && numEmployees < MAX_EMPLOYEES) {
        sscanf(line, "%d,%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%s",
               &employees[numEmployees].ID, employees[numEmployees].Name, &employees[numEmployees].Age,
               employees[numEmployees].Gender, employees[numEmployees].Job, employees[numEmployees].Salary,
               employees[numEmployees].Phone, employees[numEmployees].Address, employees[numEmployees].Email);
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

        file = fopen("empinfo.txt", "w");
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


void edr() {
    FILE *file;
    char line[MAX_LINE_LENGTH];
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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

        file = fopen("roominfo.txt", "w");
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


// Function to show all rooms
void showAllRooms(){
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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
//    for (int i = 0; i < numRooms; i++) {
//        displayRoom(rooms[i]);
//    }

    fclose(file);
}


void swap(Room *a, Room *b) {
    Room temp = *a;
    *a = *b;
    *b = temp;
}


// Function to swap two rooms with bubble sort using discounted price
void bubbleSort(Room arr[], int n) {
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
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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

    bubbleSort(rooms, numRooms);
    displayRoom(rooms[numRooms]);

    fclose(file);
}


// Function to show all bookings
void showAllBookings(){
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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

    fclose(file);
}


// Function to search booking
void searchBooking(){
    FILE *file;
    char line[MAX_LINE_LENGTH];
    char *token;
    Room rooms[MAX_ROOMS];
    int numRooms = 0;

    file = fopen("roominfo.txt", "r");
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
    //searchRoomID();

    fclose(file);
}