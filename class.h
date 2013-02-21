#ifndef class_H
#define class_H

#include <string>
#include <map>
#include "ast.h"
#include "nativeobject.h"
#include "property.h"
#include "function.h"

using namespace std;

class Namespace;

class Class : public NativeObject, public AST {	
	map<string, Property> _properties;
	multimap<string, Function> _functions;
	
	Class(AST& scope) : AST("Class", scope) {}
		
public:
	Class(string name, AST& scope);
	
	Function&	addFunction(string name);
	Function&	getFunction(string name);
	void		removeFunction(string name);
	
	Property&	addProperty(string name);
	Property&	getProperty(string name);
	void		removeProperty(string name);	
	
	Object& callMethod(Object& object, string name, vector<Object*> arguments);
	
	static void bootstrap(Namespace& ns);
	
	friend class Engine;
};

#endif