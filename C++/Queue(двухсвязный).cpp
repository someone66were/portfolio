#include<iostream>

using namespace std;

struct Queue
{
	int inf;
	Queue* next;
	Queue* prev;
};

void InBegin(int inf, Queue*& b, Queue*& e)
{
	Queue* t = new Queue;
	t->inf = inf;
	t->prev = NULL;
	t->next = NULL;
	if (b == NULL)
		b = e = t;
	else
	{
		b->prev = t;
		t->next = b;
		b = t;
	}
}
void InEnd(int inf, Queue*& b, Queue*& e)
{
	Queue* t = new Queue;
	t->inf = inf;
	t->prev = NULL;
	t->next = NULL;
	if (b == NULL)
		b = e = t;
	else
	{
		e->next = t;
		t->prev = e;
		e = t;
	}
}
void view_begin(Queue* b, Queue* e) 
{
	Queue* t = b;
	while (t != NULL) {
		cout << t->inf << " ";
		t = t->next;
	}
	cout << endl;
}
void view_end(Queue* b, Queue* e)
{
	Queue* t = e;
	while (t != NULL) {
		cout << t->inf << " ";
		t = t->prev;
	}
	cout << endl;
}
void Del_All(Queue*& b, Queue*& e)
{
	while (b != NULL) {
		Queue* t = b;
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
		cout << "Выберите операцию:\n\t1 - создание\n\t2 - добавить элемент в начало\n\t3 - добавить элемент в конец\n\t4 - просмотр с начала\n\t5 - просмотр с конца\n\t6 - удаление\n\t0 - выход из программы\n";
		int kod, k;
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
				cin >> k;
				InBegin(k, b, e);
			}
			break;
		case 2:
			cout << "Введите число: ";
			cin >> k;
			InBegin(k, b, e);
			break;
		case 3:
			cout << "Введите число: ";
			cin >> k;
			InEnd(k, b, e);
			break;
		case 4:
			cout << " Очередь: ";
			view_begin(b, e);
			break;
		case 5:
			cout << " Очередь: ";
			view_end(b, e);
			break;
		case 6:
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