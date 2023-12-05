#include "VotingSystem.h"

void VotingSystem::addAdmin(const Admin& admin) {
	auto foundAdmin = std::find_if(admins.begin(), admins.end(), [&](const Admin& adm) {
		return adm.getLogin() == admin.getLogin();
		});

	if (foundAdmin != admins.end()) {
		std::cout << "Nao pode ser registrado pois esse administrador ja existe." << std::endl;
	}
	else {
		admins.push_back(admin);
	}
}

void VotingSystem::clearAllAdmin() {
	admins.clear();
}

Admin* VotingSystem::authenticateAdmin(const std::string& login, const std::string& pass) {
	for (auto& admin : admins) {
		if (admin.getLogin() == login && admin.comparePass(pass)) {
			return &admin;
		}
	}
	return nullptr;
}

Elector* VotingSystem::authenticateElector(const std::string& login, const std::string& pass) {
	for (auto& elector : electors) {
		if (elector.getLogin() == login && elector.comparePass(pass)) {
			return &elector;
		}
	}
	return nullptr;
}

Candidate* VotingSystem::getCandidateById(const int id) {
	for (auto& candidate : candidates) {
		if (candidate.getId() == id) {
			return &candidate; // Retorna o ponteiro para a eleicao encontrada
		}
	}
	return nullptr;
}

std::vector<Election> VotingSystem::getAllAvailableElections(Elector* authenticatedElector) {
	std::vector<Election> availableElections;

	for (const auto& election : elections) {
		if (election.isVotingOpen() && !election.hasVoted(authenticatedElector->getId())) {
			availableElections.push_back(election);
		}
	}

	return availableElections;
}

void VotingSystem::getResult(Election* election) {
	std::cout << "Resultado da eleicao no momento" << election->getName() << std::endl;

	std::vector<Candidate> current_candidates = this->getCandidatesByElection(election->getName());

	election->printResults(current_candidates);
	std::cout << std::endl;

	// espera o usuario apertar enter
	std::cout << "Pressione enter para continuar...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.ignore();
}

void VotingSystem::listAllElections() {
	// list election to user choose one
	this->clearScreen();
	std::cout << "Lista de eleicoes:" << std::endl;
	for (const auto& election : elections) {
		std::cout << std::endl;
		election.print();
	}
	std::cout << std::endl;

	// chose one election
	std::string electionName;
	std::cout << "Insira o nome da eleicao que voce deseja ver o resultado: ";
	std::cin >> electionName;
	Election* chosenElection = this->getElectionByName(electionName);
	if (chosenElection == nullptr) {
		std::cout << "Esta eleicao nao existe.\n\n";
		std::cout << "Precione Enter para continuar.\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();
		return;
	}
	this->getResult(chosenElection);
}

