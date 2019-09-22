#include <iostream>

using namespace std;

enum figure_ID { triangle_id, rectangle_id, cube_id };

class FigureFactory
{
	FigureFactory* p;
public:
	FigureFactory() : p(nullptr) { }
	FigureFactory(figure_ID id);
	virtual void print() { p->print(); }
	virtual ~FigureFactory() { delete p; p = 0; }

};

class Triangle : public FigureFactory
{
public:
	//Triangle() : FigureFactory() {}
	virtual void print()
	{
		cout << "Type of figure is triangle" << endl;
	}
};

class Rectangle : public FigureFactory
{
public:
	virtual void print()
	{
		cout << "Type of figure is rectangle" << endl;
	}
};

class Cube : public FigureFactory
{
public:
	virtual void print()
	{
		cout << "Type of figure is cube" << endl;
	}
};
FigureFactory::FigureFactory(figure_ID id)
{
	if (id == triangle_id) p = new Triangle;
	if (id == rectangle_id) p = new Rectangle;
	if (id == cube_id) p = new Cube;
	else return;
}

int main()
{
	FigureFactory* tr = new FigureFactory(triangle_id);
	FigureFactory* rc = new FigureFactory(rectangle_id);
	FigureFactory* cb = new FigureFactory(cube_id);
	tr->print();
	rc->print();
	cb->print();
	return 0;
}