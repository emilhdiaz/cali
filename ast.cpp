#include "ast.h"

AST::AST(string name) : _name(name) {
	
}

AST::AST(string name, AST& scope) : _name(name), _scope(&scope) {
	this->updateFQN();
}

string AST::FQN() {
	return this->_FQN;
}

string AST::name() {
	return this->_name;
}

AST* AST::scope() {
	return this->_scope;
}

void AST::updateFQN() {
	this->_FQN = this->_scope->FQN() + ':' + this->_name;
}