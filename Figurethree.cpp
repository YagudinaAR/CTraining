#include <iostream>
#include <typeinfo>

using namespace std;

class Figure
{
	Figure* p;
public:
	Figure() : p(0) { }
	Figure(Figure* pN);
	virtual void print(double x, double y, double z) { p->print(x,y,z); }
	virtual ~Figure()
	{
		delete p;
		p = 0;
		cout << "delete figure" << endl;
	}

};

class Triangle : public Figure
{
public:
	virtual void print(double x, double y, double z)
	{
		double p = x + y + z;
		cout << "Type of figure is triangle" << endl;
		cout << "Perimeter: " << p << endl;
		cout << "Square: " << sqrt(p * (p - x) * (p - y) * (p - z)) << endl;
		cout << endl;
	}
};

class Rectangle : public Figure
{
public:
	virtual void print(double x, double y, double z = 0)
	{
		cout << "Type of figure is rectangle" << endl;
		cout << "Perimeter: " << 2 * (x + y) << endl;
		cout << "Square: " << x * y << endl;
		cout << endl;
	}
};

class Cube : public Figure
{
public:
	virtual void print(double x, double y = 0, double z = 0)
	{
		cout << "Type of figure is cube" << endl;
		cout << "Perimeter: " << 4 * x << endl;
		cout << "Square: " << x * x << endl;
		cout << endl;
	}
};
Figure::Figure(Figure* pN)
{

	if (typeid(*pN) == typeid(Triangle))
	{
		cout << "create triangle" << endl;
		p = new Triangle;
	}

	else if (typeid(*pN) == typeid(Rectangle))
	{
		cout << "create rectangle" << endl;
		p = new Rectangle;
	}

	else if (typeid(*pN) == typeid(Cube))
	{
		cout << "create cube" << endl;
		p = new Cube;
	}

	else cout << "error" << endl;

}

int main()
{
	Triangle* tr = new Triangle;
	Rectangle* rc = new Rectangle;
	Cube* cb = new Cube;
	Figure* f1 = new Figure(tr);
	Figure* f2 = new Figure(rc);
	Figure* f3 = new Figure(cb);
	tr->print(5,5,3);
	rc->print(4,6);
	cb->print(3);
	delete tr;
	delete rc;
	delete cb;
	return 0;
}