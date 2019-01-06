#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "pch.h"
#include "Parser.h"
#include "Lexer.h"
#include "Holder.h"

#define VALFALSE {curr = original; returnvalue = false;}
#define RETFALSE {curr = original; return false;}
#define SETUP int original = curr; bool returnvalue = true; NextToken(s);

Parser::Parser(Holder &h)
{
	curr = 0;

	l = Lexer();
}

Parser::~Parser()
{
}

bool Parser::Wrapper(string &s, Holder &h)
{

	int original = curr;

	
	while (curr != s.length()) {

		if (!FunctionDeclaration(s, h)) {
			return false;
		}
		h.LocalVars.clear();
	}

	return true;
}

void Parser::PrintAll()
{
	l.PrintAll();
}

bool Parser::FunctionDeclaration(string &s, Holder &h)
{
	SETUP;

	if (FuncDeclarationName(s, h) && ArgExpression(s, h) && BracketedExpression(s, h)) {
		return true;
	}

	RETFALSE;
}

bool Parser::BracketedExpression(string &s, Holder &h)
{
	SETUP;

	l.NormalPrint(consts::LB);

	if (Match(s, h, consts::LB) && InnerExpression(s, h) && Match(s, h, consts::RB)) {
		l.NormalPrint(consts::RB);
		return true;
	}

	RETFALSE;
}

bool Parser::InnerExpression(string &s, Holder &h)
{
	SETUP;

	InnerType CurrentType = Inner(s, h);
	while (CurrentType != InnerType::None) {
		if (!InnerDelim(s, h)) {
			curr = original;
			break;
		}
		else {
			
			if (s[curr - 1] == consts::SEMICOLON[0]) {
				string substr = s.substr(original, curr - original);
				l.InnerPrint(CurrentType, substr);
				original = curr;
			}
		}
		CurrentType = Inner(s, h);
	}

	l.ReturnPrint();

	CurrentType = Inner(s, h);
	while (CurrentType != InnerType::None) {
		if (!ArithmeticOp(s, h) && !BinaryOp(s, h)) {
			curr = original;
			break;
		}
		string substr = s.substr(original, curr - original);
		l.InnerPrint(CurrentType, substr);

		original = curr;
	}

	CurrentType = Inner(s, h);
	if (CurrentType!= InnerType::None) {
		string substr = s.substr(original, curr - original);
		l.InnerPrint(CurrentType, substr);

		l.NormalPrint(consts::SEMICOLON + " ");
		return true;
	}


	RETFALSE;
}

InnerType Parser::Inner(string &s, Holder &h)
{
	SETUP;

	if (FunctionCall(s, h))
		return InnerType::FunctionCall;
	if (Condition(s, h))
		return InnerType::Condition;
	if (Var(s, h))
		return InnerType::Variable;

	curr = original;
	return InnerType::None;
}

bool Parser::InnerDelim(string &s, Holder &h)
{
	SETUP;

	if (Match(s, h, consts::SEMICOLON) || ArithmeticOp(s, h) || BinaryOp(s, h))
		return true;

	RETFALSE;
}

bool Parser::ArgExpression(string &s, Holder &h)
{
	SETUP;

	int cnt = 0;
	while (s[curr] != consts::LB[0]) {
		h.LocalVars.push_back(ReadName(s, h));
		NextToken(s);
		cnt++;
	}

	h.GlobalFunctions[h.GlobalFunctions.size() - 1].ArgsCount = cnt;

	//Prints the function with the arguments
	l.FuntionDeclarationPrint(h);

	return true;
}

bool Parser::FunctionCall(string &s, Holder &h)
{
	SETUP;

	if (FunctionName(s, h) && Match(s, h, consts::LP) && FunctionParams(s, h) && Match(s, h, consts::RP)) {
		cout << "its a function" << endl;
		return true;
	}
	
	RETFALSE;
}

