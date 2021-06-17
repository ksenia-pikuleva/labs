#pragma once
#include <iostream>
#include "Vector.h"
using namespace std;

template <class T>
class Vector
{
public:
	Vector(int s, T k)                     // с параметрами 
	{
		size = s;
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = k;
	}
	Vector(const Vector<T>&a)              // конструктор копирования
	{
		size = a.size;
		data = new T[size];
		for (int i = 0; i < size; i++)
			data[i] = a.data[i];
	}
	~Vector()                              // деструктор
	{
		delete[] data;
		data = 0;
	}

	Vector& operator=(const Vector<T>&a);    // оператор присваивания


	T&operator[](int index)                // операция доступа по индексу
	{
		if (index < size) return data[index];
		else cout << " Ошибка! введенный индекс больше размера вектора" << endl;
	}

	Vector operator *(const T k)           // умножение на константу
	{
		Vector<T> temp(size, k);
		for (int i = 0; i < size; i++)
			temp.data[i] = data[i] * k;
		return temp;
	}
	int operator()()                       // возвращает длину вектора
	{
		return size;
	}

	friend std::ostream& operator<<(std::ostream& out, const Vector<T>&a)  // вывод 
	{
		for (int i = 0; i < a.size; ++i)
			out << a.data[i] << " ";
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector<T>&a)  // ввод
	{
		for (int i = 0; i < a.size; ++i)
			in >> a.data[i];
		return in;
	}

private:
	int size; // размер вектора
	T*data;   // указатель на динамический массив значений
};





