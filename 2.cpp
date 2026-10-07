#include <iostream>
using namespace std;

class Employee
{
public:
	virtual double calculateSalary() = 0;

};

class FullTimeEmployee : public Employee
{
private:
	double fixedSalary;
	
public:
	FullTimeEmployee(double fs)
	{
		fixedSalary = fs;
	}

	double calculateSalary() override
	{
		return fixedSalary;
	}
};

class PartTimeEmployee : public Employee
{
private:
	double hourWorked;
	double hourlyRate;

public:
	PartTimeEmployee(double hw,double hr)
	{
		hourWorked = hw;
		hourlyRate = hr;
	}

	double calculateSalary() override
	{
		return hourWorked * hourlyRate;
	}
};

int main()
{
	FullTimeEmployee fullTime(50000);

	PartTimeEmployee partTime(80, 5000);

	cout << "Full-Time Employee Salary: " << fullTime.calculateSalary() << endl;

	cout << "Part-Time Employee Salary: " << partTime.calculateSalary() << endl;
}