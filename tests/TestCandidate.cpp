#include "doctest.h"
#include "Candidate.h"

TEST_CASE("Testing Candidate class") {
	std::string name = "John Doe";
	std::string party = "Party";
	std::string election = "Election";
	Candidate candidate(1, 2, name, party, election);

	SUBCASE("Testing getId method") {
		CHECK(candidate.getId() == 1);
	}

	SUBCASE("Testing getNumber method") {
		CHECK(candidate.getNumber() == 2);
	}

	SUBCASE("Testing getName method") {
		CHECK(candidate.getName() == "John Doe");
	}

	SUBCASE("Testing getParty method") {
		CHECK(candidate.getParty() == "Party");
	}

	SUBCASE("Testing getElection method") {
		CHECK(candidate.getElection() == "Election");
	}
}
