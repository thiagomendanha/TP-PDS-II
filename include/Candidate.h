#pragma once
#include <iostream>
#include <string>

class Candidate {
private:
	int id;
	int number;
	std::string name;
	std::string party;
	std::string election;

public:
	Candidate(int id, int number, std::string& name, std::string& party, std::string& election);

	int getId() const;

	std::string getName() const;

	std::string getParty() const;

	std::string getElection() const;

	int getNumber() const;

	void print();
};

