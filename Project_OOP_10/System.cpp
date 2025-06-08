#include "System.h"
#include "Client.h"
#include "Admin.h"
#include "Business.h"
#include <iostream>
#include <fstream>

System* System::instance = nullptr;

System& System::getInstance() {
    if (!instance)
        instance = new System();
    return *instance;
}


// ---------- String Comparison Helpers ----------
bool str_equal(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

bool starts_with(const char* str, const char* prefix) {
    int i = 0;
    while (prefix[i] != '\0') {
        if (str[i] != prefix[i]) return false;
        i++;
    }
    return true;
}

// ---------- System Constructor ----------
System::System()
    : userCount(0), orderCount(0), productCount(0), currentUser(nullptr) {
    for (int i = 0; i < MAX_USERS; ++i)
        users[i] = nullptr;
}

// ---------- User Operations ----------
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

    if (str_equal(role, "Client")) {
        users[userCount++] = new Client(name, egn, password);
        std::cout << "Client registered.\n";
    }
    else if (str_equal(role, "Business")) {
        users[userCount++] = new Business(name, egn, password);
        std::cout << "Business registered.\n";
    }
    else if (str_equal(role, "Admin")) {
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
        if (str_equal(users[i]->getName(), name) && users[i]->checkPassword(password)) {
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

// ---------- Product Operations ----------
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

Product* System::findProductById(int id) {
    for (int i = 0; i < productCount; ++i) {
        if (products[i].getId() == id) {
            return &products[i];
        }
    }
    return nullptr;
}

// ---------- Main App Loop ----------
void System::run() {
    char command[100];

    while (true) {
        std::cout << "> ";
        std::cin.getline(command, 100);

        if (str_equal(command, "register")) registerUser();
        else if (str_equal(command, "login")) login();
        else if (str_equal(command, "logout")) logout();
        else if (str_equal(command, "help") && currentUser) currentUser->help();
        else if (str_equal(command, "view-profile") && currentUser) currentUser->viewProfile();
        else if (str_equal(command, "exit")) { logout(); break; }
        else if (str_equal(command, "add-item")) addItem();
        else if (str_equal(command, "list-products")) listProducts();
        else if (starts_with(command, "view-product")) {
            int id;
            if (sscanf_s(command, "view-product %d", &id) == 1) viewProduct(id);
            else std::cout << "Usage: view-product [product_id]\n";
        }
        else if (currentUser) handleClientCommand(command);
        else std::cout << "Unknown or unauthorized command.\n";
    }
}

void System::handleClientCommand(const char* command) {
    Client* client = dynamic_cast<Client*>(currentUser);
    if (!client) return;

    if (starts_with(command, "add-to-cart")) {
        int id, qty;
        if (sscanf_s(command, "add-to-cart %d %d", &id, &qty) == 2) {
            Product* p = findProductById(id);
            if (p && p->isAvailable() && p->getQuantity() >= qty) {
                client->addToCart(id, qty);
                std::cout << "Added to cart.\n";
            }
            else {
                std::cout << "Invalid product or quantity.\n";
            }
        }
        else {
            std::cout << "Usage: add-to-cart [product_id] [qty]\n";
        }
    }
    else if (starts_with(command, "remove-from-cart")) {
        int id, qty;
        if (sscanf_s(command, "remove-from-cart %d %d", &id, &qty) == 2) {
            client->removeFromCart(id, qty);
        }
        else {
            std::cout << "Usage: remove-from-cart [product_id] [qty]\n";
        }
    }
    else if (str_equal(command, "view-cart")) {
        client->viewCart(products, productCount);
    }
    else if (str_equal(command, "checkout")) {
        checkout();
    }
}

// ---------- Checkout ----------
void System::checkout() {
    Client* client = dynamic_cast<Client*>(currentUser);
    if (!client) {
        std::cout << "Only clients can checkout.\n";
        return;
    }

    Cart& cart = client->getCart();
    if (cart.isEmpty()) {
        std::cout << "Your cart is empty.\n";
        return;
    }

    if (orderCount >= MAX_ORDERS) {
        std::cout << "Order system is full.\n";
        return;
    }

    Order newOrder;
    double total = 0.0;

    for (int i = 0; i < cart.getItemCount(); ++i) {
        int pid = cart.getProductIdAt(i);
        int qty = cart.getQuantityAt(i);

        if (qty <= 0) continue;

        Product* p = findProductById(pid);
        if (!p || !p->isAvailable() || p->getQuantity() < qty) {
            std::cout << "Checkout failed. Invalid product ID: " << pid << "\n";
            return;
        }

        p->decreaseQuantity(qty);
        newOrder.addItem(pid, qty);
        total += p->getPrice() * qty;
    }

    newOrder.setClientEGN(client->getEGN());
    newOrder.setTotal(total);
    newOrder.setPoints(static_cast<int>(total * 0.05));
    newOrder.setStatus(PENDING);

    orders[orderCount++] = newOrder;
    cart = Cart(); // clear cart
    std::cout << "Order placed successfully. Awaiting approval.\n";
}
