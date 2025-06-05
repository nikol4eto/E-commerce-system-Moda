#pragma once
#include <iostream>
#include "User.h"
#include "Product.h"

#define MAX_USERS 100
#define MAX_PRODUCTS 100

class System {
private:
    static System* instance;
    User* users[MAX_USERS];
    int userCount = 0;

    Product products[MAX_PRODUCTS];
    int productCount = 0;

    User* currentUser = nullptr;

    System();
public:
    static System& getInstance();

    void run();
    void registerUser();
    void login();
    void logout();

    void addItem();
    void listProducts();
    void viewProduct(int id);
};
