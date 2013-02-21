#include "namespace.h"
#include "engine.h"

extern Engine& ENGINE;

Namespace::Namespace(string name, AST& scope) : AST(name, scope), NativeObject("Namespace", ENGINE.globalNamespace()) { }

/** HasVariables **/
Variable& Namespace::addVariable(string name) {
	Variable _variable(name, *this);
	this->_variables.insert( pair<string, Variable>(name, _variable) );
	return this->getVariable(name);
}

Variable& Namespace::getVariable(string name) {
	Variable& ref = this->_variables.at(name);
	return ref;
}

void Namespace::removeVariable(string name) {
	this->_variables.erase(name);
}

Object& Namespace::getValue(string name) {
	return this->_variables.at(name)();
}

void Namespace::setValue(string name, Object& value) {
	this->_variables.at(name)(value);
}


/** HasFunctions **/
Function& Namespace::addFunction(string name) {
	Function _function(name, *this);	
	std::multimap<string,Function>::iterator it = this->_functions.insert( pair<string, Function>(name, _function) );
	Function& ref = it->second;
	return ref;
}

Function& Namespace::getFunction(string name) {
	
}

void Namespace::removeFunction(string name) {
	this->_functions.erase(name);
}


/** HasClasses **/
Class& Namespace::addClass(string name) {
	Class _class(name, *this);
	this->_classes.insert( pair<string, Class>(name, _class) );
	return this->getClass(name);
}

Class& Namespace::getClass(string name) {
	Class& ref = this->_classes.at(name);
	return ref;
}

void Namespace::removeClass(string name) {
	this->_classes.erase(name);
}


/** HasNamespaces **/
Namespace& Namespace::addNamespace(string name) {
	Namespace _namespace(name, *this);
	this->_namespaces.insert( pair<string, Namespace>(name, _namespace) );
	return this->getNamespace(name);
}

Namespace& Namespace::getNamespace(string name) {
	Namespace& ref = this->_namespaces.at(name);
	return ref;
}

void Namespace::removeNamespace(string name) {
	this->_namespaces.erase(name);
}


/** Namespace **/
void Namespace::updateFQN() {
	this->_FQN = this->_name;
}

void Namespace::bootstrap(Namespace& ns) {
	ns.addClass("Namespace");
}