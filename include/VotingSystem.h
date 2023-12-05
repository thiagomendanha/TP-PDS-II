#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "Admin.h"
#include "Elector.h"
#include "Candidate.h"
#include "Election.h"

class VotingSystem {
private:
	std::vector<Admin> admins;
	std::vector<Elector> electors;
	std::vector<Candidate> candidates;
	std::vector<Election> elections;

	int getOption();

	static void clearScreen();

	void showAdminMenu(Admin* admin);

	Admin* authenticateAdmin(const std::string& login, const std::string& pass);

	void handleAdminOption();

	void handleElectorsByAdmin();

	void handleAddElectorByAdmin();

	void handleRemoveElectorByAdmin();

	void handleCandidatesByAdmin();

	void handleAddCandidateByAdmin();

	void handleRemoveCandidateByAdmin();

	void handleElectionsByAdmin();

	void handleAddElectionByAdmin();

	void handleRemoveElectionByAdmin();

	void showElectorMenu(Elector* authenticatedElector);

	void handleElectorOption();

	void handleElectorListElections(Elector* authenticatedElector);

	void handleElectorVote(Election* election, Elector* authenticatedElector);

	Candidate* getCandidateByNumber(const int number);

	void listAllAvailableElections(Elector* authenticatedElector);

	std::vector<Election> getAllAvailableElections(Elector* authenticatedElector);

	void getResult(Election* election);

	void listAllElections();


	void removeElector(const int electorId);

	void removeCandidate(int id);

	void listCandidates();

	void listElectors();

	void removeElection(std::string election);

	Election* getElectionByName(const std::string electionName);

	void listElections();

	std::vector<Candidate>getCandidatesByElection(const std::string& electionName);

	void clearAllAdmin();

	Elector* authenticateElector(const std::string& login, const std::string& pass);

	Candidate* getCandidateById(const int id);
public:
	void showMainMenu();

	void addAdmin(const Admin& admin);

	void addElector(const Elector& elector);

	int addElection(const Election newElection);

	void addCandidate(const Candidate& candidate);
};