#include "property.h"
#include "namespace.h"
#include "engine.h"

extern Engine& ENGINE;

Property::Property(string name, AST& scope) : AST(name, scope), NativeObject("Property", ENGINE.globalNamespace()) {}

Object* Property::defaultValue() {
	return this->_defaultValue;
}

Class* Property::castTo() {
	return this->_castTo;
}

void Property::bootstrap(Namespace& ns) {
	ns.addClass("Property");
}