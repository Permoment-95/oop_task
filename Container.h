#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template<class T>
class Container
{
public:

	Container();
	Container(uint32_t size);
	Container(Container<T> const& other);

	T & operator[] (uint32_t index) const;
	
	void push_back(T const& value);
	void pop_back();
	void store(uint32_t capacity);

	void print(ostream& stream) const;

	uint32_t size() const
	{
		return m_size;
	}

	bool is_empty() const
	{
		return m_size == 0;
	}

	void clear();

private:
	uint32_t m_size, m_capacity;
	uint8_t* buffer;

};


template<class T>
Container<T>::Container()
{
	m_size = 0;
	m_capacity = 0;
	buffer = new uint8_t[m_capacity * sizeof(T)];
}

template<class T>
Container<T>::Container(uint32_t size)
{
	m_size = 0;
	m_capacity = size;
	buffer = new uint8_t[m_capacity * sizeof(T)];
}

template<class T>
Container<T>::Container(Container<T> const& other)
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	buffer = new uint8_t[m_capacity * sizeof(T)];

	for (uint32_t i = 0; i < m_size; i++)
	{
		buffer = new(buffer + i * sizeof(T)) T(other[i]);
	}
}

template<class T>
T& Container<T>::operator [] (uint32_t index) const
{
	if (index >= m_size) throw exception("Invalid memory access.\n");
	return (T&)buffer[index * sizeof(T)];
}

template<class T>
void Container<T>::push_back(T const& value)
{
	if (m_size == m_capacity)
	{
		store(m_capacity * 2 + 1);
	}
	new(buffer + m_size * sizeof(T)) T(value);
	m_size++;
}

template<class T>
void Container<T>::pop_back()
{
	if (is_empty()) throw exception("Invalid memory access.\n");

	this->operator[](m_size - 1).~T();
	m_size--;
}

template<class T>
void Container<T>::store(uint32_t capacity)
{
	if (m_capacity > capacity) return;
	uint8_t* tmp = new uint8_t[capacity * sizeof(T)];
	m_capacity = capacity;
	if (m_size != 0)
	{
		for (uint32_t i = 0; i < m_size * sizeof(T); i++)
		{
			tmp[i] = buffer[i];
		}
	}
	delete[] buffer;
	buffer = tmp;
}

template<class T>
void Container<T>::print(std::ostream& stream) const
{
	stream << "Size: " << size() << std::endl;
	stream << "Empty: " << is_empty() << std::endl;
	uint32_t s = size();
	for (uint32_t i = 0; i < s; i++)
	{
		stream << *((T&)buffer[i * sizeof(T)]) << std::endl;
	}
}

template<class T>
void Container<T>::clear()
{
	uint32_t s = size();
	for (uint32_t i = 0; i < s; i++)
	{
		pop_back();
	}
	m_size = 0;
	m_capacity = 0;
	delete[] buffer;
}
