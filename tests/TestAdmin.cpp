#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Admin.h"

TEST_CASE("Testing Admin class") {
	Admin admin("admin", "1234");

	SUBCASE("Testing comparePass method") {
		CHECK(admin.comparePass("1234") == true);
		CHECK(admin.comparePass("wrong_password") == false);
	}
}
