#include <iostream>
#include "Protection.h"
#include <conio.h>
#include <ctime>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct MyStruct {
	int key{};
	string str;
};

struct Tree {
	MyStruct info;
	Tree* left{}, * right{};
};

Tree * DeleteTree2(Tree * root);
void Menu();
void TreeView(Tree *&, int);
void Create(Tree*&, int, string);
void CreateRandomOrManually(Tree**, bool*);
void PrObh(Tree*&, vector<MyStruct>& data);
void ObrObh(Tree*&);
void inorderTraversa(Tree*& root);//в порядке возрастания ключа
int MyTask(Tree*& root, int depth);
Tree* Del(Tree* root, int key);
void SearchKey(Tree*, int);
void Make_Blns(Tree*& p, int n, int k, vector<MyStruct> data);


int main()
{ 

	vector<MyStruct> data;
	Tree* root = NULL; 

	setlocale(LC_ALL, "rus");
	srand((unsigned int)time(NULL));

	int index = 0, choose_variant;
	string str;
	bool isCreate = false;
	bool isInTree[200] = { 0 };

	while (true)
	{
		system("pause");
		system("cls");
		Menu();
		choose_variant = ProtectionInt("Выберите действие = ");
		if (choose_variant != 1 && choose_variant != 0 && !isCreate)
		{
			cout << "Дерево еще не создано. Нажмите 1!" << endl;
			continue;
		}
		switch (choose_variant)
		{
		case 1:
			if (root != NULL)break;
			isCreate = true;
			CreateRandomOrManually(&root, isInTree);
			cout << "--------------БинарноеДерево---------------" << endl;
			TreeView(root, 0);
			break;
		case 2:
			cout << "--------------БинарноеДерево---------------" << endl;
			TreeView(root, 0);
			break;
		case 3:
			CreateRandomOrManually(&root, isInTree);
			cout << "--------------БинарноеДерево---------------" << endl;
			TreeView(root, 0);
			break;
		case 4:
		{
			int depth = 0;
			depth = MyTask(root, depth);
			cout << "Глубина = " << depth << endl;
			break;
		}
		case 5:
			cout << "\nПрямой обход" << endl;
			PrObh(root, data);
			data.clear();
			cout << "\nОбратный обход" << endl;
			ObrObh(root);
			cout << "\nВ порядке возрастания ключа" << endl;
			inorderTraversa(root);
			break;
		case 6:
			int key;
			key = ProtectionInt("Введите ключ = ");
			root = Del(root, key);
			break;
		case 7:
			PrObh(root, data);
			index = data.size();
			Make_Blns(root, 0, index, data);
			data.clear(); cout << endl << endl;
			TreeView(root, 0);
			break;
		case 8:
			root = DeleteTree2(root);
			cout << "Tree removed" << endl;
			isCreate = false;
			break;
		case 9:
			cin >> key;
			SearchKey(root, key);
			break;
		case 0:
			if (root != NULL)
			{
				cout << "Освободите память!" << endl;
				break;
			}
            return 0;
		default:
		cout << "Invalid value! Try again." << endl;
		break;
		}
	}
}

void Menu()
{
	cout << "Choose an option: " << endl << endl;;
	cout << "1. Создать дерево. " << endl;
	cout << "2. Просмотреть дерево. " << endl;
	cout << "3. Добавить ключ в дерево." << endl;
	cout << "4. Определить максимальную глубину дерева." << endl;//мах глубина дерева
	cout << "5. Прямой , обратный и в порядке возрастания ключа обход." << endl;
	cout << "6. Удаление элемента по заданному ключу." << endl;
	cout << "7. Сбалансировать дерево поиска." << endl;
	cout << "8. Удалить дерево." << endl;
	cout << "9. Поиск по ключу." << endl;
	cout << "0. Выход." << endl << endl;
}

void TreeView(Tree*& root, int tabs)
{
	{
		if (!root) return; 
		tabs += 5; //Увеличим счетчик рекурсивно вызванных процедур, который будет считать нам отступы для красивого вывода
		TreeView (root->right, tabs); //Выведем ветку и ее подветки слева
		
		for (int i = 0; i < tabs; i++) cout << " "; //Потом отступы
		
		cout << root->info.key << endl; //Данные этой ветки
		TreeView (root->left, tabs);//И ветки, что справа
		tabs -= 5; //После уменьшим кол-во отступов
	}
}

void Create(Tree*& root, int element, string str)
{
	if (root == NULL)
	{
		root = new Tree;
		root->info.key = element;
		root->info.str = str;
		root->left = root->right = NULL;
		return;
	}
	if (root->info.key > element) Create(root->left, element, str);
	else Create(root->right, element, str);
}

