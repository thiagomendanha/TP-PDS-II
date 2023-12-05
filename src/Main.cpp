#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Admin.h"
#include "Elector.h"
#include "Candidate.h"
#include "VotingSystem.h"
#include "Election.h"
#include <iomanip>
#include <chrono>

#define DATABASE_NAME "data.txt"

static int CheckDatabase(VotingSystem& votingSystem) {
	std::ifstream file(DATABASE_NAME);
	if (!file.is_open()) {
		return 0;
	}

	int counter = 0;
	std::string row;

	while (std::getline(file, row)) {
		std::istringstream iss(row);
		std::vector<std::string> values;
		std::string value;

		while (iss >> value) {
			values.push_back(value);
		}

		if (values.size() == 3) {
			// Lida com 3 colunas (Admin)
			int identification = std::stoi(values[0]); // Converta para int, se necessario

			// Processa os dados lidos
			if (identification == 1) {
				std::string login = values[1];
				std::string pass = values[2];
				counter += 1;
				Admin adm = Admin(login, pass);
				votingSystem.addAdmin(adm);
			}
		}
		else if (values.size() == 4) {
			// Lida com 4 colunas (Eleitor)
			int identification = std::stoi(values[0]); // Converta para int, se necessario
			int id = std::stoi(values[1]);
			std::string login = values[2];
			std::string pass = values[3];

			// Processa os dados lidos
			if (identification == 2) {
				Elector elector = Elector(id, login, pass);
				votingSystem.addElector(elector);
			}
		}
		else if (values.size() == 6) {
			// Lida com 6 colunas (Eleicao)
			int identification = std::stoi(values[0]); // Converta para int, se necessario
			std::string name = values[1];
			std::string startDate = values[2];
			std::string startTime = values[3];
			std::string endDate = values[4];
			std::string endTime = values[5];

			// Processa os dados lidos
			if (identification == 4) {
				std::tm start;
				std::tm end;
				std::istringstream issStart(startDate + " " + startTime);
				std::istringstream issEnd(endDate + " " + endTime);
				issStart >> std::get_time(&start, "%Y-%m-%d %H:%M:%S");
				issEnd >> std::get_time(&end, "%Y-%m-%d %H:%M:%S");
				std::chrono::system_clock::time_point startTP = std::chrono::system_clock::from_time_t(std::mktime(&start));
				std::chrono::system_clock::time_point endTP = std::chrono::system_clock::from_time_t(std::mktime(&end));
				Election election = Election(name, startTP, endTP);
				votingSystem.addElection(election);
			}
			else if (identification == 3) {
				int identification = std::stoi(values[0]); // Converta para int, se necessario
				int id = std::stoi(values[1]);
				int number = std::stoi(values[2]);
				std::string name = values[3];
				std::string party = values[4];
				std::string election = values[5];

				// Processa os dados lidos
				if (identification == 3) {
					Candidate candidate = Candidate(id, number, name, party, election);
					votingSystem.addCandidate(candidate);
				}
			}
		}
		else {
			std::cout << "Erro ao ler o arquivo, numero de colunas invalido." << std::endl;
			continue; // Continue para a proxima linha se tiver erro
		}
	}

	file.close();
	return counter;
}

static Admin FirstUse() {
	std::string login;
	std::string pass;

	std::cout << "Primeiro Acesso! Vamos cadastra-lo como administrador deste sistema!" << std::endl;
	std::cout << "Insira o seu nome de usuario (sem espacos): ";
	std::getline(std::cin, login);
	std::istringstream iss(login);
	iss >> login;
	std::cout << "Insira a sua senha: ";
	std::cin >> pass;
	std::cout << std::endl;

	Admin adm = Admin(login, pass);

	std::cout << "Registrado com sucesso!" << std::endl;
	std::cout << "Seu login e: " << login << std::endl;
	std::cout << "Sua senha e: " << pass << std::endl << std::endl;
	std::cout << "Pressione Enter para continuar...";

	std::cin.get();

	return adm;
}

int main() {
	VotingSystem votingSystem;

	int databaseResponse = CheckDatabase(votingSystem);
	if (databaseResponse == 0) {
		Admin adm = FirstUse();
		votingSystem.addAdmin(adm);
	}
	std::cin.ignore();
	votingSystem.showMainMenu();
}