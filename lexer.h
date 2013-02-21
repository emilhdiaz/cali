#ifndef lexer_H
#define lexer_H

#include <string>
#include <map>
#include <iostream>
#include "token.h"

using namespace std;

class Lexer {
	istream* input;
	
	void lowerCase(string);
	void skipWhitespace();
	bool islabel(int);
	bool isnewline(int);
	bool isbinary(int);
	bool isoperator(int);
	bool isbetween(int, int, int);
	string extractInteger();
	string extractBinary();
	string extractLabel();
	string extractOperator();
	string extractLineComment();
	string extractEnclosure(int);
	
public:
	map<string, Token::Type> keywords;
	map<string, Token::Type> binary_operators;
	map<string, Token::Type> unary_operators;	
	
	Lexer();
	Token scan();
	void setInput(istream* stream);
};

#endif