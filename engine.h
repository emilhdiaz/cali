#ifndef engine_H
#define engine_H

#include "namespace.h"

using namespace std;

class Engine {
	Namespace _globalNamespace;
	
	Engine() {}
	
public:
	Namespace& globalNamespace();
	static Engine& load();
};

#endif