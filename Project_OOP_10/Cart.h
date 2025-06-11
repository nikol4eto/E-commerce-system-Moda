#pragma once
#include "Product.h"
#include "String.h"

class Cart {
private:
    static const int MAX_ITEMS = 100;
    String clientEgn;
    int productIds[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;

public:
    Cart();

    void addItem(int productId, int quantity);
    void removeItem(int productId, int quantity);
    void viewCart(Product* products, int productCount) const;
    double calculateTotal(Product* products, int productCount) const;
    bool isEmpty() const;
    String getClientEgn();
    int getItemCount() const;
    int getProductIdAt(int index) const;
    int getQuantityAt(int index) const;
};
