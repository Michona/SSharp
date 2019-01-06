#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Holder.h"
#include "Lexer.h"
using namespace std;


class Parser
{
public:
	Parser(Holder &h);
	~Parser();

	/*Tryes to run the algorithm and if it doesnt read the end of the file it returns false*/
	bool Wrapper(string &s, Holder &h);
	
	/* Tells the lexer to print the content*/
	void PrintAll();

private:

	int curr;
	
	Lexer l;

	/* Works according the BNF*/
	bool FunctionDeclaration(string &s, Holder &h);

	bool BracketedExpression(string &s, Holder &h);


	/* It also tells the Lexer what to process and output*/
	bool InnerExpression(string &s, Holder &h);
	
	InnerType Inner(string &s, Holder &h);

	bool InnerDelim(string &s, Holder &h);

	bool ArgExpression(string &s, Holder &h);


	bool FunctionCall(string &s, Holder &h);
	
	bool FunctionParams(string &s, Holder &h);

	bool Condition(string &s, Holder &h);

	/* Name or number */
	bool Var(string &s, Holder &h);

	bool FunctionName(string &s, Holder &h);

	bool FuncDeclarationName(string &s, Holder &h);


	bool ArithmeticOp(string &s, Holder &h);

	bool BinaryOp(string &s, Holder &h);

	//Helper functions:

	/* Moves till the next non-whitespace char*/
	void NextToken(string &s);

	bool Match(string &s, Holder &h, const string &token);

	string ReadName(string &s, Holder &h);

	bool IsLocalVar(const string &varname, Holder &h);

	bool IsGlobalFunc(const string & funname, Holder & h);

	bool ReadNumber(string &s, Holder &h);

};

