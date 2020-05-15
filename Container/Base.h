#pragma once
#include <string>
#include <iostream>

using namespace std;

class Printable
{
public:
	virtual void print(ostream& out) const = 0;
};

class Named : Printable
{
public:
	Named(string const & name)
	{
		m_name = name;
	}

protected:
	string m_name;
};