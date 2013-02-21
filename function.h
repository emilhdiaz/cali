#ifndef function_H
#define function_H

#include <string>
#include <map>
#include "ast.h"
#include "nativeobject.h"
#include "parameter.h"

using namespace std;

class Object;
class Namespace;

class Function : public NativeObject, public AST {
	map<string, Parameter> _parameters;
		
public:	
	Function(string name, AST& scope);
	
	Parameter&	addParameter(string name);
	Parameter&	getParameter(string name);
	void		removeParameter(string name);
	
	void updateFQN();
	Object& run(vector<Object*> arguments);
	static void bootstrap(Namespace& ns);
};

#endif