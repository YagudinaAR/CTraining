#include <iostream>
#include <math.h>

using namespace std;

class IFigure
{
protected:
	double x;
	double y;
	double z;
public:
	void setParameters(double i, double j = 0, double k = 0)
	{
		x = i;
		y = j;
		z = k;
	}
	virtual void print() = 0;
};

class Triangle : public IFigure
{
public:
	virtual void print()
	{
		double p = x + y + z;
		cout << "Type of figure is triangle" << endl;
		cout << "Perimeter: " << p << endl;
		cout << "Square: " << sqrt(p * (p - x) * (p - y) * (p - z)) << endl;
		cout << endl;
	}
};

class Rectangle : public IFigure
{
public:
	virtual void print()
	{
		cout << "Type of figure is rectangle" << endl;
		cout << "Perimeter: " << 2 * (x + y) << endl;
		cout << "Square: " << x * y << endl;
		cout << endl;
	}
};
class Cube : public IFigure
{
public:
	virtual void print()
	{
		cout << "Type of figure is cube" << endl;
		cout << "Perimeter: " << 4 * x << endl;
		cout << "Square: " << x * x << endl;
		cout << endl;
	}
};
int main()
{
	Triangle tr;
	Rectangle rc;
	Cube cb;
	tr.setParameters(3, 3, 5);
	rc.setParameters(3, 5);
	cb.setParameters(3);
	tr.print();
	cb.print();
	rc.print();
	return 0;
}