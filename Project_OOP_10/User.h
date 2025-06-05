#pragma once
#include <iostream>

class User {
protected:
    char name[100];
    char egn[15];
    char password[50];
public:
    User(const char* nameInput, const char* egnInput, const char* passwordInput);
    virtual ~User() {}

    virtual void help() const = 0;
    virtual void logout() = 0;
    virtual void viewProfile() const;

    const char* getName() const;
    const char* getEGN() const;
    bool checkPassword(const char* pass) const;
};
