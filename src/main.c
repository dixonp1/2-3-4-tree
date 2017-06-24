#include "EmpStruct.h"

int getInt(char*, int, int);
double getDouble(char*, int, int);
void getString(char*, char*, int);
void help();
void outputEmployee(EMPLOYEE*, char*);

int main(void)
{
	double salary;
	char name[empSize + 1];
	char output[line + 1];
	EMPLOYEE* employee;
	TREE empList;

	char* names[] = { "bill", "john", "mary", "sally", "peter", "pat" };
	int id, i, nameCount = 6;

	initializeTree(&empList);
	int choice = 0, result = 0;
	help();
	fflush(stdout);

	while (choice != options)
	{
		choice = getInt("Please Enter a number:", 1, options);

		switch (choice)
		{
		case 1:
			getString("Enter the employee name", name, empSize);
			salary = getDouble("Enter the employee salary: ", 10000, 90000);
			if (empList.freeCount == 0){ puts("Employee List Full"); }
			else if ((employee = insert(&empList, name, salary)) == NULL)
				{puts("Insert failed"); }
			else
			{
				printf("%5s %15s %6s", "ID", "Name", "Salary\n\n");
				puts(printEmp(employee, output));
			}
			fflush(stdout);
			break;
		case 2:
			puts("UNDER CONSTRUCTION");
			break;
			id = getInt("Enter the employee ID to be removed:", 0, 100000);
			if (delete(&empList, id))
			printf("\nEmployee %d has been removed \n", id);
			else printf("\nEmployee %d was not found\n", id);
			fflush(stdout);
			break;
		case 3: 
            id = getInt("Enter employee id to display: ", 0, 100000);
			employee = find((&empList)->root, id);
			if (employee == NULL) printf("Employee %d not found", id);
			else {
				printf("%5s %15s %6s", "ID", "Name", "Salary\n\n");
				puts(printEmp(employee, output));
			}
			fflush(stdout);
			break;
		case 4:
			printf("%5s %15s %6s", "ID", "Name", "Salary\n\n");
			if (!traverse(empList.root, outputEmployee))
			{
				puts("Information is empty");
			}
			fflush(stdout);
			break;
		case 5: 
			deleteAll((&empList)->root);
			initializeTree(&empList);
			puts("Employee list reset\n");
			fflush(stdout);
			break;
		case 6:
			result = getInt("Enter the number of employees to create: ", 0, maxEmp);
			for (i = 0; i < result; i++)
			{
				salary = (int)((rand()) % 90000) + 10000;
				int nameKey = (int)((rand()) % nameCount);
				strcpy(name, names[nameKey]);

				if (insert(&empList, name, salary) == NULL)
				{ 
					printf("Only room for %d employees\n", i);
					break;
				}
			}
			puts("Employee list created\n");
			fflush(stdout);
		case 7:
			help();
			break;

		}//end switch
	}//end while
	puts("Exiting Program\n");
	fflush(stdout);
	return EXIT_SUCCESS;
}//end main

double getDouble(char* prompt, int min, int max)
{
	int result = 0;
	double value;
	while (result == 0)
	{
		printf("%s\n", prompt);
		fflush(stdout);
		result = scanf("%lf.2\n", &value);
		if (result == 0) scanf("%s");
		else if (value >= min && value <= max) break;
		result = 0;
	}
	fflush(stdin);
	return value;
	
}
void outputEmployee(EMPLOYEE *employee, char* output)
{
	puts(printEmp(employee, output));
	fflush(stdout);
}
int getInt(char* prompt, int min, int max)
{
	int result = 0;
	int value;
	while (result == 0)
	{
		puts(prompt);
		fflush(stdout);
		result = scanf("%d", &value);
		if (result == 0) scanf("%*s");
		else if (value >= min && value <= max) break;
		result = 0;

		puts("Illegal Entry");
		fflush(stdout);
	} 
	return value;
}
void getString(char* prompt, char* value, int max)
{
	int result = 0;
	while (!result)
	{
		puts(prompt);
		fflush(stdout);
		scanf(" ");
		if (fgets(value, max, stdin))
		{
			int len = strlen(value);
			if (value[len - 1] == '\n')
			{
				value[len - 1] = '\0';
				if (len > 1 && value[len - 2] == '\r') value[len - 2] = '\0';
			}
			else {scanf("%*s");}
			result = 1;
		}
	}
}
void help()
{
	puts("EMPLOYEE MAINTENANCE PROGRAM");
	puts("1) Add Employee");
	puts("2) Remove Employee ----- (under construction)");
	puts("3) Display Employee");
	puts("4) Display Employee List");
	puts("5) Reset List");
	puts("6) Create Initial List");
	puts("7) Help");
	puts("8) Quit");
}