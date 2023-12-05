#pragma once
#include <deque>
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include "Candidate.h"

class Election {
private:
	std::string name;
	std::chrono::system_clock::time_point votingStart;
	std::chrono::system_clock::time_point votingEnd;
	std::unordered_set<int> votersWhoVoted;
	std::unordered_map<int, int> candidateVotes;
	std::unordered_map<int, std::string> candidates;

public:
	Election(std::string& name, std::chrono::system_clock::time_point& date, std::chrono::system_clock::time_point& votingEnd);

	std::string getName() const;
	std::chrono::system_clock::time_point getStartDate() const;
	std::chrono::system_clock::time_point getEndDate() const;

	void setVotingPeriod(const std::chrono::system_clock::time_point& startTime, const std::chrono::system_clock::time_point& endTime);

	bool isVotingOpen() const;

	void print() const;

	void voteForCandidate(int electorId, int candidateId, std::vector<Candidate> cantidates);

	bool hasVoted(int electorId) const;

	void printResults(std::vector<Candidate> candidates);
};

