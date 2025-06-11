#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
#include "Constants.h"

using namespace std;
class Product {
private:
    static int nextId;
    int id;
    String businessEgn;
    String name;
    double price;
    int quantity;
    String description;
    double rating; // 0-5, average
    int ratingCount;
    bool available;
public:
    Product();
    Product(String& nameInput, String _businessEgn, double price, int quantity, String& descriptionInput);

    int getId() const;
    const String getName() const;
    double getPrice() const;
    int getQuantity() const;
    const String getDescription() const;
    double getRating() const;
    bool isAvailable() const;

    void decreaseQuantity(int q);
    void increaseQuantity(int q);
    void rate(int stars);
    String saveData();

    void printSummary() const;
    void printDetailed() const;
    int getLatestId();
};
