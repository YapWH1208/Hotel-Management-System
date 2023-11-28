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

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]",
               employees[count].id, employees[count].name, employees[count].age,
               employees[count].gender, employees[count].job, employees[count].salary,
               employees[count].phone, employees[count].address, employees[count].email);
        count++;
    }

    fclose(file);
    return count;
}

void deleteEmployee(char* empId, int count) {
    int i, found = 0;

    for (i = 0; i < count; ++i) {
        if (strcmp(employees[i].id, empId) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        for (int j = i; j < count - 1; ++j) {
            strcpy(employees[j].id, employees[j + 1].id);
            strcpy(employees[j].name, employees[j + 1].name);
            strcpy(employees[j].age, employees[j + 1].age);
            strcpy(employees[j].gender, employees[j + 1].gender);
            strcpy(employees[j].job, employees[j + 1].job);
            strcpy(employees[j].salary, employees[j + 1].salary);
            strcpy(employees[j].phone, employees[j + 1].phone);
            strcpy(employees[j].address, employees[j + 1].address);
            strcpy(employees[j].email, employees[j + 1].email);
        }

        count--;
        printf("Employee with ID %s deleted successfully.\n", empId);


        FILE *file = fopen("empinfo.txt", "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        for (i = 0; i < count; ++i) {
            fprintf(file, "%s, %s, %s, %s, %s, %s, %s, %s, %s\n", employees[i].id,
                    employees[i].name, employees[i].age, employees[i].gender,
                    employees[i].job, employees[i].salary, employees[i].phone,
                    employees[i].address, employees[i].email);
        }

        fclose(file);
    } else {
        printf("Employee with ID %s not found.\n", empId);
    }
}

int main() {
    const char *filename = "empinfo.txt";
    int count = readEmployeesFromFile(filename);
    if (count == -1) {
        return 1;
    }

    char empId[10];
    printf("Enter the ID of the employee you want to delete: ");
    scanf("%s", empId);

    deleteEmployee(empId, count);

    return 0;
}
