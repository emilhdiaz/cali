#ifndef nativeobject_H
#define nativeobject_H

#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include "object.h"

using namespace std;

class NativeObject : public Object {
protected:
	map<string, Object*> _members;
	
	NativeObject() {}

public:
	NativeObject(string type, Namespace& ns);
	Object& getValue(string name);
	void    setValue(string name, Object& value);
	Object& callMethod(string name, vector<Object*> arguments);
};

#endif