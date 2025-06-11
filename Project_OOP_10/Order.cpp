#include "Order.h"
#include "Constants.h"
#include <iostream>

Order::Order() {
    id = getLatestOrderId() + 1;
    itemCount = 0;
    totalPrice = 0.0;
    earnedPoints = 0;
    status = PENDING;

    // Initialize EGN to empty string
    clientEGN.data[0] = '\0';

    // Optional: initialize arrays
    for (int i = 0; i < MAX_ORDER_ITEMS; ++i) {
        productIds[i] = 0;
        quantities[i] = 0;
    }
}

Order::Order(int _id, int* _productIds, int* _quantities, int _itemCount, double _totalPrice, int _earnedPoints, OrderStatus _status, String _clientEGN)
{
    id = _id;
    for (int i = 0; i < _itemCount; i++) {
        productIds[i] = _productIds[i];
        quantities[i] = _quantities[i];
    }
    itemCount = _itemCount;
    totalPrice = _totalPrice;
    earnedPoints = _earnedPoints;
    status = _status;
    clientEGN = _clientEGN;
}

void Order::addItem(int productId, int quantity) {
    if (itemCount < MAX_ORDER_ITEMS) {
        productIds[itemCount] = productId;
        quantities[itemCount] = quantity;
        itemCount++;
    }
}

void Order::setClientEGN(const String egn) {
    clientEGN = egn;
}

const String Order::getClientEGN() const {
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

String* Order::saveData(int& length) const
{
    String* arr = new String[itemCount + 1];
    length = itemCount;
    String item;
    String charId;
    convertToString(id, charId);
    item.append(charId);
    item.append(":");
    item.append(clientEGN);
    item.append(":");
    String charCount;
    convertToString(itemCount, charCount);
    item.append(charCount);
    item.append(":");
    String charTotal;
    convertDoubleToString(totalPrice, charTotal);
    item.append(charTotal);
    item.append(":");
    String charPoints;
    convertToString(earnedPoints, charPoints);
    item.append(":");
    String charStatus;
    convertToString(status, charStatus);
    item.append(charStatus);
    arr[0] = item;

    for (int i = 0; i < itemCount + 1; i++) {
        String prod;
        prod.append(charId);
        prod.append(":");
        String prodIdChar;
        convertToString(productIds[i], prodIdChar);
        prod.append(prodIdChar);
        prod.append(":");
        String prodQChar;
        convertToString(quantities[i], prodQChar);
        prod.append(prodQChar);
        arr[i + 1] = prod;
    }
    
    return arr;
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

int Order::getId() const
{
    return id;
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

int getLatestOrderId()
{
    ifstream file(ORDERS_FILE);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return -1;
    }
    int tempId;
    file >> tempId;
    file.close();
    return tempId;
}
