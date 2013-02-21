#include "function.h"
#include "variable.h"
#include "class.h"
#include "namespace.h"
#include "engine.h"

extern Engine& ENGINE;

Function::Function(string name, AST& scope) : AST(name, scope), NativeObject("Function", ENGINE.globalNamespace()) {}

/** HasParameters **/
Parameter& Function::addParameter(string name) {
	Parameter _parameter(name, *this);	
	this->_parameters.insert( pair<string, Parameter>(name, _parameter) );
	return this->getParameter(name);
}

Parameter& Function::getParameter(string name) {
	Parameter& ref = this->_parameters.at(name);
	return ref;
}

void Function::removeParameter(string name) {
	this->_parameters.erase(name);
}


/** Function **/
void Function::updateFQN() {
	this->_FQN = this->_scope->FQN() + ':' + this->_name;
	for (map<string, Parameter>::iterator it=this->_parameters.begin(); it!=this->_parameters.end(); ++it) {
		this->_FQN += "?" + it->second.castTo()->name();
	}
}

Object& Function::run(vector<Object*> arguments) {
	map<string, Variable> variables;
	
}

void Function::bootstrap(Namespace& ns) {
	ns.addClass("Function");
}