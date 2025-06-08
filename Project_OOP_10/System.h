#pragma once
#include <iostream>
#include "User.h"
#include "Product.h"
#include "Order.h"

#define MAX_USERS 100
#define MAX_PRODUCTS 100
#define MAX_ORDERS 100

class System {
private:
    static System* instance;

    User* users[MAX_USERS];
    int userCount;

    Order orders[MAX_ORDERS];
    int orderCount;

    Product products[MAX_PRODUCTS];
    int productCount;

    User* currentUser;

    Product* findProductById(int id);
    void checkout(); 

public:
    System();

    static System& getInstance();

    void run();
    void registerUser();
    void login();
    void logout();

    void addItem();
    void listProducts();
    void viewProduct(int id);
    void handleClientCommand(const char* command);

    Product* getProducts() { return products; }
    int getProductCount() const { return productCount; }
};
