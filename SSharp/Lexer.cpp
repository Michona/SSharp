#include "pch.h"
#include "Holder.h"
#include "Lexer.h"

#include <iostream>
#include <string>
#include "Holder.h"
using namespace std;

#define ADD OutputString +=

Lexer::Lexer()
{
	OutputString = "";
	Init();
	Disabled = false;
}


Lexer::~Lexer()
{
}

void Lexer::Init()
{
	ADD "#include <iostream>\n";
	ADD "#include <cstdint>\n";
	ADD "typedef uint64_t u \n";

	ADD "void write(u x) { std::cout << x << std::endl; } \n";
	ADD "u read() { u x; std::cin >> x; return x; } \n";
}

void Lexer::NormalPrint(const string s) {

	if (Disabled)
		return;
	ADD s;
}

void Lexer::ReturnPrint() {

	if (Disabled) return;
	ADD "return ";
}

void Lexer::FuntionDeclarationPrint(Holder &h) {

	if (Disabled) return;
	ADD "u ";
	ADD h.GlobalFunctions[h.GlobalFunctions.size() - 1].Name;
	ADD "(";
	for (int i = 0; i < h.LocalVars.size() - 1; i++) {
		ADD ("u " + h.LocalVars[i] + ",");
	}
	ADD("u " + h.LocalVars[h.LocalVars.size() - 1]);
	ADD ")";
}

void Lexer::InnerPrint(InnerType CurrentType, string &s)
{
	if (Disabled) return;

	if (CurrentType != InnerType::Condition) {
		ADD s;
		return;
	}
	else {
		//TODO Implement the "if condition" logic
	}
}

void Lexer::PrintAll() {
	cout << OutputString << endl;
}

void Lexer::DisableAdding()
{
	Disabled = true;
}

void Lexer::EnableAdding()
{
	Disabled = false;
}
