#pragma once
#include <iostream>
#include "Vector.h"
using namespace std;

template <class T>
class Vector
{
public:
	Vector(int s, T k)                     // � ����������� 
	{
		size = s;
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = k;
	}
	Vector(const Vector<T>&a)              // ����������� �����������
	{
		size = a.size;
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];
	}
	~Vector()                              // ����������
	{
		delete[] data;
		data = 0;
	}

	Vector& operator=(const Vector<T>&a);    // �������� ������������


	T&operator[](int index)                // �������� ������� �� �������
	{
		if (index < size) return data[index];
		else cout << " ������! ��������� ������ ������ ������� �������" << endl;
	}

	Vector operator *(const T k)           // ��������� �� ���������
	{
		Vector<T> temp(size, k);
		for (int i = 0; i < size; i++)
			temp.data[i] = data[i] * k;
		return temp;
	}
	int operator()()                       // ���������� ����� �������
	{
		return size;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>&a)  // ����� 
	{
		for (int i = 0; i < a.size; ++i)
			out << a.data[i] << " ";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector<T>&a)  // ����
	{
		for (int i = 0; i < a.size; ++i)
			in >> a.data[i];
		return in;
	}

private:
	int size; // ������ �������
	T*data;   // ��������� �� ������������ ������ ��������
};





