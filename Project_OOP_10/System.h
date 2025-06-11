#pragma once
#include <iostream>
#include "User.h"
#include "Product.h"
#include "Order.h"
#include "Utils.h"
#include "String.h"
#include "Constants.h"
#include "Check.h"
#include "Cart.h"

int const MAX_CARTS = 100;
int const MAX_USERS = 100;
int const MAX_PRODUCTS = 100;
int const MAX_ORDERS = 100;
int const MAX_CHEQUES = 100;

class System {
private:
    static System* instance;

    Cart** carts = new Cart*[MAX_CARTS];
    int cartCount;

    User** users = new User*[MAX_USERS];
    int userCount;

    Order** orders = new Order*[MAX_ORDERS];
    int orderCount;

    Product** products = new Product*[MAX_PRODUCTS];
    int productCount;

    Check** cheques = new Check*[MAX_CHEQUES];
    int chequesCount;

    User* currentUser;
    String currentRole;

    Product* findProductById(int id);
    void checkout(); 

public:
    System();
    ~System();

    static System& getInstance();

    void run();
    void registerUser();
    void login();
    void logout();

    void addItem();
    void listProducts();
    void viewProduct(int id);
    void handleClientCommand(const String command);

    void load();
    void save() const;

    Product* getProducts() { return *products; }
    int getProductCount() const { return productCount; }

    Cart findCartByEgn(String egn);
};
