#pragma once
#include <iostream>

class Product {
private:
    static int nextId;
    int id;
    char name[100];
    double price;
    int quantity;
    char description[200];
    double rating; // 0-5, average
    int ratingCount;
public:
    Product();
    Product(const char* nameInput, double price, int quantity, const char* descriptionInput);

    int getId() const;
    const char* getName() const;
    double getPrice() const;
    int getQuantity() const;
    const char* getDescription() const;
    double getRating() const;
    bool isAvailable() const;

    void decreaseQuantity(int q);
    void increaseQuantity(int q);
    void rate(int stars);

    void printSummary() const;
    void printDetailed() const;
};
