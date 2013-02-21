#ifndef namespace_H
#define namespace_H

#include <string>
#include <map>
#include "ast.h"
#include "nativeobject.h"
#include "variable.h"
#include "function.h"
#include "class.h"

using namespace std;

class Object;

class Namespace : public NativeObject, public AST {
	map<string, Variable> _variables;
	multimap<string, Function> _functions;
	map<string, Class> _classes;
	map<string, Namespace> _namespaces;
	
	Namespace() : AST("Global", *this) {}
	
public:
	Namespace(string name, AST& scope);
	
	Variable&	addVariable(string name);
	Variable&	getVariable(string name);
	void		removeVariable(string name);
	
	Object&		getValue(string name);
	void		setValue(string name, Object& value);
	
	Function&	addFunction(string name);
	Function&	getFunction(string name);
	void		removeFunction(string name);
	
	Class&		addClass(string name);
	Class&		getClass(string name);
	void		removeClass(string name);
	
	Namespace&	addNamespace(string name);
	Namespace&	getNamespace(string name);
	void		removeNamespace(string name);	
	
	void updateFQN();
	
	static void bootstrap(Namespace& ns);
	
	friend class Engine;
};

#endif
