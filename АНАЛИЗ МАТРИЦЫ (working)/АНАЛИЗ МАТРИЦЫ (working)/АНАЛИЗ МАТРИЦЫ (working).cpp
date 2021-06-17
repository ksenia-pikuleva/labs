// АНАЛИЗ МАТРИЦЫ (working).cpp 

#include "pch.h"
#include <stdio.h> //
#include <Windows.h> //
#include <iostream>
using namespace std;

// ПЕРЕМЕННЫЕ:
int op;
int x, y;
bool res, s, a_s, r, a_r, t;
const int n = 5; 
int arr[n][n];

// ВВОД ЭЛЕМЕНТОВ:
void input()
{
	for (int i = 0; i < n; ++i) // зануляем всю матрицу
	{for (int j = 0; j < n; ++j)
		arr[i][j] = 0;}

	cout << " Введите элементы отношения (ч/з пробел):" << endl;
	do
	{
		scanf_s("%d%*c%d", &x, &y);
		arr[x][y] = 1;
	} while (x != 0);

	
	cout << " ввод завершен" << endl;
	cout << " Матрица:" << endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //*
	SetConsoleTextAttribute(hConsole, (WORD)((15 << 4) | 0)); //*
	for (int i = 1; i < n; ++i) 
	{  
		cout << "\t ";
		for (int j = 1; j < n; ++j)
			cout << arr[i][j] << " ";
		cout << endl; 
	}
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 15) | 15)); //* настроить
}

// СВОЙСТВА:

// рефлексивность
void reflex()
{
	r = false;
	res = true;
	for (int i = 1; i < n; ++i)
	{
		if (arr[i][i] == 0) res = false;
	}
	if (res == true) { cout << "\tрефлексивное - ДА"; r = true; }
	else cout << "\tрефлексивное - НЕТ";
	cout << endl;
}

// антирефлексивность 
void a_reflex()
{
	a_r = false;
	res = true;
	for (int i = 1; i < 5; ++i)
	{
		if (arr[i][i] == 1) res = false;
	}
	if (res == true) { cout << "\tантирефлексивное - ДА"; a_r = true; }
	else cout << "\tантирефлексивное - НЕТ";
	cout << endl;
}

// симметричность  
void symmetr()
{
	res = true;
	s = false;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			{
				if (arr[j][i] != arr[i][j]) res = false;
			}
		}
	}
	if (res) { cout << "\tсимметричное - ДА"; s = true;}
	else cout << "\tсимметричное - НЕТ";
	cout << endl;

}

//антисимметричность
void a_symmetr()
{
	res = true;
	a_s = false;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (i != j) 
			{
				if (arr[i][j] == 1)
				{ 
					if (arr[j][i] == 1) res = false;
				}
			}
		}
	}
	if (res) { cout << "\tантисимметричное - ДА";  a_s = true; }
	else cout << "\tантисимметричное - НЕТ"; 
	cout << endl;
}

// транзитивность 
void transit()
{
	t = false;
	res = true;
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (arr[i][j] == 1)
			{
				for (int k = 1; k < n; ++k)
				{
					if (arr[j][k] == 1 && arr[i][k] != 1) res = false;
				}
			}
		}
	}
	if (res == true) { cout << "\tтранзитивное - ДА"; t = true; }
	else cout << "\tтранзитивное - НЕТ"; 
	cout << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	cout << endl << "***************************************** АНАЛИЗ МАТРИЦЫ БИНАРНОГО ОТНОШЕНИЯ *******************************************" << endl;
	cout << endl << " Матрица задана на множестве A = { 1, 2, 3, 4 }" << endl;
	cout << endl << "************************************************************************************************************************" << endl;


	do
	{
		input();
		cout << endl;

		reflex();
		a_reflex();
		symmetr();
		a_symmetr();
		transit();
		cout << endl;

		if ((r == true) && (s == true) && (t == true)) cout << " ~ Отношение эквивалентности" << endl; 
		if ((r == true) && (s == true)) cout << " ~ Отношение толерантности" << endl; 
		if ((a_s==true)&&(t==true)) cout << " ~ Отношение порядка" << endl; 
		if ((a_r==true)&&(a_s==true)&&(t==true)) cout << " ~ Отношение строгого порядка" << endl; 
		if ((r==true)&&(a_s==true)&&(t==true)) cout << " ~ Отношение нестрогого порядка" << endl; 

		cout << "\t\t\t\t\t\t\t\t\t\t\t новое отношение / выход:";
		cin >> op;
	} while (op != 0);
	return 0;
}

