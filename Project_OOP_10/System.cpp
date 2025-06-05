#include "System.h"
#include "Client.h"
#include "Admin.h"
#include "Business.h"
#include <iostream>

System* System::instance = nullptr;

System::System() {}

System& System::getInstance() {
    if (!instance)
        instance = new System();
    return *instance;
}

void System::registerUser() {
    char name[100], egn[15], password[50], role[20];

    std::cout << "Name: ";
    std::cin.getline(name, 100);
    std::cout << "EGN: ";
    std::cin.getline(egn, 15);
    std::cout << "Password: ";
    std::cin.getline(password, 50);
    std::cout << "Select Role (Client, Business, Admin): ";
    std::cin.getline(role, 20);

    if (strcmp(role, "Client") == 0) {
        users[userCount++] = new Client(name, egn, password);
        std::cout << "Client registered.\n";
    }
    else if (strcmp(role, "Business") == 0) {
        users[userCount++] = new Business(name, egn, password);
        std::cout << "Business registered.\n";
    }
    else if (strcmp(role, "Admin") == 0) {
        users[userCount++] = new Admin(name, egn, password);
        std::cout << "Admin registered.\n";
    }
    else {
        std::cout << "Invalid role.\n";
    }
}

void System::login() {
    char name[100], password[50];
    std::cout << "Name: ";
    std::cin.getline(name, 100);
    std::cout << "Password: ";
    std::cin.getline(password, 50);

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i]->getName(), name) == 0 && users[i]->checkPassword(password)) {
            currentUser = users[i];
            std::cout << "Login successful.\n";
            return;
        }
    }
    std::cout << "Login failed.\n";
}

void System::logout() {
    if (currentUser) {
        currentUser->logout();
        currentUser = nullptr;
    }
}

void System::run() {
    char command[100];

    while (true) {
        std::cout << "> ";
        std::cin.getline(command, 100);

        if (strcmp(command, "register") == 0) {
            registerUser();
        }
        else if (strcmp(command, "login") == 0) {
            login();
        }
        else if (strcmp(command, "logout") == 0) {
            logout();
        }
        else if (strcmp(command, "help") == 0 && currentUser) {
            currentUser->help();
        }
        else if (strcmp(command, "view-profile") == 0 && currentUser) {
            currentUser->viewProfile();
        }
        else if (strcmp(command, "exit") == 0) {
            logout();
            break;
        }
        else if (strcmp(command, "add-item") == 0) {
            addItem();
        }
        else if (strcmp(command, "list-products") == 0) {
            listProducts();
        }
        else if (strncmp(command, "view-product", 12) == 0) {
            int id;
            if (sscanf(command, "view-product %d", &id) == 1)
                viewProduct(id);
            else
                std::cout << "Usage: view-product [product_id]\n";
        }
        else {
            std::cout << "Unknown or unauthorized command.\n";
        }
    }
}

void System::addItem() {
    if (!currentUser) {
        std::cout << "You must be logged in as a Business.\n";
        return;
    }

    Business* b = dynamic_cast<Business*>(currentUser);
    if (!b) {
        std::cout << "Only Business users can add items.\n";
        return;
    }

    char name[100], desc[200];
    double price;
    int quantity;

    std::cout << "Product name: ";
    std::cin.getline(name, 100);
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cin.ignore(); // clear newline
    std::cout << "Description: ";
    std::cin.getline(desc, 200);

    if (productCount < MAX_PRODUCTS) {
        products[productCount++] = Product(name, price, quantity, desc);
        std::cout << "Product added successfully.\n";
    }
    else {
        std::cout << "Product list is full.\n";
    }
}

void System::listProducts() {
    if (productCount == 0) {
        std::cout << "No products in the system.\n";
        return;
    }
    for (int i = 0; i < productCount; ++i) {
        if (products[i].isAvailable())
            products[i].printSummary();
    }
}

void System::viewProduct(int id) {
    for (int i = 0; i < productCount; ++i) {
        if (products[i].getId() == id) {
            products[i].printDetailed();
            return;
        }
    }
    std::cout << "Product with ID " << id << " not found.\n";
}
