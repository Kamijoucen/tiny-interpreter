#include "interpreter.h"
#include <string>
#include <iostream>
using namespace std;




int main()
{
	string str;

	cout << "�������ļ�����";
	cin >> str;

	cen::Interpreter in;
	in.interp(str);
	getchar();
	getchar();
	return 0;
}