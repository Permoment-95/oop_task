#pragma once
#include "Base.h"
#include "Container.h"
#include "string"
#include "corecrt_math_defines.h"

using namespace std;

class Shape : public Printable
{
public:

	Shape() { sm_shapes++; }

	Shape(string const& name)
	{
		sm_shapes++;
	}

	virtual ~Shape()
	{
		sm_shapes--;
	}

	virtual void print(ostream& out) const = 0;

	friend ostream& operator << (ostream& ioStream, Shape const& p)
	{
		//ioStream << p << "\n";
		p.print(ioStream);
		return ioStream;
	}

	static int getCount()
	{
		return sm_shapes;
	}
private:
	static int sm_shapes;
};


int Shape::sm_shapes = 0;

class Point : public Shape, Named
{
public:
	Point(float x, float y) : Named("Point")
	{
		m_x = x;
		m_y = y;
	}

	float X() const
	{
		return m_x;
	}


	float Y() const
	{
		return m_y;
	}
	void print(ostream& out) const
	{
		out << m_name << endl;
		out << "(" << m_x << ", " << m_y << ")" << endl;
	}

private:
	float m_x, m_y;
};

class Circle : public Shape, Named
{
public:
	Circle(float radius, Point& p) : Named("Circle"), m_center(p), m_radius(radius)
	{
		m_area = (float)M_PI * m_radius * m_radius;
	}
	~Circle() { };


	void print(ostream& out) const
	{
		out << m_name << endl;
		m_center.print(out);
		out << "Radius: " << m_radius << " Area: " << m_area << endl;
	}

private:
	float m_radius, m_area;
	Point m_center;
};

class Rectangle : public Shape, Named
{
public:
	Rectangle(Point& x1, Point& x2) : Named("Rectangle"), m_x1(x1), m_x2(x2)
	{
		m_area = abs((m_x1.X() - m_x2.X()) * (m_x2.Y() - m_x1.Y()));
	}
	~Rectangle() { }
	void print(ostream& out) const
	{
		out << m_name << endl;
		m_x1.print(out);
		m_x2.print(out);
		out << "Area: " << m_area << endl;
	}
private:
	Point m_x1,  m_x2;
	float m_area;
};

class Square : public Shape, Named
{
public:
	Square(Point& center, float side) : Named("Square"), m_center(center), m_side(side)
	{
		m_area = side * side;
	}

	~Square() {}
	void print(ostream& out) const
	{
		out << m_name << endl;
		m_center.print(out);
		out << "Area: " << m_area << endl;
	}
private:
	Point m_center;
	float m_side, m_area;
};

class Polyline : public Shape, Named
{
public:
	Polyline(Container<Point*>& points) : m_length(0), m_points(&points), Named("Polyline")
	{
		if (m_points->size() == 0) return;
		calcLength();
	}

	~Polyline()
	{
		uint32_t s = m_points->size();
		for (uint32_t i = 0; i < s; i++)
		{
			delete (*m_points)[i];
		}
		delete m_points;
	}


	void addPoint(Point& p)
	{
		m_points->push_back(&p);
		uint32_t s = m_points->size();
		if (s <= 1) return;
		Point* p1 = (*m_points)[m_points->size() - 1];
		Point* p2 = (*m_points)[m_points->size() - 2];

		m_length += sqrt(pow(p1->Y() - p2->Y(), 2)
			+ pow(p1->X() - p2->X(), 2));
	}

	void calcLength()
	{
		uint32_t size = m_points->size() - 1;
		for (uint32_t i = 0; i < size; i++)
		{
			Point* p1 = (*m_points)[i];
			Point* p2 = (*m_points)[i + 1];

			m_length += sqrt(pow(p1->Y() - p2->Y(), 2)
				+ pow(p1->X() - p2->X(), 2));
		}
	}

	Point& getStartPoint() const 
	{ 
		return *(*m_points)[0]; 
	}

	float getLength() const 
	{ 
		return m_length; 
	}

	void print(ostream& out) const
	{
		out << m_name << endl;
		for (uint32_t i = 0; i < m_points->size(); i++)
		{
			(*m_points)[i]->print(out);
		}
		out << "Length: " << getLength() << endl;
	}
private:
	Container<Point*>* m_points;
	float m_length;
};

class Polygon : public Shape, Named
{
public:
	Polygon(Polyline& shape) : m_shape(&shape), Named("Polygon")
	{
		Point* startPoint = new Point(shape.getStartPoint().X(), shape.getStartPoint().Y());
		shape.addPoint(*startPoint);
	}

	~Polygon() 
	{ 
		delete m_shape; 
	}
	void print(ostream& out) const 
	{ 
		out << m_name << endl;
		m_shape->print(out); 
	}
private:
	Polyline* m_shape;
};