#include "Protection.h"
#include<iostream>
using namespace std;

int ProtectionInt(const char* s)
{
	double t;
	cout << s;
	cin >> t;
	while (std::cin.get() != '\n')
	{
		cout << "Пожалуйста, введите корректные данные!" << std::endl << std::endl;
		cin.clear();
		cin.ignore(258, '\n');
		cin >> t;
	}
	return t;
}
