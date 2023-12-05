#pragma once
#include "User.h"
#include <string>

class Elector : public User {
private:
	int id;
public:
	Elector(const int id, const std::string& login, const std::string& pass);

	int getId() const;

	bool comparePass(const std::string& password);
};

