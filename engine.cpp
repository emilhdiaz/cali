#include "engine.h"

Engine& Engine::load()  {
	static bool loaded = false;
	static Engine engine;
	if (!loaded) {
		Class _class(engine._globalNamespace);
		engine._globalNamespace._classes.insert( pair<string, Class>(_class.name(), _class) );
		loaded = true;
	}
	return engine;
}

Namespace& Engine::globalNamespace() {
	return this->_globalNamespace;
}