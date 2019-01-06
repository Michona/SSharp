#pragma once

#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace consts
{
	const string LB = "{";
	const string RB = "}";
	const string LP = "(";
	const string RP = ")";
	const string SEMICOLON = ";";
	const string COMMA = ",";
	const string IF = "if";

	const string ARITH_PLUS = "+";
	const string ARITH_MINUS = "-";
	const string ARITH_TIMES = "*";
	const string ARITH_DIV = "/";

	const string BIN_AND = "&&";
	const string BIN_OR = "||";
	const string BIN_EQ = "==";
	const string BIN_NOT_EQ = "!=";
	const string BIN_BIGGER = ">";
	const string BIN_SMALLER = "<";

	const string WRITE = "write";
	const string READ = "read";

}

/* Used for storing information about the function*/
struct Function
{
	Function(string name, int argscount) {
		Name = name;
		ArgsCount = argscount;
	}
	string Name;
	int ArgsCount;
};

/* Used when outputting the string*/
enum InnerType
{
	Condition,
	FunctionCall,
	Variable,
	None
};

class Holder
{
public:
	Holder();
	~Holder();

	/*The two important vector that store local vars and global functions*/
	vector<string> LocalVars;
	vector<Function> GlobalFunctions;
};

