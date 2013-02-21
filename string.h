#ifndef string_H
#define string_H

#include <string>
#include "common.h"
#include "nativeobject.h"

using namespace std;

class String : public NativeObject {
	string _value;
};

#endif