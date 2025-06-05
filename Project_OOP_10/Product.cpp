#include "Product.h"

int Product::nextId = 1;

Product::Product() {
    id = nextId++;
    name[0] = '\0';
    price = 0;
    quantity = 0;
    description[0] = '\0';
    rating = 0;
    ratingCount = 0;
}

Product::Product(const char* nameInput, double priceInput, int quantityInput, const char* descriptionInput) {
    id = nextId++;
    // Copy name
    int i = 0;
    while (nameInput[i] != '\0' && i < 99) {
        name[i] = nameInput[i];
        i++;
    }
    name[i] = '\0';

    // Copy description
    i = 0;
    while (descriptionInput[i] != '\0' && i < 199) {
        description[i] = descriptionInput[i];
        i++;
    }
    description[i] = '\0';

    price = priceInput;
    quantity = quantityInput;
    rating = 0;
    ratingCount = 0;
}

int Product::getId() const {
    return id;
}

const char* Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

const char* Product::getDescription() const {
    return description;
}

double Product::getRating() const {
    return (ratingCount == 0) ? 0 : rating;
}

bool Product::isAvailable() const {
    return quantity > 0;
}

void Product::decreaseQuantity(int q) {
    if (q <= quantity) {
        quantity -= q;
    }
}

void Product::increaseQuantity(int q) {
    quantity += q;
}

void Product::rate(int stars) {
    if (stars >= 1 && stars <= 5) {
        rating = ((rating * ratingCount) + stars) / (ratingCount + 1);
        ratingCount++;
    }
}

void Product::printSummary() const {
    std::cout << id << " | " << name << " | " << price << " BGN | "
        << getRating() << " star | " << quantity << " quantity\n";
}

void Product::printDetailed() const {
    std::cout << "ID: " << id << "\n"
        << "Product Name: " << name << "\n"
        << "Price: " << price << " BGN\n"
        << "Stock: " << quantity << " pcs\n"
        << "Rating: " << getRating() << " stars\n"
        << "Description: " << description << "\n";
}
