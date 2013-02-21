#include "parameter.h"
#include "namespace.h"
#include "engine.h"

extern Engine& ENGINE;

Parameter::Parameter(string name, AST& scope) : AST(name, scope), NativeObject("Parameter", ENGINE.globalNamespace()) { }

Object* Parameter::defaultValue() {
	return this->_defaultValue;
}

Class* Parameter::castTo() {
	return this->_castTo;
}

bool Parameter::isOptional() {
	return this->_isOptional;
}

void Parameter::bootstrap(Namespace& ns) {
	ns.addClass("Parameter");
}