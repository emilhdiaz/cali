#ifndef ast_H
#define ast_H

#include <string>

using namespace std;

class AST {
protected:
	string _FQN;
	string _name;
	AST* _scope;
	
	AST(string name);
	
public:
	AST(string name, AST& scope);
	
	string FQN();
	string name();
	AST* scope();
	virtual void updateFQN();
};

#endif