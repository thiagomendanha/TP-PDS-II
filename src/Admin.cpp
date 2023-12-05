#include "Admin.h";

Admin::Admin(const std::string& login, const std::string& pass)
	: User(login, pass) {}

bool Admin::comparePass(const std::string& password) {
	return pass == password;
}
