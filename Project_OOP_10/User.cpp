#include "User.h"

User::User(const char* nameInput, const char* egnInput, const char* passwordInput) {
    //  copy  name
    int i = 0;
    while (nameInput[i] != '\0' && i < 99) {
        name[i] = nameInput[i];
        i++;
    }
    name[i] = '\0';

    //  copy  EGN
    i = 0;
    while (egnInput[i] != '\0' && i < 14) {
        egn[i] = egnInput[i];
        i++;
    }
    egn[i] = '\0';

    //  copy for password
    i = 0;
    while (passwordInput[i] != '\0' && i < 49) {
        password[i] = passwordInput[i];
        i++;
    }
    password[i] = '\0';
}

void User::viewProfile() const {
    std::cout << "Name: " << name << "\nEGN: " << egn << std::endl;
}

const char* User::getName() const {
    return name;
}

const char* User::getEGN() const {
    return egn;
}

bool User::checkPassword(const char* pass) const {
    int i = 0;
    while (password[i] != '\0' && pass[i] != '\0') {
        if (password[i] != pass[i]) return false;
        i++;
    }
    return password[i] == pass[i]; //  must reach '\0' at the same time
}
