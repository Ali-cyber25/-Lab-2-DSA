#include <iostream>
using namespace std;

class Shape
{
public:

	virtual double area() = 0;

};

class Circle : public Shape
{
private:
	double radius;

public:
	Circle(double r)
	{
		radius = r;
	}

	double area() override
	{
		return 3.14159 * radius * radius;
	}
};

class Rectangle : public Shape
{
private:
	double length;
	double width;

public:
	Rectangle(double l, double w)
	{
		length = l;
		width = w;
	}

	double area() override
	{
		return length * width;
	}

};

int main()
{
	Circle c(5);
	Rectangle r(10, 3);

	cout << "Area of Circle: " << c.area() << endl;
	cout << "Area of Rectangle: " << r.area() << endl;
	return 0;
}