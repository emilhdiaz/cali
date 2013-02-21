#define CATCH_CONFIG_MAIN

#include "engine_test.h"
#include "catch.hpp"
#include "engine.h"

Engine& ENGINE = Engine::load();

TEST_CASE( "namespace/global", "The Global Namespace is initialized correctely" ) {
	REQUIRE( ENGINE.globalNamespace().FQN() == "Global");
}