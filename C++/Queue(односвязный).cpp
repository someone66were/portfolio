#include<iostream>

using namespace std;

struct Queue
{
	int inf;
	Queue* next;
};

void Create(int inf, Queue*& b, Queue*& e)
{
	Queue* t = new Queue;
	t->inf = inf;
	t->next = NULL;
	if (b == NULL)
		b = e = t;
	else
	{
		e->next = t;
		e = t;
	}
}

void view(Queue* b, Queue* e) 
{
	Queue* t = b;
	while (t != NULL) {
		cout << t->inf << " ";
		t = t->next;
	}
	cout << endl;
}

void Del_All(Queue*& b, Queue*& e)
{
	while (b != NULL) {
		 t = b;
		b = b->next;
		delete t;
	}
	e = NULL;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	Queue* b = NULL, * e = NULL;
	while (true) {
		cout << "Выберите операцию:\n\t1 - создание\n\t2 - просмотр\n\t3 - удаление\n\t0 - выход из программы\n";
		int kod;
		cin >> kod;
		switch (kod)
		{
		case 1:
			cout << "Введите количество элементов: ";
			int n;
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "Введите число: ";
				int k;
				cin >> k;
				Create(k, b, e);
			}
			break;
		case 2:
			cout << " Очередь: ";
			view(b, e);
			break;
		case 3:
			Del_All(b, e);
			cout << "Очередь удалена.\n";
			break;
		case 0:
			Del_All(b, e);
			cout << "Программа завершает работу.\n";
			return 0;
			break;
		default:
			cout << "Некорректный ввод. Повторите попытку.\n";
			break;
		}
	}
	return 0;
}