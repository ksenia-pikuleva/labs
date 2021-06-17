// КАЛЬКУЛЯТОР МНОЖЕСТВ working.cpp 
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// МНОЖЕСТВА
int n; // кол-во элементов в мн-ве
vector <int> vA; // мн-во A (вектор)
vector <int> vB; // мн-во В (вектор)
vector <int> vC; // мн-во С (вектор)
vector <int> v1, v2, vU; // вектора функций
const char *first;
const char *second;

// УНИВЕРСУМ:
void input_univer(vector <int> &vU)
{
	for (int i = 1; i <= 100; i++)
	{
		int a = i;
		vU.push_back(a);
	}
	std::sort(vU.begin(), vU.end());
}

// ФУНКЦИИ ЗАДАНИЯ МНОЖЕСТВ:
void input_keyboard(vector <int> &v1)
{
	cout << "   кол-во элементов множества: "; 
	cin >> n;
	cout << "   введите элементы ч/з enter" << endl;
	for (int i = 0; i < n; i++)
	{
		int a; // переменная со значением элемента
		cin >> a;
		v1.push_back(a);
	}
	sort(v1.begin(), v1.end());
}
void input_random(vector <int> &v1) 
{
	cout << "   кол-во элементов множества: "; 
	cin >> n; 
	for (int i = 1; i <= 100; i++)
	{
		v1.push_back(i);
	}
	random_shuffle(v1.begin(), v1.end());
	v1.resize(n);
	sort(v1.begin(), v1.end()); 
	
}
void input_formula(vector <int> &v1) 
{
	int p; // переменная кратности для всех элементов мн-ва
	cout << "   элементы множества кратны (число > 0): ";
	cin >> p;
	cout << "   кол-во элементов множества: ";
	cin >> n;
	for (int i = 1; i <= 100; i++)
	{ 
		if(i%p==0) v1.push_back(i);
	}
	random_shuffle(v1.begin(), v1.end());
	v1.resize(n);
	sort(v1.begin(), v1.end());
}

// ФУНКЦИЯ ПЕЧАТИ МНОЖЕСТВА:
void output(vector <int> &v1)
{
	for (int i = 0; i < n; i++)
	{
		cout << v1[i] << " ";
	}
	cout << "}" << endl;
}

// ФУНКЦИИ ОПЕРАЦИЙ С МНОЖЕСТВАМИ:
// объединение 
void mergerF(vector <int> v1, vector <int> v2)
{
	bool emp = false;
	v1.insert(v1.end(), v2.begin(), v2.end()); // заливаем в один вектор
	sort(v1.begin(), v1.end()); // сортировка по возрастанию
	auto iter = std::unique(v1.begin(), v1.end()); // итератор на unique
	v1.erase(iter, v1.end()); // удаляем одинаковые
	cout << "{ ";
	for (int i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " "; // выводим результат
		emp = true;
	}
	if (emp == false) cout << "пустое множество ";
	cout <<"}"<< endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}
// пересечение
void crossF(vector <int> v1, vector <int> v2)
{
	bool emp = false;
	cout << "{ ";
	for (std::vector<int>::iterator it1 = v1.begin(), it1_end = v1.end(); it1 < it1_end; ++it1)
	{
		for (std::vector<int>::iterator it2 = v2.begin(), it2_end = v2.end(); it2 < it2_end; ++it2)
		{
			if (*it1 == *it2) {
				cout << *it2 << " "; emp = true;
			}
		}
	}
	if (emp == false) cout << "пустое множество ";
	cout << "}" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}
// разность
void difF(vector <int> v1, vector <int> v2)
{
	bool emp = false;
	bool f = false;
	cout << "{ ";
	for (std::vector<int>::iterator it1 = v1.begin(), it1_end = v1.end(); it1 < it1_end; ++it1)
	{
		for (std::vector<int>::iterator it2 = v2.begin(), it2_end = v2.end(); it2 < it2_end; ++it2)
		{
			if (*it1 == *it2) { f = true;  break; }
		}
		if (f == false) { cout << *it1 << " "; emp = true;
		}
		f = false;
	}
	if (emp == false) cout << "пустое множество ";
	cout << "}" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}
// симметрическая разность
void symdifF(vector <int> v1, vector <int> v2)
{
	bool emp = false;
	bool f = false;
	cout << "{ ";
	for (std::vector<int>::iterator it1 = v1.begin(), it1_end = v1.end(); it1 < it1_end; ++it1)
	{
		for (std::vector<int>::iterator it2 = v2.begin(), it2_end = v2.end(); it2 < it2_end; ++it2)
		{
			if (*it1 == *it2) { f = true; break; }
		}
		if (f == false) { cout << *it1 << " "; emp = true;
		}
		f = false;
	}
	for (std::vector<int>::iterator it2 = v2.begin(), it2_end = v2.end(); it2 < it2_end; ++it2)
	{
		for (std::vector<int>::iterator it1 = v1.begin(), it1_end = v1.end(); it1 < it1_end; ++it1)
		{
			if (*it2 == *it1) { f = true; break; }
		}
		if (f == false) { cout << *it2 << " "; }
		f = false;
	}
	if (emp == false) cout << "пустое множество ";
	cout << "}" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}