void VotingSystem::listAllAvailableElections(Elector* authenticatedElector) {
	std::vector<Election> availableElections = this->getAllAvailableElections(authenticatedElector);
	int i = 1;

	for (const auto& election : availableElections) {
		std::cout << "--- Opcao " << i << " ---" << std::endl;
		election.print();
		i++;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int VotingSystem::getOption() {
	int option;
	std::cin >> option;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 0;
	}
	return option;
}

void VotingSystem::clearScreen() {
#ifdef _WIN32
	system("cls"); // Comando para limpar tela no Windows
#else
	system("clear"); // Comando para limpar tela em sistemas Unix
#endif
}

void VotingSystem::showMainMenu() {
	while (true) {
		this->clearScreen();

		std::cout << "=====================\n";
		std::cout << "  MENU DE OPCOES\n";
		std::cout << "=====================\n";
		std::cout << "1. ADMINISTRADOR\n";
		std::cout << "2. ELEITOR\n";
		std::cout << "0. Sair\n";
		std::cout << "Escolha uma opcao: ";

		int option = getOption();
		if (option == 1) {
			this->handleAdminOption();
		}
		else if (option == 2) {
			this->handleElectorOption();
		}
		else if (option == 0) {
			break;
		}
		else {
			std::cout << "Opcao invalida. Tente outra: ";
		}
	}
}

void VotingSystem::showElectorMenu(Elector* authenticatedElector) {
	this->clearScreen();
	while (true) {
		std::cout << "Bem vindo! " << authenticatedElector->getLogin() << "!" << std::endl;

		int option;
		std::cout << "1 - Escolher eleicao disponivel\n";
		std::cout << "2 - Ver lista de candidatos\n";
		std::cout << "0 - Sair\n";
		std::cin >> option;

		switch (option) {
		case 1:
			this->handleElectorListElections(authenticatedElector);
			break;
		case 2:
			this->listCandidates();
			break;
		case 0:
			// Sai do menu
			this->clearScreen();
			return;
		default:
			std::cout << "Opção inválida. Tente novamente." << std::endl;
			break;
		}
	}
}

void VotingSystem::handleElectorOption() {
	std::string login;
	std::string pass;

	std::cout << "Login: ";
	std::cin >> login;
	std::cout << "Senha: ";
	std::cin >> pass;

	Elector* authenticatedElector = this->authenticateElector(login, pass);

	if (authenticatedElector != nullptr) {
		this->showElectorMenu(authenticatedElector);
	}
	else {
		this->clearScreen();
		std::cout << "Login ou senha incorretos." << std::endl << std::endl;
		return;
	}
}

void VotingSystem::handleElectorListElections(Elector* authenticatedElector) {
	this->clearScreen();

	while (true) {
		this->listAllAvailableElections(authenticatedElector);

		std::string electionName;
		std::cout << "Insira o nome da eleicao que voce deseja participar: ";
		std::cin >> electionName;

		Election* election = this->getElectionByName(electionName);

		if (election == nullptr) {
			std::cout << "Opcao invalida\n\n";
			std::cout << "Precione enter para continuar\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			this->clearScreen();
			break;
		}
		else {
			this->handleElectorVote(election, authenticatedElector);
			this->clearScreen();
			break;
		}
	}
}

void VotingSystem::handleElectorVote(Election* election, Elector* authenticatedElector) {
	std::vector<Candidate> availableCandidates = this->getCandidatesByElection(election->getName());

	for (const auto& candidate : availableCandidates) {
		std::cout << candidate.getNumber() << " - " << candidate.getName() << std::endl;
	}

	int candidateNumber;
	std::cout << "Insira o numero do candidato que voce deseja votar: ";
	std::cin >> candidateNumber;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, voce deve inserir um numero.\n";
		return;
	}

	Candidate* votedCandidate = this->getCandidateByNumber(candidateNumber);

	if (votedCandidate == nullptr) {
		std::cout << "Candidato nao encontrado." << std::endl;
		return;
	}

	election->voteForCandidate(authenticatedElector->getId(), votedCandidate->getId(), availableCandidates);
}

Candidate* VotingSystem::getCandidateByNumber(const int number) {
	for (auto& candidate : candidates) {
		if (candidate.getNumber() == number) {
			return &candidate; // Retorna o ponteiro para a eleicao encontrada
		}
	}
	return nullptr; // Retorna nullptr se não encontrar a eleicao
}

void VotingSystem::showAdminMenu(Admin* admin) {
	while (true) {
		this->clearScreen();

		std::cout << "Bem vindo! " << admin->getLogin() << "!\n";

		int option;
		std::cout << "1 - Gerenciar eleitores" << std::endl;
		std::cout << "2 - Gerenciar candidatos" << std::endl;
		std::cout << "3 - Definir eleicoes" << std::endl;
		std::cout << "4 - Verificar eleicoes" << std::endl;
		std::cout << "0 - Sair" << std::endl;
		std::cin >> option;

		switch (option) {
		case 1:
			// Lógica para gerenciar eleitores
			this->handleElectorsByAdmin();
			break;
		case 2:
			// Logicar para gerenciar candidatos
			this->handleCandidatesByAdmin();
			break;
		case 3:
			// Lógica para definir eleições
			this->handleElectionsByAdmin();
			break;
		case 4:
			// Lógica para verificar eleições
			this->listAllElections();
			break;
		case 0:
			// Sai do menu
			this->clearScreen();
			return;
		default:
			std::cout << "Opção inválida. Tente novamente." << std::endl;
			break;
		}
	}
}

void VotingSystem::handleAdminOption() {
	std::string login;
	std::string pass;

	std::cout << "Login: ";
	std::cin >> login;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Senha: ";
	std::cin >> pass;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Admin* admin = this->authenticateAdmin(login, pass);

	if (admin != nullptr) {
		this->showAdminMenu(admin);
	}
	else {
		this->clearScreen();
		std::cout << "Login ou senha incorretos.\n\n";
	}
}

void VotingSystem::handleElectorsByAdmin() {
	this->clearScreen();

	while (true) {
		std::cout << "1 - Adicionar Eleitor" << std::endl;
		std::cout << "2 - Remover Eleitor" << std::endl;
		std::cout << "3 - Listar Eleitores" << std::endl;
		std::cout << "0 - Sair" << std::endl;

		int option = getOption();

		switch (option) {
		case 1:
			this->handleAddElectorByAdmin();
			break;
		case 2:
			this->handleRemoveElectorByAdmin();
			break;
		case 3:
			this->listElectors();
			std::cout << std::endl;
			break;
		case 0:
			this->clearScreen();
			return;
		default:
			std::cout << "Opção inválida. Tente novamente.\n";
			break;
		}
	}
}

