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



// ---------- System Constructor ----------
System::System()
    : users(new User*[MAX_USERS]), userCount(0),
    orders(new Order*[MAX_ORDERS]), orderCount(0), 
    cheques(new Check*[MAX_CHEQUES]), chequesCount(0), 
    carts(new Cart*[MAX_CARTS]), cartCount(0), 
    products(new Product*[MAX_PRODUCTS]), productCount(0), 
    currentUser(nullptr) {}

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
        users[userCount++] = new Client(name, egn, password, 0, 0, Cart());
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
    String name, password;
    std::cout << "Name: ";
    std::cin.getline(name.data, 100);
    std::cout << "Password: ";
    std::cin.getline(password.data, 50);

    for (int i = 0; i < userCount; ++i) {
        if (str_equal(users[i]->getName(), name) && users[i]->checkPassword(password)) {
            currentUser = users[i];
            std::cout << "Login successful.\n";
            currentRole = users[i]->getRole();
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

System::~System()
{
    delete[] orders;
    delete[] carts;
    delete[] products;
    delete[] users;
    delete[] cheques;
}

// ---------- Product Operations ----------
void System::addItem() {
    if (!currentUser) {
        std::cout << "You must be logged in as a Business.\n";
        return;
    }

    Business* b = dynamic_cast<Business*>(currentUser);
    if (!currentRole.compare("Business")) {
        std::cout << "Only Business users can add items.\n";
        return;
    }

    char name[100], desc[200];
    double price;
    int quantity;

    std::cout << "Product name: ";
    std::cin.getline(name, 100);
    String nameT = name;
    std::cout << "Price: ";
    std::cin >> price;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    std::cin.ignore(); // clear newline
    std::cout << "Description: ";
    std::cin.getline(desc, 200);
    String descT = desc;

    if (productCount < MAX_PRODUCTS - 1) {
        Product a = Product(nameT, currentUser->getEGN(), price, quantity, descT);
        products[productCount++] = &a;
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
        if (products[i]->isAvailable())
            products[i]->printSummary();
    }
}

void System::viewProduct(int id) {
    for (int i = 0; i < productCount; ++i) {
        if (products[i]->getId() == id) {
            products[i]->printDetailed();
            return;
        }
    }
    std::cout << "Product with ID " << id << " not found.\n";
}

Product* System::findProductById(int id) {
    for (int i = 0; i < productCount; ++i) {
        if (products[i]->getId() == id) {
            return products[i];
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

void System::handleClientCommand(const String command) {
    Client* client = dynamic_cast<Client*>(currentUser);
    if (!client) return;

    if (starts_with(command, "add-to-cart")) {
        int id, qty;
        if (sscanf_s(command.data, "add-to-cart %d %d", &id, &qty) == 2) {
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
        if (sscanf_s(command.data, "remove-from-cart %d %d", &id, &qty) == 2) {
            client->removeFromCart(id, qty);
        }
        else {
            std::cout << "Usage: remove-from-cart [product_id] [qty]\n";
        }
    }
    else if (str_equal(command, "view-cart")) {
        client->viewCart(*products, productCount);
    }
    else if (str_equal(command, "checkout")) {
        checkout();
    }
}

void System::load()
{
    //Users Load
    ifstream Users(USERS_FILE);
    if (!Users.is_open()) {
        cout << "Failed to open file!" << endl
            << "Users load failed!" << endl;
        return;
    }
    int length = 0;
    Users >> length;
    for (int i = 0; i < length; i++) {
        String input;
        Users >> input.data;
        String* arr = stringToArray(input, ':');

        if (arr[0].compare("Admin")) {
            Admin a = Admin(arr[1], arr[2], arr[3]);
            users[userCount] = &a;
            userCount++;
        }
        if (arr[0].compare("Client")) {
            double balance = 0;
            int points = 0;
            tryConvertToDouble(arr[4].data, balance);
            tryConvertToInt(arr[5].data, points);
            Client a = Client(arr[1], arr[2], arr[3], balance, points, findCartByEgn(arr[2]));
            users[userCount] = &a;
            userCount++;
        }
        if (arr[0].compare("Business")) {
            Business a = Business(arr[1], arr[2], arr[3]);
            users[userCount] = &a;
            userCount++;
        }
    }

}

void System::save() const
{
    //Cheques Save
    ofstream cFile(CHEQUES_FILE);
    if (!cFile.is_open()) {
        cout << "Failed to open file!" << endl;
        cout << "Cheques save was unsuccessful!" << endl;
        return;
    }
    if (chequesCount > 0)
        cFile << cheques[chequesCount - 1]->getId() << endl;
    else
        cFile << -1 << endl;
    cFile << chequesCount << endl;
    for (int i = 0; i < chequesCount; i++) {
        String output = cheques[i]->saveData();
        cFile << output.data << endl;
    }
    cFile.close();

    //Orders Save
    ofstream oFile(ORDERS_FILE);
    if (!oFile.is_open()) {
        cout << "Failed to open file!" << endl;
        cout << "Orders save was unsuccessful!" << endl;
        return;
    }
    if (orderCount > 0)
        oFile << orders[orderCount - 1]->getId() << endl;
    else
        oFile << -1 << endl;
    for (int i = 0; i < orderCount; i++) {
        int length;
        String* output = orders[i]->saveData(length);
        oFile << output[0].data << endl;
        for (int k = 0; k < length; k++) {
            oFile << output[k + 1].data << endl;
        }
    }
    oFile.close();

    //Users Save
    ofstream uFile(USERS_FILE, ios::trunc);
    if (!uFile.is_open()) {
        cout << "Failed to open file!" << endl;
        cout << "Users save was unsuccessful!" << endl;
        return;
    }
    uFile << userCount << endl;
    for (int i = 0; i < userCount; i++) {
        String output = users[i]->saveData();
        uFile << output.data << endl;
    }
    uFile.close();

    //Products Save
    ofstream pFile(PRODUCTS_FILE, ios::trunc);

    if (!pFile.is_open()) {
        cout << "Failed to open file!" << endl;
        cout << "Products save was unsuccessful!" << endl;
        return;
    }
    if (productCount > 0)
        pFile << products[productCount - 1]->getId() << endl;
    else
        pFile << -1 << endl;
    pFile << productCount << endl;
    for (int i = 0; i < productCount; i++) {
        String output = products[i]->saveData();
        pFile << output.data << endl;
    }

    pFile.close();
}

Cart System::findCartByEgn(String egn)
{
    for (int i = 0; i < cartCount; i++) {
        Cart a = *carts[i];
        if (a.getClientEgn().compare(egn)) {
            return a;
        }
    }
}

// ---------- Checkout ----------
void System::checkout() {
    Client* client = dynamic_cast<Client*>(currentUser);
    if (!currentRole.compare("Client")) {
        std::cout << "Only clients can checkout.\n";
        return;
    }

    Cart cart = client->getCart();
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

    orders[orderCount++] = &newOrder;
    cart = Cart(); // clear cart
    std::cout << "Order placed successfully. Awaiting approval.\n";
}
