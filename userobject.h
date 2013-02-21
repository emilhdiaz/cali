#ifndef userobject_H
#define userobject_H

#include <string>
#include <vector>
#include <map>
#include "object.h"

using namespace std;

class Variable;

class UserObject : public Object {
protected:
	map<string, Variable> _variables;
	
public:
	Variable&	addVariable(string name);
	Variable&	getVariable(string name);
	void		removeVariable(string name);
	
	Object&		getValue(string name);
	void		setValue(string name, Object& value);
	
	Object&		callMethod(string name, vector<Object*> arguments);
};

#endif