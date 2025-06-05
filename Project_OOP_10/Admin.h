#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin(const char* name, const char* egn, const char* password);
    void help() const override;
    void logout() override;
};
