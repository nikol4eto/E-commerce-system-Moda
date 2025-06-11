#pragma once
#include "User.h"
#include "String.h"
#include "Check.h"

class Admin : public User {
public:
    Admin();
    Admin(int id, const String name, const String egn, const String password);
    Admin(const String name, const String egn, const String password);
    void help() const override;
    void logout() override;
    String getRole() const override;
    String saveData() const override;

    void sendCheque(double _amount, String _code, String _clientEgn);
};
