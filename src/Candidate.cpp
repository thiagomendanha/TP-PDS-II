#include "Candidate.h"

Candidate::Candidate(int id, int number, std::string& name, std::string& party, std::string& election) {
	this->id = id;
	this->number = number;
	this->name = name;
	this->party = party;
	this->election = election;
}

int Candidate::getId() const {
	return this->id;
}

std::string Candidate::getName() const {
	return name;
}

std::string Candidate::getParty() const {
	return this->party;
}

std::string Candidate::getElection() const {
	return this->election;
}

int Candidate::getNumber() const {
	return this->number;
}

void Candidate::print() {
	std::cout << "ID: " << this->id << this->number << " | Nome: " << this->name << " | Partido: " << this->party << " | Vai participar da eleicao: " << this->election << std::endl;
}
