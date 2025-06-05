#include "Client.h"
#include <iostream>

Client::Client(const char* name, const char* egn, const char* password)
    : User(name, egn, password) {}

void Client::help() const {
    std::cout << "Available commands for Client:\n"
        << "- check-balance\n"
        << "- redeem [code]\n"
        << "- list-products\n"
        << "- filter-by-rating\n"
        << "- filter-by-price\n"
        << "- filter-by-alphabetical-order\n"
        << "- view-product [id]\n"
        << "- add-to-cart [id] [qty]\n"
        << "- remove-from-cart [id] [qty]\n"
        << "- apply-discount\n"
        << "- remove-discount\n"
        << "- view-cart\n"
        << "- checkout\n"
        << "- list-orders\n"
        << "- confirm-order [index]\n"
        << "- order-history\n"
        << "- rate [product_id] [1-5]\n"
        << "- request-refund\n"
        << "- refunded-orders\n";
}

void Client::logout() {
    std::cout << "Logged out successfully.\n";
}

Cart& Client::getCart() {
    return cart;
}
