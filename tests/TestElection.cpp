#include "doctest.h"
#include "Election.h"
#include "Candidate.h"
#include <chrono>

TEST_CASE("Testing Election class") {
	std::string name = "Election";
	std::chrono::system_clock::time_point votingStart = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point votingEnd = votingStart + std::chrono::hours(24);
	Election election(name, votingStart, votingEnd);

	SUBCASE("Testing getName method") {
		CHECK(election.getName() == "Election");
	}

	SUBCASE("Testing getStartDate method") {
		CHECK(election.getStartDate() == votingStart);
	}

	SUBCASE("Testing getEndDate method") {
		CHECK(election.getEndDate() == votingEnd);
	}

	SUBCASE("Testing isVotingOpen method") {
		CHECK(election.isVotingOpen() == true);
	}

	SUBCASE("Testing hasVoted method") {
		CHECK(election.hasVoted(1) == false);
	}

	SUBCASE("Testing voteForCandidate method") {
		std::string candidateName = "John Doe";
		std::string party = "Party";
		Candidate candidate(1, 2, candidateName, party, name);
		std::vector<Candidate> candidates = { candidate };
		election.voteForCandidate(1, 1, candidates);
		CHECK(election.hasVoted(1) == true);
	}
}
