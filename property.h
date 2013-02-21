#ifndef property_H
#define property_H

#include "ast.h"
#include "nativeobject.h"

using namespace std;

class Object;
class Class;
class Namespace;

class Property : public NativeObject, public AST {	
	Object* _defaultValue;
	Class* _castTo;
		
public:
	Property(string name, AST& scope);
	
	Object* defaultValue();
	Class* castTo();
	static void bootstrap(Namespace& ns);
};

#endif