bool Parser::FunctionParams(string &s, Holder &h)
{
	SETUP;

	l.DisableAdding();

	int numberOfArgs = h.GlobalFunctions[h.GlobalFunctions.size() - 1].ArgsCount;

	if (numberOfArgs == 0){
		l.EnableAdding();
		return true;
	}

	while (numberOfArgs - 1 > 0) {
		if (!InnerExpression(s, h) || !Match(s, h, consts::COMMA)) {
			RETFALSE;
		}
		numberOfArgs--;
	}
	if (!InnerExpression(s, h)) {
		RETFALSE;
	}

	l.EnableAdding();
	return true;
}

bool Parser::Condition(string &s, Holder &h)
{
	SETUP;

	if (Match(s, h, consts::IF) && Match(s, h, consts::LP)
		&& Var(s, h) && BinaryOp(s, h) && Var(s, h)
		&& Match(s, h, consts::RP)
		&& BracketedExpression(s, h) && BracketedExpression(s, h))
		return true;

	RETFALSE;
}

bool Parser::Var(string &s, Holder &h)
{
	SETUP;

	if (IsLocalVar(ReadName(s,h), h) || ReadNumber(s, h)) {
		return true;
	}

	RETFALSE;
}


bool Parser::FunctionName(string &s, Holder &h)
{
	SETUP;

	if (Match(s, h, consts::IF))
		RETFALSE;

	if (IsGlobalFunc(ReadName(s, h), h)) {
		NextToken(s);
		if (s[curr] == consts::LP[0])
			return true;
	}

	RETFALSE;
}

bool Parser::FuncDeclarationName(string & s, Holder & h)
{
	h.GlobalFunctions.push_back(Function(ReadName(s,h), 0));
	return true;
}

bool Parser::ArithmeticOp(string &s, Holder &h)
{
	SETUP;

	if (Match(s, h, consts::ARITH_DIV) || Match(s, h, consts::ARITH_TIMES) || Match(s, h, consts::ARITH_MINUS) || Match(s, h, consts::ARITH_PLUS))
		return true;

	RETFALSE;
}

bool Parser::BinaryOp(string &s, Holder &h)
{
	SETUP;

	if (Match(s, h, consts::BIN_AND) || Match(s, h, consts::BIN_OR) || Match(s, h, consts::BIN_BIGGER)
		|| Match(s, h, consts::BIN_SMALLER) || Match(s, h, consts::BIN_NOT_EQ) || Match(s, h, consts::BIN_EQ))
		return true;

	RETFALSE;
}

//helper functions
void Parser::NextToken(string &s)
{
	while (s[curr] == ' ' || s[curr] == '\n' || s[curr] == '\t')
		curr++;
}

bool Parser::Match(string &s, Holder &h, const string &token)
{
	NextToken(s);
	if (s.compare(curr, token.size(), token) == 0){
		curr += token.size();
		return true;
	}
	return false;
}

string Parser::ReadName(string &s, Holder &h)
{
	SETUP;

	string varname = "";
	while (isalpha(s[curr])) {
		varname += s[curr];
		curr++;
	}

	return varname;
}

bool Parser::IsLocalVar(const string & varname, Holder & h)
{
	for (int i = 0; i < h.LocalVars.size(); i++) {
		if (h.LocalVars[i] == varname)
			return true;
	}
	return false;
}

bool Parser::IsGlobalFunc(const string & funname, Holder &h)
{
	for (int i = 0; i < h.GlobalFunctions.size(); i++) {
		if (h.GlobalFunctions[i].Name == funname) {
			//swap the one that matched the function name and the last, so that it's easy to access in function params
			swap(h.GlobalFunctions[i], h.GlobalFunctions[h.GlobalFunctions.size() - 1]);
			return true;
		}
	}
	return false;
}

bool Parser::ReadNumber(string &s, Holder &h)
{
	SETUP;

	string varname = "";
	while (isdigit(s[curr])) {
		varname += s[curr];
		curr++;
	}

	if (varname.empty())
		RETFALSE;

	return true;
}
