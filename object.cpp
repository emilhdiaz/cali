#include "object.h"
#include "class.h"
#include "namespace.h"

Class& Object::getClass() {
	return *(this->_class);
}

void Object::bootstrap(Namespace& ns) {
	ns.addClass("Object");
}