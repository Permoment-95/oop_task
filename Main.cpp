#include <iostream>
#include "Container.h"
//#include "Shapes.h"
#include "ShapeFactory.h"
#include <time.h>

using namespace std;

int main()
{

    srand((uint32_t)time(NULL));

    Container<shared_ptr<Shape>> shapes;

	for (uint8_t i = 0; i < 5; i++)
	{
		try
		{
			shared_ptr<Shape> s = ShapeFactory::makeShape(
				ShapeType(i % (uint8_t)ShapeType::LENGTH));
			shapes.push_back(s);
		}

		catch (exception e)
		{
			cout << e.what();
		}
	}
	
	shapes.print(cout);
	cout << Shape::getCount() << endl;
	shapes.clear();
	cout << Shape::getCount() << endl;

}
