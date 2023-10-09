#include<iostream>
#include<string>

using namespace std;
const string znak = "+-/*^";

struct Stack //стек для операций
{
	char info;
	Stack* next;
};
Stack* InStack(Stack* stack, char a) // добавить в стек a
{
	Stack* t = new Stack;
	t->info = a;
	t->next = stack;
	return t;
}
Stack* OutStack(Stack* stack, char* a) //достать из стека в a
{
	*a = stack->info;
	Stack* t = stack->next;
	delete stack;
	return t;
}

int Prior(char a) //определение приоритета операций
{
	switch (a) 
	{
	case '^':				return 4;
	case '*': case '/':		return 3;
	case '-': case '+':		return 2;
	case '(':				return 1;
	}

	return 0;
}
int main()
{
	Stack* stack1 = NULL;
	system("chcp 1251>null");
	string str;
	cout << "Введите пример: ";
	cin >> str;
	string OPZ = "";
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')//если буква, добавляем её в строку
		{
			OPZ += str[i];
			continue;
		}
		if (znak.find(str[i]) != string::npos)//если знак
		{
			while (stack1 != NULL && Prior(stack1->info) >= Prior(str[i]))//то он выталкивает из стека в строку все знаки с большим либо равным приоритетом
			{
				char c;
				stack1 = OutStack(stack1, &c);
				OPZ += c;
			}
			stack1 = InStack(stack1, str[i]);//и сам добавляется в стек
			continue;
		}
		if (str[i] == '(')//скобка добавляется в стек
		{
			stack1 = InStack(stack1, str[i]);
			continue;
		}
		if (str[i] == ')') //закрывающая скобка выталкивает из стека в строку все знаки до открывающей скобки
		{
			while (stack1 != NULL && stack1->info != '(')
			{
				char c;
				stack1 = OutStack(stack1, &c);
				OPZ += c;
			}
			char c;
			stack1 = OutStack(stack1, &c);
		}

	}
	while (stack1 != NULL) //в конце все знаки выталкиваются из стека в строку 
	{
		char c;
		stack1 = OutStack(stack1, &c);
		OPZ += c;
	}
	cout << "Выражение " << str << " в форме ОПЗ: " << OPZ << endl;//вывод строки
	return 0;
}