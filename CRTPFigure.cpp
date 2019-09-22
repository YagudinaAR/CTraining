#include <iostream>
#include <math.h>

using namespace std;

template<class T>
class IFigure
{
    protected:
	double x = 0.0f;
	double y = 0.0f;
	double z = 0.0f;
public:
	void setParameters(double i, double j = 0, double k = 0)
	{
		x = i;
		y = j;
		z = k;
	}
    void print()
    {
        static_cast<T*>(this)->print_info();
    }
};

class Triangle : public IFigure<Triangle>
{
public:
     void print_info()
	{
		double p = x + y + z;
		cout << "Type of figure is triangle" << endl;
		cout << "Perimeter: " << p << endl;
		cout << "Square: " << sqrt(p * (p - x) * (p - y) * (p - z)) << endl;
		cout << endl;
	}
};

class Rectangle : public IFigure<Rectangle>
{
public:
	void print_info()
	{
		cout << "Type of figure is rectangle" << endl;
		cout << "Perimeter: " << 2 * (x + y) << endl;
		cout << "Square: " << x * y << endl;
		cout << endl;
	}
};
class Cube : public IFigure<Cube>
{
public:
	void print_info()
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
	tr.print_info();
	rc.print_info();
	cb.print_info();
	return 0;
}