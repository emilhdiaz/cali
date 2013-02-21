#ifndef parser_H
#define parser_H

#include <string>
#include <stack>
#include <map>
#include <vector>
#include <fstream>
#include <exception>
#include "token.h"

using namespace std;

class Lexer;
class Namespace;

class Parser {	
	Lexer& lexer;
	Namespace* _namespace;
	Token token;
	ifstream source;
	
	void next();
	void parseFile();
	void parseStatement();
	void parseExpression();
	void parseNamespaceDeclaration();
	void parseFunctionDeclaration();
	void parseClassDeclaration();
	void parseInterfaceDeclaration();
	void parseConstantDeclaration();
	void parseVariableDeclaration();
	void parseIfStatement();
	void parseWhileStatement();
	void parseCondition();
	void parseClosure();
	void parseParameters();
	void parseArguments();
	void parseList();	
	bool isliteral();
	
public:	
	Parser(Lexer&);
	~Parser();
	void parse();
	void parse(string);
	
	class Exception: public exception {
	public:
		string message;
		Exception(Token) throw();
		~Exception() throw();
	};
};

#endif