void VotingSystem::handleAddElectorByAdmin() {
	int id;
	std::string name;
	std::string pass;

	std::cout << "Insira o ID: ";
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, voce deve inserir um numero.\n";
		return;
	}
	// Ignora newline char do buffer
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Insira o nome: ";
	// Usa getline para ler a linha inteira, incluindo espaços
	std::getline(std::cin, name);
	std::cout << "Crie uma senha do eleitor: ";
	// Usa getline para ler a linha inteira, incluindo espaços
	std::getline(std::cin, pass);

	Elector newElector(id, name, pass);
	this->addElector(newElector);

	std::cout << std::endl;
}

void VotingSystem::handleRemoveElectorByAdmin() {
	int id;
	std::cout << "Insira o id do eleitor a ser excluido: ";
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, voce deve inserir um numero.\n";
	}
	else {
		this->removeElector(id);
		std::cout << std::endl;
	}
}

void VotingSystem::handleCandidatesByAdmin() {
	this->clearScreen();

	while (true) {
		int option;
		std::cout << "1 - Adicionar Candidato" << std::endl;
		std::cout << "2 - Remover Candidato" << std::endl;
		std::cout << "3 - Listar Candidatos" << std::endl;
		std::cout << "0 - Sair" << std::endl;
		std::cin >> option;

		switch (option) {
		case 1: {
			this->handleAddCandidateByAdmin();
			break;
		}
		case 2: {
			this->handleRemoveCandidateByAdmin();
			break;
		}
		case 3: {
			this->listCandidates();
			break;
		}
		case 0: {
			this->clearScreen();
			return; // Sai do menu
		}
		default: {
			this->clearScreen();
			std::cout << "Opção inválida. Tente novamente.\n";
			break;
		}
		}
	}
}

void VotingSystem::handleAddCandidateByAdmin() {
	int id;
	int number;
	std::string name;
	std::string party;
	std::string election;

	std::cout << "Insira o ID: ";
	while (!(std::cin >> id)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, insira um numero: ";
	}

	std::cout << "Insira o numero do candidato: ";
	while (!(std::cin >> number)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, insira um numero: ";
	}

	std::cout << "Insira o nome do candidato: ";
	std::cin.ignore();
	std::getline(std::cin, name);

	std::cout << "Insira a sigla do partido: ";
	std::cin >> party;

	std::cout << "Insira a qual eleicao ele vai concorrer: ";
	std::cin >> election;

	Candidate newCandidate(id, number, name, party, election);
	this->addCandidate(newCandidate);

	this->clearScreen();
}

void VotingSystem::handleRemoveCandidateByAdmin() {
	int id;
	std::cout << "Insira o id do candidato a ser excluido: ";
	if (!(std::cin >> id)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Input invalido, insira um numero." << std::endl;
	}
	else {
		this->removeCandidate(id);
	}
}

void VotingSystem::handleElectionsByAdmin() {
	this->clearScreen();

	while (true) {
		int option;
		std::cout << "1 - Adicionar Eleicao" << std::endl;
		std::cout << "2 - Remover Eleicao" << std::endl;
		std::cout << "3 - Listar Eleicoes" << std::endl;
		std::cout << "0 - Sair" << std::endl;
		std::cin >> option;

		switch (option) {
		case 1: {
			this->handleAddElectionByAdmin();
			break;
		}
		case 2: {
			this->handleRemoveElectionByAdmin();
			break;
		}
		case 3: {
			this->listElections();
			break;
		}
		case 0: {
			// Sai do menu
			this->clearScreen();
			return;
		}
		default: {
			this->clearScreen();
			std::cout << "Opção inválida. Tente novamente.\n";
			break;
		}
		}
	}
}

void VotingSystem::handleAddElectionByAdmin() {
	std::string electionName;
	std::string userInput;

	std::cout << "Insira o nome da eleicao: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, electionName);

	Election* ele = this->getElectionByName(electionName);

	if (ele != nullptr) {
		std::cout << "Eleicao ja existe!" << std::endl;
		return;
	}

	auto parseDate = [](const std::string& userInput) -> std::pair<bool, std::chrono::system_clock::time_point> {
		std::tm tm = {};
		std::istringstream ss(userInput);
		ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

		if (ss.fail()) {
			std::cout << "Formato de data invalido.\n";
			return { false, std::chrono::system_clock::time_point() };
		}

		std::time_t time = std::mktime(&tm);
		if (time == -1) {
			std::cout << "Erro ao converter a data.\n";
			return { false, std::chrono::system_clock::time_point() };
		}

		return { true, std::chrono::system_clock::from_time_t(time) };
		};

	std::cout << "Insira a data de inicio no formato (YYYY-MM-DD HH:MM:SS): ";
	std::getline(std::cin, userInput);


	auto startDate = parseDate(userInput);
	if (!startDate.first) {
		return;
	}

	std::cout << "Insira a data de fim (YYYY-MM-DD HH:MM:SS): ";
	std::getline(std::cin, userInput);


	auto endDate = parseDate(userInput);
	if (!endDate.first) {
		return;
	}

	if (endDate.second < startDate.second) {
		std::cout << "A data de fim nao pode ser anterior a data de inicio.\n";
		return;
	}

	Election newElection = Election(electionName, startDate.second, endDate.second);
	this->addElection(newElection);
}