// дополнение до универсума
void univF(vector <int> vU, vector <int> v1)
{
	bool emp = false;
	bool f = false;
	cout << "{ ";
	for (std::vector<int>::iterator itU = vU.begin(), itU_end = vU.end(); itU < itU_end; ++itU)
	{
		for (std::vector<int>::iterator it1 = v1.begin(), it1_end = v1.end(); it1 < it1_end; ++it1)
		{
			if (*itU == *it1) { f = true; break; }
		}
		if (f == false) { cout << *itU << " "; emp = true;
		}
		f = false;
	}
	if (emp == false) cout << "пустое множество ";
	cout <<"}"<< endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
}

// Ф-Я ВЫБОРА РАБОТАЮЩИХ МНОЖЕСТВ:
void setchoice(int z)
{
	cout << "Выберите 1-е множество: ";
	cin >> z;
	switch (z)
	{
	case 1: v1.assign(vA.begin(), vA.end()); first = "A"; break;
	case 2: v1.assign(vB.begin(), vB.end()); first = "B"; break;
	case 3: v1.assign(vC.begin(), vC.end()); first = "C"; break;
	default: /*cout << "Ошибка ввода" << endl;*/ break;
	}

	cout << "Выберите 2-е множество: ";
	cin >> z;
	switch (z)
	{
	case 1: v2.assign(vA.begin(), vA.end()); second = "A"; break;
	case 2: v2.assign(vB.begin(), vB.end()); second = "B"; break;
	case 3: v2.assign(vC.begin(), vC.end()); second = "C"; break;
	case 0: cout << "Будет выбрана унарная операция" << endl;
	default: /*cout << "Ошибка ввода" << endl;*/ break;
	}
}
// Ф-Я ВЫБОРА ОПЕРАЦИИ:
void operation(int z)
{
	cout << "  Выберите операцию: ";
	cin >> z;
	switch (z)
	{
	case 1: cout << "    ОБЪЕДИНЕНИЕ " << first << " и " << second << ":" << endl; mergerF(v1, v2); break; // объединение
	case 2: cout << "    ПЕРЕСЕЧЕНИЕ " << first << " и " << second << ":" << endl; crossF(v1, v2); break; // пересечение
	case 3: cout << "    РАЗНОСТЬ " << first << " и " << second << ":" << endl; difF(v1, v2); break; // разность
	case 4: cout << "    СИММЕТРИЧЕСКАЯ РАЗНОСТЬ " << first << " и " << second << " " << endl; symdifF(v1, v2); break; // симметрическая разность
	case 5: cout << "    ДОПОЛНЕНИЕ " << first << ":" << endl; input_univer(vU); univF(vU, v1); break; // дополнение
	default: break;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << endl;
	cout << "                                                КАЛЬКУЛЯТОР МНОЖЕСТВ" << endl;
	cout << "***********************************************                      **************************************************" << endl;
	cout << "Способы задания множеств:" << endl;
	cout << "1) Ввод элементов множества с клавиатуры" << endl;
	cout << "2) Заполнение множества случайными числами" << endl;
	cout << "3) Заполнение множества через фомулу кратности" << endl;
	cout << "***********************************************************************************************************************" << endl;
	int z; // z - идентификатор способа задания

	cout << "Выберите способ задания множества А: ";
	cin >> z;
	switch (z)
	{
	case 1: input_keyboard(vA); cout << "Mножество: А = { "; output(vA); break;
	case 2: input_random(vA); cout << "Mножество: А = { "; output(vA); break;
	case 3: input_formula(vA); cout << "Mножество: А = { "; output(vA); break;
	default: cout << "Ошибка ввода" << endl; break;
	}
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

	cout << "Выберите способ задания множества B: ";
	cin >> z;
	switch (z)
	{
	case 1: input_keyboard(vB); cout << "Mножество: B = { "; output(vB); break;
	case 2: input_random(vB); cout << "Mножество: B = { "; output(vB); break;
	case 3: input_formula(vB); cout << "Mножество: B = { "; output(vB); break;
	default: cout << "Ошибка ввода" << endl; break;
	}
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

	cout << "Выберите способ задания множества C: ";
	cin >> z;
	switch (z)
	{
	case 1: input_keyboard(vC); cout << "Mножество: C = { "; output(vC); break;
	case 2: input_random(vC); cout << "Mножество: C = { "; output(vC); break;
	case 3: input_formula(vC); cout << "Mножество: C = { "; output(vC); break;
	default: cout << "Ошибка ввода" << endl; break;
	}
	cout << "***********************************************************************************************************************" << endl << endl;

	cout << "                                                    о п е р а ц и и" << endl << endl;
	cout << "   1) объединение" << endl;
	cout << "   2) пересечение" << endl;
	cout << "   3) разность" << endl;
	cout << "   4) симметрическая разность" << endl;
	cout << "   5) дополнение (унарная операция, код 0)" << endl << endl;
	cout << "***********************************************************************************************************************" << endl << endl;

	int op;
	do {
		setchoice(z);
		do {
			operation(z);
			cout << endl << "                                                                     [ другая операция (1) ]" << endl;
			cout << "                                                                     [ другие множества (2) ]" << endl;
			cin >> op;
			if (op == 0) cout << "Калькулятор завершает работу";
		} while (op == 1);
	} while (op == 2);
	
	return 0;
}
