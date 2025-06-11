#include "User.h"

User::User() {}

User::User(const String nameInput, const String egnInput, const String passwordInput) {
    name = nameInput;
    egn = egnInput;
    password = passwordInput;
}

void User::viewProfile() const {
    std::cout << "Name: " << name.data << "\nEGN: " << egn.data << std::endl;
}

String User::getRole() const
{
    return String("None");
}

String User::saveData() const
{
    String item = String();
    item.append("None");
    item.append(":");
    item.append(name);
    item.append(":");
    item.append(egn);
    item.append(":");
    item.append(password);

    return item;
}

const String User::getName() const {
    return name;
}

const String User::getEGN() const {
    return egn;
}


bool User::checkPassword(const String pass) const {
    int i = 0;
    while (password.data[i] != '\0' && pass.data[i] != '\0') {
        if (password.data[i] != pass.data[i]) return false;
        i++;
    }
    return password.data[i] == pass.data[i]; //  must reach '\0' at the same time
}
