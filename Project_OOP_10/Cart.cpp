#include "Cart.h"
#include "Product.h"
#include <iostream>

Cart::Cart() {

    itemCount = 0;
    for (int i = 0; i < MAX_ITEMS; ++i) {
        productIds[i] = 0;
        quantities[i] = 0;
    }
}

void Cart::addItem(int productId, int quantity) {
    for (int i = 0; i < itemCount; ++i) {
        if (productIds[i] == productId) {
            quantities[i] += quantity;
            return;
        }
    }

    if (itemCount < MAX_ITEMS) {
        productIds[itemCount] = productId;
        quantities[itemCount] = quantity;
        itemCount++;
    }
    else {
        std::cout << "Cart is full.\n";
    }
}

void Cart::removeItem(int productId, int quantity) {
    for (int i = 0; i < itemCount; ++i) {
        if (productIds[i] == productId) {
            quantities[i] -= quantity;
            if (quantities[i] <= 0) {
                for (int j = i; j < itemCount - 1; ++j) {
                    productIds[j] = productIds[j + 1];
                    quantities[j] = quantities[j + 1];
                }
                itemCount--;
            }
            return;
        }
    }
}

void Cart::viewCart(Product* products, int productCount) const {
    if (itemCount == 0) {
        std::cout << "Cart is empty.\n";
        return;
    }

    double total = 0.0;
    std::cout << "Items in cart:\n";

    for (int i = 0; i < itemCount; ++i) {
        int id = productIds[i];
        int qty = quantities[i];

        for (int j = 0; j < productCount; ++j) {
            if (products[j].getId() == id) {
                double price = qty * products[j].getPrice();
                total += price;
                std::cout << "- " << qty << "x " << products[j].getName().data
                    << " - " << price << " BGN\n";
                break;
            }
        }
    }

    std::cout << "Total price: " << total << " BGN\n";
}

double Cart::calculateTotal(Product* products, int productCount) const {
    double total = 0.0;
    for (int i = 0; i < itemCount; ++i) {
        int id = productIds[i];
        int qty = quantities[i];

        for (int j = 0; j < productCount; ++j) {
            if (products[j].getId() == id) {
                total += qty * products[j].getPrice();
                break;
            }
        }
    }
    return total;
}

bool Cart::isEmpty() const {
    return itemCount == 0;
}

String Cart::getClientEgn()
{
    return clientEgn;
}

int Cart::getItemCount() const {
    return itemCount;
}

int Cart::getProductIdAt(int index) const {
    if (index >= 0 && index < itemCount) {
        return productIds[index];
    }
    return -1;
}

int Cart::getQuantityAt(int index) const {
    if (index >= 0 && index < itemCount) {
        return quantities[index];
    }
    return 0;
}


