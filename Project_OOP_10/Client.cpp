#include "Client.h"
#include <iostream>

Client::Client(const String name, const String egn, const String password, double _balance, int _points, Cart _cart)
    : User(name, egn, password) {
    balance = _balance;
    points = _points;
    cart = _cart;
}

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

String Client::getRole() const
{
    return String("Client");
}

Cart& Client::getCart() {
    return cart;
}

double Client::getBalance()
{
    return balance;
}

String Client::saveData() const
{
    String item = String();
    item.append("Client");
    item.append(":");
    item.append(name);
    item.append(":");
    item.append(egn);
    item.append(":");
    item.append(password);
    item.append(":");
    String charBal;
    convertDoubleToString(balance, charBal);
    item.append(charBal);
    item.append(":");
    String charPts;
    convertDoubleToString(balance, charPts);
    item.append(charPts);

    return item;
}

void Client::addToCart(int productId, int quantity) {
    cart.addItem(productId, quantity);
    std::cout << "Item added to cart.\n";
}

void Client::removeFromCart(int productId, int quantity) {
    cart.removeItem(productId, quantity);
    std::cout << "Item removed from cart.\n";
}

void Client::viewCart(Product* products, int productCount) const {
    cart.viewCart(products, productCount);
}

void Client::redeemCheque(Check cheque, String _code)
{
    if (cheque.isUsed()) {
        cout << "Cheque already used!" << endl;
        return;
    }
    if (!cheque.userAuthorized(egn)) {
        cout << "You are not authorized to use this cheque!" << endl;
        return;
    }
}

void Client::ckeckBalance()
{
    cout << "Balance: " << balance << endl
        << "Points: " << points << endl;
}

