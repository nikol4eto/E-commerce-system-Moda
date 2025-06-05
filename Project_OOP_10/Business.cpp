#include "Business.h"
#include <iostream>

Business::Business(const char* name, const char* egn, const char* password)
    : User(name, egn, password) {}

void Business::help() const {
    std::cout << "Available commands for Business:\n"
        << "- add-item [name] [price] [qty] [desc]\n"
        << "- remove-item [name]\n"
        << "- list-pending-orders\n"
        << "- approve-order [index]\n"
        << "- reject-order [index] [reason]\n"
        << "- list-orders\n"
        << "- list-best-selling-products\n"
        << "- view-revenue\n"
        << "- list-refunds\n"
        << "- approve-refund [index]\n"
        << "- reject-refund [index] [reason]\n";
}

void Business::logout() {
    std::cout << "Logged out from Business profile.\n";
}
