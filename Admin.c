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