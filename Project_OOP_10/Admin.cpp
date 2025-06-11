#include "Admin.h"
#include <iostream>

Admin::Admin() : User() {}

Admin::Admin(const String name, const String egn, const String password)
    : User(name, egn, password) {}

void Admin::help() const {
    std::cout << "Available commands for Admin:\n"
        << "- send-check [amount] [code] [client_egn]\n"
        << "- customer-insights\n"
        << "- view-transactions\n";
}

void Admin::logout() {
    std::cout << "Logged out from Admin profile.\n";
}

String Admin::getRole() const
{
    return String("Admin");
}

String Admin::saveData() const
{
    String item = String();
    item.append("Admin");
    item.append(":");
    item.append(name);
    item.append(":");
    item.append(egn);
    item.append(":");
    item.append(password);

    return item;
}

void Admin::sendCheque(double _amount, String _code, String _clientEgn)
{
    if (alreadyExists(_code)) {
        cout << "Cheque with that code already Exists!" << endl;
        return;
    }
    if (_amount <= 0) {
        cout << "Amount is not acceptable!" << endl;
        return;
    }
    Check newCheck = Check(_code, _clientEgn, _amount, 0);
    cout << "Cheque successfully created!" << endl;
}
