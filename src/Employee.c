#include "EmpStruct.h"

void deleteEmp(EMPLOYEE** employee)
{
	free(*employee);
	*employee = null;
}
EMPLOYEE* createEmp(char* name, double salary, int ID)
{
	EMPLOYEE *emp = (EMPLOYEE *)malloc(sizeof(EMPLOYEE));
	emp->ID = ID;

	if (strlen(name) > empSize) {name[empSize] = 0;}
	strcpy(emp->name, name);
	emp->salary = salary;
	return emp;
}
char* printEmp(EMPLOYEE* employee, char* output)
{
	sprintf(output, "%5d %15s %8.2f", employee->ID, employee->name, employee->salary);
	return output;
}