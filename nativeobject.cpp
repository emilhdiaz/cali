#include "nativeobject.h"
#include "namespace.h"
#include "class.h"

NativeObject::NativeObject(string type, Namespace& ns) {
	this->_class = &(ns.getClass(type));
}

Object& NativeObject::getValue(string name) {
	return *(this->_members.at(name));
}

void NativeObject::setValue(string name, Object& value) {
	this->_members.at(name) = &value;
}

Object& NativeObject::callMethod(string name, vector<Object*> arguments) {
	return this->_class->callMethod(*this, name, arguments);
}