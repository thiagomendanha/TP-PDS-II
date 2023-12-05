#pragma once
#include "User.h"
#include <string>

class Admin : public User {
public:
    Admin(const std::string& login, const std::string& pass);

    bool comparePass(const std::string& password);
};

