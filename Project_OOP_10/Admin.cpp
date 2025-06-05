#include "Admin.h"
#include <iostream>

Admin::Admin(const char* name, const char* egn, const char* password)
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
