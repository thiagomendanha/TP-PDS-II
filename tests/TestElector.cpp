#include "doctest.h"
#include "Elector.h"

TEST_CASE("Testing Elector class") {
	Elector elector(1, "testLogin", "testPass");

	SUBCASE("Testing getId method") {
		CHECK(elector.getId() == 1);
	}

	SUBCASE("Testing comparePass method") {
		CHECK(elector.comparePass("testPass") == true);
		CHECK(elector.comparePass("wrongPass") == false);
	}
}