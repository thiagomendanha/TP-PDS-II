#include "User.h"

User::User(const std::string& loginUser, const std::string& passUser) 
	: login(loginUser), pass(passUser) {}

std::string User::getLogin() const {
	return login;
}

void User::setLogin(const std::string& newLogin) {
	login = newLogin;
}

void User::setPass(const std::string& newPass) {
	pass = newPass;
}