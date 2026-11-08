#include <stdio.h>

struct Employee {
    int id;
    char name[50];
    float basicSalary;
};

float calculateTax(float salary) {

    if (salary <= 20000)
        return 0;

    else if (salary <= 40000)
        return salary * 0.05;

    else
        return salary * 0.10;
}

void addEmployee() {

    struct Employee e;

    printf("\nEnter Employee ID: ");
    scanf("%d", &e.id);

    printf("Enter Employee Name: ");
    scanf(" %49[^\n]", e.name);

    printf("Enter Basic Salary: ");
    scanf("%f", &e.basicSalary);

    if (e.basicSalary < 0) {
        printf("Invalid salary!\n");
        return;
    }

    FILE *fp = fopen("employees.txt", "a");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fprintf(fp, "%d|%s|%.2f\n",
            e.id, e.name, e.basicSalary);

    fclose(fp);

    printf("Employee added successfully!\n");
}

void displayPayroll() {

    struct Employee e;
    char line[200];

    FILE *fp = fopen("employees.txt", "r");

    if (fp == NULL) {
        printf("No employee records found!\n");
        return;
    }

    float totalPayroll = 0;

    printf("\n===== EMPLOYEE PAYROLL REPORT =====\n");

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line, "%d|%49[^|]|%f",
                   &e.id, e.name, &e.basicSalary) == 3) {

            float allowance = e.basicSalary * 0.10;
            float deduction = e.basicSalary * 0.05;

            float grossSalary =
                e.basicSalary + allowance;

            float tax = calculateTax(grossSalary);

            float netSalary =
                grossSalary - deduction - tax;

            printf("\nEmployee ID: %d\n", e.id);
            printf("Name: %s\n", e.name);
            printf("Basic Salary: Rs. %.2f\n", e.basicSalary);
            printf("Allowance: Rs. %.2f\n", allowance);
            printf("Deduction: Rs. %.2f\n", deduction);
            printf("Tax: Rs. %.2f\n", tax);
            printf("Net Salary: Rs. %.2f\n", netSalary);

            totalPayroll += netSalary;
        }
    }

    printf("\nTotal Payroll: Rs. %.2f\n", totalPayroll);

    fclose(fp);
}

int main() {

    int choice;

    do {

        printf("\n===== PAYROLL MANAGEMENT =====\n");
        printf("1. Add Employee\n");
        printf("2. Generate Payroll Report\n");
        printf("3. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addEmployee();
                break;

            case 2:
                displayPayroll();
                break;

            case 3:
                printf("Exiting Payroll System!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 3);

    return 0;
}
