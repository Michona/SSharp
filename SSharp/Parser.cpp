#include <iostream>
#include <string>
using namespace std;

#include "pch.h"
#include "Parser.h"

#define VALFALSE {curr = original; returnvalue = false;}
#define RETFALSE {curr = original; return false;}
#define SETUP int original = curr; bool returnvalue = true; NextToken(s);

Parser::Parser()
{
	curr = 0;
}


Parser::~Parser()
{
}

bool Parser::Wrapper(string &s)
{

	int original = curr;

	if (FunctionDeclaration(s)) {
		NextToken(s);

		//TODO see to this
		if (curr == s.length())
			return true;
		else {
			curr = original;
			return false;
		}
	}
	return false;
}

bool Parser::FunctionDeclaration(string & s)
{
	SETUP;

	if (ReadName(s) && ArgExpression(s) && BracketedExpression(s))
		return true;

	RETFALSE;
}

bool Parser::BracketedExpression(string & s)
{
	SETUP;

	if (Match(s, consts::LB) && InnerExpression(s) && Match(s, consts::RB))
		return true;

	RETFALSE;
}

bool Parser::InnerExpression(string & s)
{
	SETUP;

	while (Inner(s)) {
		if (!InnerDelim(s)) {
			break;
		}
	}

	if (Inner(s)) {
		//TODO add logic bcs this is the VALUE
		return true;
	}

	RETFALSE;
}

bool Parser::Inner(string & s)
{
	SETUP;

	if (FunctionCall(s) || Condition(s) || Var(s))
		return true;

	RETFALSE;
}

bool Parser::InnerDelim(string &s)
{
	SETUP;

	if (Match(s, consts::SEMICOLON) || ArithmeticOp(s) || BinaryOp(s))
		return true;

	RETFALSE;
}

bool Parser::ArgExpression(string & s)
{
	SETUP;

	while (s[curr] != consts::LB[0] && curr <= s.size()) {
		NextToken(s);
		returnvalue = returnvalue && ReadName(s);
	}
	
	return true;
}

bool Parser::FunctionCall(string & s)
{
	SETUP;

	if (!FunctionName(s)) RETFALSE;
	
	if (!Match(s, consts::LP)) RETFALSE;

	if (!FunctionParams(s)) RETFALSE;

	if (!Match(s, consts::RP)) RETFALSE;
	
	if (returnvalue) { cout << "its function" << endl; }

	return true;
}

bool Parser::FunctionParams(string & s)
{
	SETUP;

	int numberOfArgs = 2;
	while (numberOfArgs - 1 > 0) {
		if (!Var(s) || !Match(s, consts::COMMA)) RETFALSE;
		numberOfArgs--;
	}
	if (!Var(s)) RETFALSE;

	return returnvalue;
}

bool Parser::Condition(string & s)
{
	SETUP;

	if (Match(s, consts::IF) && Match(s, consts::LP)
		&& Var(s) && BinaryOp(s) && Var(s)
		&& Match(s, consts::RP)
		&& BracketedExpression(s) && BracketedExpression(s))
		return true;

	RETFALSE;
}

bool Parser::Var(string & s)
{
	SETUP;

	if (ReadName(s) || ReadNumber(s)) {
		return true;
	}

	RETFALSE;
}


bool Parser::FunctionName(string & s)
{
	SETUP;

	if (Match(s, consts::IF))
		RETFALSE;

	if (ReadName(s)) {
		NextToken(s);
		if (s[curr] == consts::LP[0])
			return true;
	}

	RETFALSE;
}

bool Parser::MainFunction(string & s)
{
	return true;
}

bool Parser::ArithmeticOp(string & s)
{
	SETUP;

	if (Match(s, consts::ARITH_DIV) || Match(s, consts::ARITH_TIMES) || Match(s, consts::ARITH_MINUS) || Match(s, consts::ARITH_PLUS))
		return true;

	RETFALSE;
}

bool Parser::BinaryOp(string & s)
{
	SETUP;

	if (Match(s, consts::BIN_AND) || Match(s, consts::BIN_OR) || Match(s, consts::BIN_BIGGER)
		|| Match(s, consts::BIN_SMALLER) || Match(s, consts::BIN_NOT_EQ) || Match(s, consts::BIN_EQ))
		return true;

	return false;
}

bool Parser::ReadFunc(string & s)
{
	return false;
}


//helper functions
void Parser::NextToken(string &s)
{
	while (s[curr] == ' ' || s[curr] == '\n' || s[curr] == '\t')
		curr++;
}

bool Parser::Match(string &s, const string &token)
{
	NextToken(s);
	if (s.compare(curr, token.size(), token) == 0){
		curr += token.size();
		return true;
	}
	return false;

}

bool Parser::ReadName(string & s)
{
	SETUP;

	string varname = "";
	while (isalpha(s[curr])) {
		varname += s[curr];
		curr++;
	}

	if (varname == "")
		return false;
	cout << varname << endl;
	return true;
}

bool Parser::ReadNumber(string & s)
{
	SETUP;

	string varname = "";
	while (isdigit(s[curr])) {
		varname += s[curr];
		curr++;
	}

	if (varname == "")
		return false;
	cout << varname << endl;
	return true;
}
