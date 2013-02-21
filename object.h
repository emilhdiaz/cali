#ifndef object_H
#define object_H

#include <string>
#include <vector>

using namespace std;

class Class;
class Namespace;

class Object {
protected:
	Class* _class;
	
public:
	virtual Class&  getClass();
	virtual Object& getValue(string name) = 0;
	virtual void    setValue(string name, Object& value) = 0;
	virtual Object& callMethod(string name, vector<Object*> arguments) = 0;
	static void bootstrap(Namespace& ns);
};

#endif