#include "variable.h"

Object& Variable::operator() () {
	return *(this->_value);
}

void Variable::operator() (Object& value) {
	this->_value = &value;
}