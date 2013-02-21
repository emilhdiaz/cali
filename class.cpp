#include "class.h"
#include "namespace.h"
#include "engine.h"

extern Engine& ENGINE;

Class::Class(string name, AST& scope) : AST(name, scope), NativeObject("Class", ENGINE.globalNamespace()) { }

/** HasProperties **/
Property& Class::addProperty(string name) {
	Property _property(name, *this);
	this->_properties.insert( pair<string, Property>(name, _property) );
	return this->getProperty(name);
}

Property& Class::getProperty(string name) {
	Property& ref = this->_properties.at(name);
	return ref;
}

void Class::removeProperty(string name) {
	this->_properties.erase(name);
}


/** HasFunctions **/
Function& Class::addFunction(string name) {
	Function _function(name, *this);	
	std::multimap<string,Function>::iterator it = this->_functions.insert( pair<string, Function>(name, _function) );
	Function& ref = it->second;
	return ref;
}

Function& Class::getFunction(string name) {
	
}

void Class::removeFunction(string name) {
	this->_functions.erase(name);
}


/** Class **/
Object& Class::callMethod(Object& object, string name, vector<Object*> arguments) {
	
}

void Class::bootstrap(Namespace& ns) {
	ns.addClass("Class");
}