#pragma once
#include <iostream>
#include "String.h"

class User {
protected:
    String name;
    String egn;
    String password;
public:
    User();
    User(const String nameInput, const String egnInput, const String passwordInput);

    virtual void help() const = 0;
    virtual void logout() = 0;
    virtual void viewProfile() const;
    virtual String getRole() const;
    virtual String saveData() const;

    const String getName() const;
    const String getEGN() const;
    bool checkPassword(const String pass) const;
};
