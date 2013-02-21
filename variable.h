#ifndef variable_H
#define variable_H

#include <map>
#include "ast.h"
#include "object.h"

using namespace std;

class Variable : public AST {
	Object* _value;
	map<>
		
public:	
	Variable(string name, AST& scope) : AST(name, scope) {}
	
	Object& operator() ();
	void operator() (Object& value);
};

#endif

