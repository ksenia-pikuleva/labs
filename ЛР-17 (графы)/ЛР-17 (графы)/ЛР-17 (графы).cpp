#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "\t \t \t \t \t \tЛабораторная работа № 14" << endl;
	cout << "\t \t \t \t \t \t \t Графы" << endl << endl;
	cout << " Матрица смежномти графа 6 на 6:" << endl;
	int graf[6][6] = {
	{0,5,0,16,0,0},
	{5,0,10,0,0,7},
	{0,10,0,14,20,0},
	{16,0,14,0,0,0},
	{0,0,20,0,0,9},
	{0,7,0,0,9,0}}; // заполняем граф

	for (int count = 0; count < 7; count++) { // вывод графа
		for (int i = 0; i < 7; i++) {
			if (count == 0) printf("%3d ", i);
			else if (i == 0) printf("%3d ", count);
			else printf("%3d ", graf[count - 1][i - 1]);
		}
		cout << endl;
	}



	int d[6]; // минимальное расстояние
	int v[6]; // посещенные вершины
	int temp;
	int minindex, min;
	for (int i = 0; i < 7; i++)
	{
		d[i] = 10000;
		v[i] = 1;
	}
	d[2] = 0;

	do {
		minindex = 10000;
		min = 10000;
		for (int i = 0; i < 6; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((v[i] == 1) && (d[i] < min))
			{ // Переприсваиваем значения
				min = d[i];
				minindex = i;
			}
		}

		if (minindex != 10000) {
			for (int i = 0; i < 6; i++) {
				if (graf[minindex][i] > 0) {
					temp = min + graf[minindex][i];
					if (temp < d[i]) d[i] = temp;
				}
			}
			v[minindex] = 0; //вершину обошли
		}
	} while (minindex != 10000);
	// Вывод кратчайших расстояний до вершин
	cout << "\nКратчайшие расстояния до вершин: \n";
	for (int i = 0; i < 7; i++)
		printf("%4d ", d[i]);
	
	// Восстановление пути
	int *ver = new int[6], end; // массив посещенных вершин
	cout << "\nВведите конечную вершину: ";
	cin >> end; // индекс конечной вершины 
	cout << "Вывод кратчайшего пути до вершины " << end << endl;
	end = end - 1;
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = d[end]; // вес конечной вершины
	while (end != 5) {// пока не дошли до начальной вершины
		for (int i = 0; i < 6; i++) // просматриваем все вершины
			if (graf[end][i] != 0) {  // если связь есть
				int temp = weight - graf[end][i]; // определяем вес пути из предыдущей вершины
				if (temp == d[i]) {// если вес совпал с рассчитанным значит из этой вершины и был переход
					weight = temp; // сохраняем новый вес
					end = i;       // сохраняем предыдущую вершину
					ver[k] = i + 1; // и записываем ее в массив
					k++;
				}
			}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	for (int i = k - 1; i >= 0; i--)
		printf("%3d ", ver[i]);

	return 0;
}
