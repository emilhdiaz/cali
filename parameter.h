#ifndef parameter_H
#define parameter_H

#include "ast.h"
#include "nativeobject.h"

using namespace std;

class Object;
class Class;
class Namespace;

class Parameter : public NativeObject, public AST {	
	Object* _defaultValue;
	Class* _castTo;
	bool _isOptional;
		
public:
	Parameter(string name, AST& scope);
	
	Object* defaultValue();
	Class* castTo();
	bool isOptional();
	static void bootstrap(Namespace& ns);
};

#endif