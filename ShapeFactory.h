#pragma once
#include "Shapes.h"
const int MAX_RANGE = 101;

enum class ShapeType
{
    Point,
	Circle,
	Rectangle,
	Square,
	Polyline,
	Polygon,
    LENGTH
};

class ShapeFactory
{
public:
	static shared_ptr<Shape> makeShape(ShapeType type)
	{
		Shape* shape = nullptr;
		switch (type)
		{
		case ShapeType::Point:
		{
			float x = RandomFloat(MAX_RANGE);
			float y = RandomFloat(MAX_RANGE);
			shape = new Point(x, y);
			break;
		}
		case ShapeType::Circle:
		{
			float x = RandomFloat(MAX_RANGE);
			float y = RandomFloat(MAX_RANGE);
			Point* p = new Point(x, y);
			float radius = RandomFloat(MAX_RANGE);
			shape = new Circle(radius, *p);
			break;
		}

		case ShapeType::Rectangle:
		{
			float x1 = RandomFloat(MAX_RANGE);
			float y1 = RandomFloat(MAX_RANGE);

			Point* p1 = new Point(x1, y1);

			float x2 = RandomFloat(MAX_RANGE);
			float y2 = RandomFloat(MAX_RANGE);

			Point* p2 = new Point(x2, y2);

			shape = new Rectangle(*p1, *p2);
			break;
		}
		case ShapeType::Square:
		{
			float x = RandomFloat(MAX_RANGE);
			float y = RandomFloat(MAX_RANGE);
			Point* p = new Point(x, y);
			float sideLength = RandomFloat(MAX_RANGE);
			shape = new Square(*p, sideLength);
			break;
		}
		case ShapeType::Polyline:
		{
			Container<Point*>* container = new Container<Point*>;
			Polyline* tmp = new Polyline(*container);
			uint32_t rand_range = RandomUInt(10);
			for (uint32_t i = 0; i < rand_range; i++)
			{
				float x = RandomFloat(MAX_RANGE);
				float y = RandomFloat(MAX_RANGE);
				Point* p = new Point(x, y);
				tmp->addPoint(*p);
			}
			shape = tmp;
			break;
		}
		case ShapeType::Polygon:
		{
			Container<Point*>* container = new Container<Point*>;
			Polyline* pl = new Polyline(*container);
			uint32_t rand_range = RandomUInt(10);
			for (uint32_t i = 0; i < rand_range; i++)
			{
				float x = RandomFloat(MAX_RANGE);
				float y = RandomFloat(MAX_RANGE);
				Point* p = new Point(x, y);
				pl->addPoint(*p);
			}
			Polygon* p = new Polygon(*pl);
			shape = p;
			break;
		}
		}
		return shared_ptr<Shape>(shape);
	}
    static uint32_t RandomUInt(uint32_t max_range)
	{
		return 1 + rand() / (RAND_MAX / max_range);
	}
	static float RandomFloat(uint32_t max_range)
	{
		return static_cast <float> (rand()) / static_cast <float> (RAND_MAX / max_range);
	}
	
};