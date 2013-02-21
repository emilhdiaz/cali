#ifndef parameter_H
#define parameter_H

#include <string>
#include "ast.h"
#include "namespace.h"

using namespace std;

class Parameter {
	string _name;
	bool _isOptional;
	Variable* _defaultValue;
	Class* _castTo;
	
	Parameter::Parameter(string name, bool isOptional = false) : _name(name), _isOptional(isOptional),  {
		this->castTo = &global().getClass("Any");
	}
	
public:	
	
	
	friend class Function;
};

#endif
