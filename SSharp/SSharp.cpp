#include "pch.h"
#include "Parser.h"
#include "Holder.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string input;
	std::string s;

	ifstream file("input.txt");

	if (file.is_open()) {
		while (getline(file, s)) {
			input += s;
		}
	}
	Holder h = Holder();
	Parser p = Parser(h);
	if (p.Wrapper(input, h)) {
		p.PrintAll();
	}
	else
		cout << "Error" << endl;
}
