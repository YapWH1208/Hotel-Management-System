#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_LINE_LENGTH 200

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char job[50];
    float salary;
    char phone[20];
    char address[100];
    char email[50];
} Employee;

Employee employees[MAX_EMPLOYEES];


int readEmployeesFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d %[^,], %d, %[^,], %[^,], $%f, %[^,], %[^,], %s", &employees[count].id, employees[count].name, &employees[count].age,
               employees[count].gender, employees[count].job, &employees[count].salary, employees[count].phone,
               employees[count].address, employees[count].email);
        count++;
    }

    fclose(file);
    return count;
}


int binarySearch(int id, int low, int high) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        if (employees[mid].id == id) {
            return mid;
        } else if (employees[mid].id > id) {
            return binarySearch(id, low, mid - 1);
        } else {
            return binarySearch(id, mid + 1, high);
        }
    }
    return -1;
}

//int main() {
//    const char *filename = "empinfo.txt";
//    int employeeCount = readEmployeesFromFile(filename);
//
//    if (employeeCount <= 0) {
//        printf("No employees found or error reading the file.\n");
//        return 1;
//    }
//
//    int searchID;
//    printf("Enter the Employee ID to search: ");
//    scanf("%d", &searchID);
//
//    int result = binarySearch(searchID, 0, employeeCount - 1);
//
//    if (result == -1) {
//        printf("Employee with ID %d not found.\n", searchID);
//    } else {
//        printf("Employee found:\n");
//        printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nJob: %s\nSalary: $%.2f\nPhone: %s\nAddress: %s\nEmail: %s\n",
//               employees[result].id, employees[result].name, employees[result].age, employees[result].gender,
//               employees[result].job, employees[result].salary, employees[result].phone, employees[result].address,
//               employees[result].email);
//    }
//
//    return 0;
//}
