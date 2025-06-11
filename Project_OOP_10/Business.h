#pragma once
#include "User.h"
#include "String.h"

class Business : public User {
public:
    Business(const String name, const String egn, const String password);
    void help() const override;
    void logout() override;
    String getRole() const override;
    String saveData() const override;
};
