#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
	int i, j, n, m, sum = 0;
	cout << "Vvedite kolichestvo strok: ";
	cin >> n;
	cout << "Vvedite kolichestvo stolbcov: ";
	cin >> m;
	int** a = new int* [n];

	for (i = 0; i < n; i++)
	{
		a[i] = new int[m];
	}
	cout << "Massiv: " << endl;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			cout << a[i][j] << "  \t"; //горизонтальная табуляция получаеца
		}
		cout << endl;
	}

	int t; // переменная с которой будет всё сравниваться 
	cout << "Vvedite peremennui: ";
	cin >> t;

	int kolv = 0; // переменная обозначающая количество строк, которые по среднему арифметическому меньше t
	for (i = 0; i < n; i++)
	{
		sum = 0;

		for (j = 0; j < m; j++)
		{
			sum = (a[i][j] + sum * j) / (j + 1);
		}

		if (sum < t)
		{
			kolv++;
		}
	}

	cout << "Kolichestvo podhodyashih strok: " << kolv << endl;
	delete[] a;
	system("pause");
	return 0;
}