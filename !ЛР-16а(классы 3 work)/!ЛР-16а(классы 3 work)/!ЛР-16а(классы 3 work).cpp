#include "pch.h"
#include <iostream>
#include"Vector.h"
#include "Time.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "\t \t \t \t \t \tЛабораторная работа № 13-а" << endl;
	cout << "\t \t \t \t \t \t  Классы: шаблоны классов" << endl << endl;

	cout << "Тестирование класса Vector" << endl;
	Vector<int> A(5, 0); // инициализация, ввод и вывод значений
	cin >> A; cout << A << endl;
	Vector<int> B(10, 1); //инициализация и вывод значений
	cout << B << endl;
	//B = A; // присваивание
	//cout << B << endl;
	//cout << A[2] << endl; // доступ по индексу
	cout << A() << endl; // получение длины вектора
	//B = A * 10; cout << B << endl; // умножение на константу
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
	cout << "Тестирование класса Time" << endl;

	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
	cout << "Тестирование контейнера Vector типа данных Time" << endl;

	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - "<<endl;


	return 0;
}

