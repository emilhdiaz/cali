#ifndef closure_H
#define closure_H

#include <string>
#include <map>
#include <queue>
#include <list>
#include "ast.h"
#include "scope.h"

using namespace std;

class Closure : public ClosureAST {
	
	
	Closure();
public:
	
	friend class Namespace;
	friend class Function;
};

#endif
