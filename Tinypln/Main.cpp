#include "interpreter.h"
#include <string>
#include <iostream>
using namespace std;

void f() {
	string str = "fun2.l";

	//cout << "�������ļ�����";
	//cin >> str;

	cen::Interpreter in;
	in.interp(str);
}


int main()
{
	int i = 10000;
	f();
	getchar();
	getchar();
	return 0;
}