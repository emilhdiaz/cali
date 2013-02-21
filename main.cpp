#include "lexer.h"
#include "parser.h"
#include "engine.h"

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//

Engine& ENGINE = Engine::load();

int main() {
	Namespace::bootstrap(ENGINE.globalNamespace());
	Function::bootstrap(ENGINE.globalNamespace());
	Property::bootstrap(ENGINE.globalNamespace());
	Parameter::bootstrap(ENGINE.globalNamespace());
	
	Lexer lexer;

	Parser parser(lexer);
	
	//parser.parse("/Users/cuit/Developer/cali/cali2/test.mz");
	
	return 0;
}

void stats() {	
//	cout << "\n\nNamespace: " << this->FQN();
//	
//	cout << "\n • Functions :";
//	for (multimap<string, Function>::iterator it=this->functions.begin(); it!=this->functions.end(); ++it) {
//		cout << "\n  -> " << it->second.FQN();
//	}
//	
//	for (map<string, Namespace>::iterator it=this->namespaces.begin(); it!=this->namespaces.end(); ++it) {
//		it->second.stats();
//	}
}