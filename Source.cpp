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
void inorderTraversa(Tree*& root);//� ������� ����������� �����
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
		choose_variant = ProtectionInt("�������� �������� = ");
		if (choose_variant != 1 && choose_variant != 0 && !isCreate)
		{
			cout << "������ ��� �� �������. ������� 1!" << endl;
			continue;
		}
		switch (choose_variant)
		{
		case 1:
			if (root != NULL)break;
			isCreate = true;
			CreateRandomOrManually(&root, isInTree);
			cout << "--------------��������������---------------" << endl;
			TreeView(root, 0);
			break;
		case 2:
			cout << "--------------��������������---------------" << endl;
			TreeView(root, 0);
			break;
		case 3:
			CreateRandomOrManually(&root, isInTree);
			cout << "--------------��������������---------------" << endl;
			TreeView(root, 0);
			break;
		case 4:
		{
			int depth = 0;
			depth = MyTask(root, depth);
			cout << "������� = " << depth << endl;
			break;
		}
		case 5:
			cout << "\n������ �����" << endl;
			PrObh(root, data);
			data.clear();
			cout << "\n�������� �����" << endl;
			ObrObh(root);
			cout << "\n� ������� ����������� �����" << endl;
			inorderTraversa(root);
			break;
		case 6:
			int key;
			key = ProtectionInt("������� ���� = ");
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
				cout << "���������� ������!" << endl;
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
	cout << "1. ������� ������. " << endl;
	cout << "2. ����������� ������. " << endl;
	cout << "3. �������� ���� � ������." << endl;
	cout << "4. ���������� ������������ ������� ������." << endl;//��� ������� ������
	cout << "5. ������ , �������� � � ������� ����������� ����� �����." << endl;
	cout << "6. �������� �������� �� ��������� �����." << endl;
	cout << "7. �������������� ������ ������." << endl;
	cout << "8. ������� ������." << endl;
	cout << "9. ����� �� �����." << endl;
	cout << "0. �����." << endl << endl;
}

void TreeView(Tree*& root, int tabs)
{
	{
		if (!root) return; 
		tabs += 5; //�������� ������� ���������� ��������� ��������, ������� ����� ������� ��� ������� ��� ��������� ������
		TreeView (root->right, tabs); //������� ����� � �� �������� �����
		
		for (int i = 0; i < tabs; i++) cout << " "; //����� �������
		
		cout << root->info.key << endl; //������ ���� �����
		TreeView (root->left, tabs);//� �����, ��� ������
		tabs -= 5; //����� �������� ���-�� ��������
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
		value = ProtectionInt("������� ���������� ��������, ������� ������ �������� � ������ = ");
	} while (value < 1);
	
	choice = ProtectionInt("�������� ������ ����� ��������: 1 - �������, 2 - ��������  = ");
	while (true)
	{
		switch (choice)
		{
		case 1:
			cout << "�� ������� ������ ���������� �������." << endl;
			for (int i = 0; i < value; i++)
			{
				do {
					element = ProtectionInt("������� = ");
				} while (isInTree[element]);

				isInTree[element] = true;
				cout << "������ = ";
				cin >> str;
				Create(*root, element, str);
			}
			system("cls");
			break;
		case 2:
			cout << "�� ������� ���������� ��������" << endl;
			do {
				min = ProtectionInt("������� ����������� �������� ��������(>0!!!) = ");
				max = ProtectionInt("������� ������������ �������� �������� = ");
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
				Create(*root, element, str);//������� ��������� ���������� ������!
			}
			break;
		default:
			cout << "Invalid value! Try again." << endl;
			break;
		}
		break;
	}
	cout << "�������� ���������" << endl;
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

void inorderTraversa(Tree*& root)//� ������� ����������� �����
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
	Tree* Del, * Prev_Del, * R, * Prev_R;//Del, Prev_Del � ��������� ������� � ��� ���������� (��������), R, Prev_R - ������� �� ������� ���������� ��������� � ��� �������;
	Del = root;
	Prev_Del = NULL;
	/*����� ��������� �������� � ��� ��������*/
	while (Del != NULL && Del->info.key != key)
	{
		Prev_Del = Del;
		if (Del->info.key > key) Del = Del->left;
		else Del = Del->right;
	}
	if (Del == NULL) {
		cout << "������� �� ������." << endl;
		return root;
	}
	/*����� �������� R ��� ������*/
	if (Del->right == NULL)R = Del->left;
	else if (Del->left == NULL)R = Del->right;
	else {/*���� ����� ������ ���� � ����� ���������*/
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
	if (Del == root)root = R; // ������ ������, �������� ��� �� R
	else /*��������� R ������������ � �������� ���������� ����*/
		if (Del->info.key < Prev_Del->info.key)
			Prev_Del->left = R;//�� ����� �����
		else Prev_Del->right = R;//�� ������
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