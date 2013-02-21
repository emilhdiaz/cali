#include "parameter.h"

void Variable::updateFQN() {
	this->_FQN = this->scope->FQN() + ':' + this->name;
}