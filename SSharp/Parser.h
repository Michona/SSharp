#pragma once

#include <string>
#include <iostream>
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
}

class Parser
{
public:
	Parser();
	~Parser();

	bool Wrapper(string &s);

private:

	int curr;

	bool FunctionDeclaration(string &s);

	bool BracketedExpression(string &s);

	bool InnerExpression(string &s);

	bool InnerDelim(string &s);

	bool ArgExpression(string &s);

	bool FunctionCall(string &s);
	
	bool FunctionParams(string &s);

	bool Condition(string &s);

	bool Var(string &s);

	bool FunctionName(string &s);

	bool MainFunction(string &s);

	bool Inner(string &s);

	bool ArithmeticOp(string &s);

	bool BinaryOp(string &s);

	bool ReadFunc(string &s);

	//helpers
	void NextToken(string &s);

	bool Match(string &s, const string &token);

	bool ReadName(string &s);

	bool ReadNumber(string &s);

};

