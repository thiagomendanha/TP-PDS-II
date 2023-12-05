#pragma once
#include <string>


class User {
protected:
	std::string login;
	std::string pass;

public:
	User(const std::string& loginUser, const std::string& passUser);

	std::string getLogin() const;
	
	void setLogin(const std::string& newLogin);
	void setPass(const std::string& newPass);
};