void VotingSystem::handleRemoveElectionByAdmin() {
	std::string name;
	std::cout << "Insira o nome da eleicao a ser excluida: ";
	std::cin >> name;
	this->removeElection(name);
	std::cout << std::endl;
}

void VotingSystem::addElector(const Elector& newElector) {
	auto foundElector = std::find_if(electors.begin(), electors.end(), [&](const Elector& elector) {
		return elector.getId() == newElector.getId();
		});

	if (foundElector != electors.end()) {
		std::cout << "Nao pode ser registrado pois esse eleitor ja existe." << std::endl;
	}
	else {
		electors.push_back(newElector);
	}
}

void VotingSystem::listElectors() {
	std::cout << std::endl << "Lista de Eleitores:" << std::endl;
	for (const auto& elector : electors) {
		std::cout << "ID: " << elector.getId() << " | Nome: " << elector.getLogin() << std::endl;
	}
}

int VotingSystem::addElection(const Election newElection) {
	auto foundElection = std::find_if(elections.begin(), elections.end(), [&](const Election& election) {
		return election.getName() == newElection.getName();
		});

	if (foundElection != elections.end()) {
		std::cout << "Nao pode ser registrado pois essa eleicao ja existe." << std::endl;
		return 0;
	}
	else {
		this->elections.push_back(newElection);
		return 1;
	}
}

void VotingSystem::removeElection(std::string election) {
	auto it = std::remove_if(elections.begin(), elections.end(), [&](const Election& e) {
		return e.getName() == election;
		});

	if (it != elections.end()) {
		elections.erase(it, elections.end());
		std::cout << "Eleicao removido com sucesso." << std::endl;
	}
	else {
		std::cout << "Eleicao nao encontrado." << std::endl;
	}
}

Election* VotingSystem::getElectionByName(const std::string electionName) {
	for (auto& election : elections) {
		if (election.getName() == electionName) {
			return &election; // Retorna o ponteiro para a eleicao encontrada
		}
	}
	return nullptr; // Retorna nullptr se não encontrar a eleicao
}

void VotingSystem::listElections() {
	std::cout << "Imprimindo informacao de eleicoes:" << std::endl;
	for (const auto& election : this->elections) {
		election.print();

		std::vector<Candidate> current_candidates = this->getCandidatesByElection(election.getName());
		for (auto it = current_candidates.begin(); it != current_candidates.end(); ++it) {
			(*it).print();
		}
	}
	std::cout << std::endl << std::endl;
}

std::vector<Candidate> VotingSystem::getCandidatesByElection(const std::string& electionName) {
	std::vector<Candidate> filteredCandidates;

	for (const auto& candidate : candidates) {
		if (candidate.getElection() == electionName) {
			filteredCandidates.push_back(candidate);
		}
	}

	return filteredCandidates;
}

void VotingSystem::removeElector(const int electorId) {
	auto it = std::remove_if(electors.begin(), electors.end(), [&](const Elector& e) {
		return e.getId() == electorId;
		});

	if (it != electors.end()) {
		electors.erase(it, electors.end());
		std::cout << "Elector removido com sucesso." << std::endl;
	}
	else {
		std::cout << "Elector nao encontrado." << std::endl;
	}
}

void VotingSystem::addCandidate(const Candidate& candidate) {
	auto it = std::find_if(this->candidates.begin(), this->candidates.end(), [&](const Candidate& c) {
		return c.getId() == candidate.getId();
		});

	if (it == candidates.end()) {
		candidates.push_back(candidate);
	}
	else {
		std::cout << "Candidato com mesmo ID ja existe." << std::endl;
	}
}

void VotingSystem::removeCandidate(int id) {
	auto it = std::find_if(candidates.begin(), candidates.end(), [&](const Candidate& c) {
		return c.getId() == id;
		});

	if (it != candidates.end()) {
		candidates.erase(it);
		std::cout << "Candidato removido com sucesso." << std::endl;
	}
	else {
		std::cout << "Candidato nao encontrado." << std::endl;
	}
}

void VotingSystem::listCandidates() {
	for (auto it = candidates.begin(); it != candidates.end(); ++it) {
		(*it).print();
	}

	std::cout << std::endl << std::endl;
}
