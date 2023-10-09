#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tree
{
	int key;
	string data;
	Tree* left;
	Tree* right;
};
void add_leaf(int key, string str, Tree*& root) //добавить узел с ключом key и информацией info в дерево
{
	Tree* tmp = new Tree;
	tmp->key = key;//ключ узла (по нему будет определяться размещение узла в дереве)
	tmp->data = str;//информация в узле(просто рандомный текст, не играет никакой роли)
	tmp->left = NULL;//слева ничаво
	tmp->right = NULL;//справа ничаво
	Tree* t = root;
	Tree* p = NULL;
	while (t != NULL)//ищем куда вставить этот узел
	{
		if (key > t->key)
		{
			p = t;
			t = t->right;
		}
		else if (key < t->key)
		{
			p = t;
			t = t->left;
		}
		else if (key == t->key)
		{
			cout << "This key is repeated!\n";
			return;
		}
	}
	if (root == NULL) root = tmp;//если корень пуст, то узел это корень
	else
	{
		if (tmp->key > p->key)p->right = tmp;//если не, то цепляем его к родителю, справа или слева зависит от ключа
		else p->left = tmp;
	}
}
void search(int key, Tree* root)//поиск ключа в дереве
{
	Tree* tmp = root;
	while (tmp != NULL && tmp->key != key)
	{
		if (key > tmp->key)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	if (tmp == NULL) 
	{
		cout << "This key is not in this tree!\n";
		return;
	}
	cout << tmp->data << endl;
}
void del(int key, Tree*& root)//удаление узла с заданным ключом из дерева
{
	Tree* tmp = root;
	Tree* p = NULL;
	while (tmp != NULL && tmp->key != key)//сначала ищем собсна узел
	{
		p = tmp;
		if (key > tmp->key)
			tmp = tmp->right;
		else
			tmp = tmp->left;
	}
	if (tmp == NULL) //если не нашли, бан
	{
		cout << "This key is not in this tree!\n";
		return;
	}
	Tree* c, * p_c;//вот это вот узел, который мы поставим вместо того, который удалим. И его батя
	if (tmp->right == NULL) c = tmp->left;//если справа от удаляемого пусто, то мы вместо него поставим то, шо слева
	else if (tmp->left == NULL) c = tmp->right;//аналогично для слева
	else
	{//а это случай, когда и справа есть и слева
		p_c = tmp;
		c = tmp->left;
		while (c->right != NULL)//ищем узел на замену(самый правый в левой ветке удаляемого узла)
		{
			p_c = c;
			c = c->right;
		}
		if (p_c == tmp)c->right = tmp->right;//если так совпало, что самый правый в левой ветке оказался просто левым узлом удаляемого, то к нему справа цепляем всё то, что было у удаляемого узла справа. Мы его удалим, оно ему больше не надо
		else
		{//если самый правый в левой ветке оказался немного ниже, чем в примере сверху, то
			c->right = tmp->right;//цепляем к нему правое наследство покойного
			p_c->right = c->left;//левое наследие того узла, который примет на себя полномочия усопшего, передаётся бате этого узла, только передаётся справа, тк узел был правым сыном))
			c->left = tmp->left;//и поэтому теперь мы можем спокойно прицепить к нему левое наследство покойного
		}
	}
	if (tmp == root)root = c;//если мы удалили корень, то корень умер, здравствует новый корень. Всё просто
	else
	{
		if (tmp->key < p->key)//а иначе цепляем узел с нужной стороны
			p->left = c;
		else p->right = c;
	}
	delete tmp;//кремируем покойного
}
void make_balance(vector<pair<int, string> >& tree, int l, int r, Tree*& node)//балансировка(рекурсивная функция)
{//тут ты насколько я помню в курсе, так что даваааай, Женёк, даваааай. Вперёт!!
	if (l == r) 
	{
		node = NULL;
		return;
	}
	Tree* tmp = new Tree;
	int m = (l + r) / 2;
	tmp->key = tree[m].first;
	tmp->data = tree[m].second;
	node = tmp;
	make_balance(tree, l, m, node->left);
	make_balance(tree, m + 1, r, node->right);
}

void del_tree(Tree*& root)//удаление всего дерева
{
	if (root == NULL)return;
	del_tree(root->left);//удаляем левую ветку
	del_tree(root->right);//удаляем правую ветку
	Tree* tmp = root;
	root = NULL;
	delete tmp;//удаляем сам узел
}
void read_tree(vector<pair<int, string> >& tree, Tree* node)//это для записи дерева в массив
{
	if (node == NULL)return;
	read_tree(tree, node->left);//сначала прочитаем левую ветку текущего узла
	pair<int, string> p;						//потом мы 
	p.first = node->key;					    //в массив запишем
	p.second = node->data;						//то что в узле хранится 
	tree.push_back(p);
	read_tree(tree, node->right);//а потом прочитаем правую ветку текущего узла
}//запускаем эту функцию от корня дерева и получаем дерево, только в массиве и записанное в порядке возрастания ключа
Tree* balanc_tree(Tree* root)//балансировка дерева(основная функция)
{
	vector<pair<int, string> > tree;
	read_tree(tree, root);//записываем дерево в массив(см. выше)
	del_tree(root);//удаляем дерево
	make_balance(tree, 0, tree.size(), root);//а потом перезаписываем его из массива с помощью балансеровки(рекрусивной)
	return root;
}


//три способа печати дерева
void inorder_print(Tree* node)//когда сначал печатается левая ветка, потом сам узел, потом правая ветка
{
	if (node == NULL)return;
	inorder_print(node->left);
	cout << node->key << "  " << node->data << "\n";
	inorder_print(node->right);
}
void postorder_print(Tree* node)//сначала левая ветка, потом правая, потом узел
{
	if (node == NULL)return;
	postorder_print(node->left);
	postorder_print(node->right);
	cout << node->key << "  " << node->data << "\n";
}
void preorder_print(Tree* node)//сначала узел, потом левая ветка, потом правая ветка
{
	if (node == NULL)return;
	cout << node->key << "  " << node->data << "\n";
	preorder_print(node->left);
	preorder_print(node->right);
}
int menu()
{
	int n;
	cout << "------------Меню------------\n";
	cout << "1 - создать дерево\n";
	cout << "2 - добавить информацию\n";
	cout << "3 - поиск по ключу\n";
	cout << "4 - удаление по ключу\n";
	cout << "5 - сбалансировать дерево\n";
	cout << "6 - вывести прямым ходом\n";
	cout << "7 - вывести обратным ходом\n";
	cout << "8 - вывести в порядке возрастания ключа\n";
	cout << "0 - выход из программы\n";
	cout << "-----------------------------\n";
	cin >> n;
	return n;
}
int main()
{
	system("chcp 1251>null");
	Tree* root = NULL;
	while (true)
	{
		int k;
		int inf;
		char c;
		string str;
		switch (menu())
		{
		case 1:
			cout << "Введите количество узлов\n";
			cin >> k;
			for (int i = 0; i < k; i++)
			{
				cout << "Введите ключ\n";
				cin >> inf;
				cout << "Введите информацию\n";
				cin.ignore(32000, '\n');
				getline(cin, str);
				add_leaf(inf, str, root);
			}
			break;
		case 2:
			cout << "Введите ключ\n";
			cin >> inf;
			cout << "Введите информацию\n";
			cin.ignore(32000, '\n');
			getline(cin, str);
			add_leaf(inf, str, root);
			break;
		case 3:
			cout << "Введите ключ\n";
			cin >> inf;
			cout << "Информация: \n";
			search(inf, root);
			break;
		case 4:
			cout << "Введите ключ\n";
			cin >> inf;
			del(inf, root);
			cout << "Ключ удалён\n";
			break;
		case 5:
			root = balanc_tree(root);
			cout << "Дерево сбалансировано\n";
			break;
		case 6:
			cout << "Дерево:\n";
			preorder_print(root);
			break;
		case 7:
			cout << "Дерево:\n";
			postorder_print(root);
			break;
		case 8:
			cout << "Дерево:\n";
			inorder_print(root);
			break;
		default:
			cout << "Выход из программы......\n";
			return 0;
			break;
		}
		system("pause");
		system("cls");
	}
	return 0;
}