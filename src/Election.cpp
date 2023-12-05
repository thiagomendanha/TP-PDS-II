#include "Election.h"

Election::Election(std::string& name, std::chrono::system_clock::time_point& votingStart, std::chrono::system_clock::time_point& votingEnd) {
	this->name = name;
	this->votingStart = votingStart;
	this->votingEnd = votingEnd;
}

std::string Election::getName() const {
	return this->name;
}

std::chrono::system_clock::time_point Election::getStartDate() const {
	return votingStart;
}

std::chrono::system_clock::time_point Election::getEndDate() const {
	return votingEnd;
}

void Election::setVotingPeriod(const std::chrono::system_clock::time_point& startTime, const std::chrono::system_clock::time_point& endTime) {
	this->votingStart = startTime;
	this->votingEnd = endTime;
}

bool Election::isVotingOpen() const {
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	return (now >= votingStart && now <= votingEnd);
}

void Election::print() const {
	std::time_t start = std::chrono::system_clock::to_time_t(this->getStartDate());
	std::time_t end = std::chrono::system_clock::to_time_t(this->getEndDate());

	std::cout << "Nome: " << this->getName() << std::endl;

	std::tm timeinfo;
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&timeinfo, &start);
#else
	localtime_r(&start, &timeinfo);
#endif
	std::cout << "Data de Inicio: " << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
#if defined(_WIN32) || defined(_WIN64)
	localtime_s(&timeinfo, &end);
#else
	localtime_r(&end, &timeinfo);
#endif
	std::cout << "Data de fim: " << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
}

void Election::voteForCandidate(int electorId, int candidateId, std::vector<Candidate> candidates) {
	if (this->votersWhoVoted.find(electorId) != this->votersWhoVoted.end()) {
		std::cout << "Este eleitor ja votou nesta eleicao" << std::endl;
		return;
	}

	for (auto& candidate : candidates) {
		if (this->candidateVotes.find(candidate.getId()) == this->candidateVotes.end()) {
			this->candidateVotes[candidate.getId()] = 0;
			this->candidates[candidate.getId()] = candidate.getName();
		}
	}

	if (this->candidateVotes.find(candidateId) == this->candidateVotes.end()) {
		std::cout << "Este candidato nao esta participando desta eleicao\n";
		return;
	}

	this->candidateVotes[candidateId]++;
	std::cout << "Voto computado com sucesso!\n\n";
	this->votersWhoVoted.insert(electorId);

	// espere o usuario apertar enter
	std::cout << "Pressione enter para continuar...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.ignore();
}

bool Election::hasVoted(int electorId) const {
	return this->votersWhoVoted.find(electorId) != this->votersWhoVoted.end();
}

void Election::printResults(std::vector<Candidate> candidates) {
	for (auto& candidate : candidates) {
		if (this->candidateVotes.find(candidate.getId()) == this->candidateVotes.end()) {
			this->candidateVotes[candidate.getId()] = 0;
			this->candidates[candidate.getId()] = candidate.getName();
		}

	}

	std::cout << "Eleicao: " << this->getName() << std::endl;
	std::cout << "Resultados: " << std::endl;
	for (auto& candidate : this->candidateVotes) {
		std::cout << "Candidato: " << this->candidates[candidate.first] << " | Votos: " << candidate.second << std::endl;
	}
	std::cout << std::endl;
}
