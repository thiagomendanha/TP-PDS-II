#include "doctest.h"
#include "User.h"

TEST_CASE("Testing User class") {
	User user("testLogin", "testPass");

	SUBCASE("Testing getLogin method") {
		CHECK(user.getLogin() == "testLogin");
	}

	SUBCASE("Testing setLogin method") {
		user.setLogin("newLogin");
		CHECK(user.getLogin() == "newLogin");
	}
}