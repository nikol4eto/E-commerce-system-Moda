#pragma once

class Product;

class Cart {
private:
    static const int MAX_ITEMS = 100;
    int productIds[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount; // how many actual items in cart

public:
    Cart();

    void addItem(int productId, int quantity);
    void removeItem(int productId, int quantity);
    void viewCart(Product* products, int productCount) const;
    double calculateTotal(Product* products, int productCount) const;
    bool isEmpty() const;
};
