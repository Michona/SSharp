#pragma once

#include <string>
#include "Holder.h"
using namespace std;

class Lexer
{
public:
	Lexer();
	~Lexer();

private:

	string OutputString;
	void Init();

	bool Disabled;

public:
	void NormalPrint(const string  s);
	void ReturnPrint();
	void FuntionDeclarationPrint(Holder & h);
	void InnerPrint(InnerType CurrentType, string & s);

	void PrintAll();
	void DisableAdding();
	void EnableAdding();
};

