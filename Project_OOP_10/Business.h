#pragma once
#include "User.h"

class Business : public User {
public:
    Business(const char* name, const char* egn, const char* password);
    void help() const override;
    void logout() override;
};
