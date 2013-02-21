#include "userobject.h"
#include "variable.h"
#include "class.h"

Variable& UserObject::addVariable(string name) {
	Variable _variable(name, *this->_class);
	this->_variables.insert( pair<string, Variable>(name, _variable) );
	return this->getVariable(name);
}

Variable& UserObject::getVariable(string name) {
	Variable& ref = this->_variables.at(name);
	return ref;
}

void UserObject::removeVariable(string name) {
	this->_variables.erase(name);
}

Object& UserObject::getValue(string name) {
	return this->_variables.at(name)();
}

void UserObject::setValue(string name, Object& value) {
	this->_variables.at(name)(value);
}

Object& UserObject::callMethod(string name, vector<Object*> arguments) {
	return this->_class->callMethod(*this, name, arguments);
}
