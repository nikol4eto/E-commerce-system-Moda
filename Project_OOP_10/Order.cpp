#include "Order.h"
#include <iostream>

Order::Order() {
    itemCount = 0;
    totalPrice = 0.0;
    earnedPoints = 0;
    status = PENDING;

    // Initialize EGN to empty string
    clientEGN[0] = '\0';

    // Optional: initialize arrays
    for (int i = 0; i < MAX_ORDER_ITEMS; ++i) {
        productIds[i] = 0;
        quantities[i] = 0;
    }
}

void Order::addItem(int productId, int quantity) {
    if (itemCount < MAX_ORDER_ITEMS) {
        productIds[itemCount] = productId;
        quantities[itemCount] = quantity;
        itemCount++;
    }
}

void Order::setClientEGN(const char* egn) {
    int i = 0;
    while (egn[i] != '\0' && i < 14) {
        clientEGN[i] = egn[i];
        i++;
    }
    clientEGN[i] = '\0';
}

const char* Order::getClientEGN() const {
    return clientEGN;
}

void Order::setTotal(double price) {
    totalPrice = price;
}

double Order::getTotal() const {
    return totalPrice;
}

void Order::setPoints(int points) {
    earnedPoints = points;
}

int Order::getPoints() const {
    return earnedPoints;
}

void Order::setStatus(OrderStatus s) {
    status = s;
}

OrderStatus Order::getStatus() const {
    return status;
}

void Order::printSummary() const {
    std::cout << "Order total: " << totalPrice << " BGN | Status: ";
    switch (status) {
    case PENDING: std::cout << "Pending"; break;
    case SHIPPED: std::cout << "Shipped"; break;
    case DELIVERED: std::cout << "Delivered"; break;
    }
    std::cout << std::endl;
}

void Order::printDetailed() const {
    std::cout << "Order details:\n";
    for (int i = 0; i < itemCount; ++i) {
        std::cout << "- Product ID: " << productIds[i] << ", Quantity: " << quantities[i] << "\n";
    }
    std::cout << "Total: " << totalPrice << " BGN\n"
        << "Loyalty Points: " << earnedPoints << "\n"
        << "Status: ";
    switch (status) {
    case PENDING: std::cout << "Pending"; break;
    case SHIPPED: std::cout << "Shipped"; break;
    case DELIVERED: std::cout << "Delivered"; break;
    }
    std::cout << std::endl;
}

int Order::getItemCount() const {
    return itemCount;
}

int Order::getProductIdAt(int index) const {
    if (index >= 0 && index < itemCount)
        return productIds[index];
    return -1;
}

int Order::getQuantityAt(int index) const {
    if (index >= 0 && index < itemCount)
        return quantities[index];
    return 0;
}