void CreateRandomOrManually(Tree** root, bool isInTree[])
{
	int value, element, choice, min, max, a;
	string str;

	
	do
	{
		value = ProtectionInt("Введите количество значений, которые хотите добавить в дерево = ");
	} while (value < 1);
	
	choice = ProtectionInt("Выберите способ ввода значений: 1 - вручную, 2 - рандомом  = ");
	while (true)
	{
		switch (choice)
		{
		case 1:
			cout << "Вы выбрали способ заполнения вручную." << endl;
			for (int i = 0; i < value; i++)
			{
				do {
					element = ProtectionInt("Элемент = ");
				} while (isInTree[element]);

				isInTree[element] = true;
				cout << "Символ = ";
				cin >> str;
				Create(*root, element, str);
			}
			system("cls");
			break;
		case 2:
			cout << "Вы выбрали заполнение рандомом" << endl;
			do {
				min = ProtectionInt("Введите минимальный диапазон значений(>0!!!) = ");
				max = ProtectionInt("Введите максимальный диапазон значений = ");
			} while (min > max || min < 1);// || = or

			for (int i = 0; i < value; i++)
			{
					do {
						element = rand() % (max - min + 1) + min;
						if(isInTree)
						cout << element << endl;

					} while (isInTree[element]);
					isInTree[element] = true;

					a = 33 + rand() % 94;
					str += a;					
				Create(*root, element, str);//Сделать рандомное заполнение строки!
			}
			break;
		default:
			cout << "Invalid value! Try again." << endl;
			break;
		}
		break;
	}
	cout << "Элементы добавлены" << endl;
}

Tree* DeleteTree2(Tree* root)
{
	if (root == NULL) return NULL;
	DeleteTree2(root->left);
	DeleteTree2(root->right);
	delete root;
	return NULL;
}

void PrObh(Tree*& root, vector<MyStruct>& data)
{

	if (root == NULL) return;
	data.push_back(root->info);
	cout << root->info.key << "\t";
	PrObh(root->left, data);
	PrObh(root->right, data);

}

void ObrObh(Tree*& root)
{
	if (root == NULL) return;
	ObrObh(root->left);
	ObrObh(root->right);
	cout << root->info.key<<"\t";
}

void inorderTraversa(Tree*& root)//в порядке возрастания ключа
{
	if (root == NULL) return;
	inorderTraversa(root->left);
	cout << root->info.key << "\t";
	inorderTraversa(root->right);	
}

int MyTask(Tree*& root, int depth)
{
	if (root == NULL) return depth;
	return max(MyTask(root->left, depth + 1), MyTask(root->right, depth + 1));
}

Tree* Del(Tree* root, int key)
{
	Tree* Del, * Prev_Del, * R, * Prev_R;//Del, Prev_Del – удаляемый элемент и его предыдущий (родитель), R, Prev_R - элемент на который заменяется удаленный и его родител;
	Del = root;
	Prev_Del = NULL;
	/*Поиск удалемого элемента и его родителя*/
	while (Del != NULL && Del->info.key != key)
	{
		Prev_Del = Del;
		if (Del->info.key > key) Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {
		cout << "Элемент не найден." << endl;
		return root;
	}
	/*Поиск элемента R для замены*/
	if (Del->right == NULL)R = Del->left;
	else if (Del->left == NULL)R = Del->right;
	else {/*Ищем самый правфй узел в левом поддереве*/
		Prev_R = Del;
		R = Del->left;
		while (R->right != NULL) {
			Prev_R = R;
			R = R->right;
		}
		if (Prev_R == Del)
			R->right = Del->right;
		else {
			R->right = Del->right;
			Prev_R->right = R->left;
			R->left = Prev_R;
		}
	}
	if (Del == root)root = R; // Удаляя корень, заменяем его на R
	else /*Поддерево R присоединяем к родителю удаляемого узла*/
		if (Del->info.key < Prev_Del->info.key)
			Prev_Del->left = R;//На левую ветвь
		else Prev_Del->right = R;//На правую
	cout << "Delete = " << Del->info.key << endl;
	delete Del;
	return root;
}

void SearchKey(Tree* root, int key)
{
  	Tree* t = root;
	if (!t)	return;
    if (t->info.key == key)
	{
		cout << "str = " << root->info.str << endl;
		return;
	}
	SearchKey(t->left, key);
	SearchKey(t->right, key);

}

void Make_Blns(Tree*& p, int n, int k, vector<MyStruct> data)
{
	if (k == n) {
		p = NULL;
		return;
	}
	else {
		int m = (n + k) / 2;
		p = new Tree;
		p->info.key = data.at(m).key;
		p->info.str = data.at(m).str;
		Make_Blns(p->left, n, m, data);
		Make_Blns(p->right, m + 1, k, data);
	}
}