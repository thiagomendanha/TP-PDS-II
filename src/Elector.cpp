#include "Elector.h"

Elector::Elector(const int id, const std::string& login, const std::string& pass)
	: User(login, pass) {
    this->id = id;
}

int Elector::getId() const {
	return this->id;
}

bool Elector::comparePass(const std::string& password)
{
	return pass == password;
}
