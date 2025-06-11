#include "Product.h"


int Product::nextId = 1;

Product::Product() {
    id = getLatestId() + 1;
    name = "\0";
    businessEgn = "\0";
    price = 0;
    quantity = 0;
    description = "\0";
    rating = 0;
    ratingCount = 0;
    available = 0;
}

Product::Product(String& nameInput, String _businessEgn, double priceInput, int quantityInput, String& descriptionInput) {
    id = nextId++;
    name = nameInput;
    businessEgn = _businessEgn;
    description = descriptionInput;
    price = priceInput;
    quantity = quantityInput;
    rating = 0;
    ratingCount = 0;
    if (quantityInput > 0)
        available = 1;
    else
        available = 0;
}

int Product::getId() const {
    return id;
}

const String Product::getName() const {
    return name;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

const String Product::getDescription() const {
    return description;
}

double Product::getRating() const {
    return (ratingCount == 0) ? 0 : rating;
}

bool Product::isAvailable() const {
    return quantity > 0;
}

void Product::decreaseQuantity(int q) {
    if (!available) {
        if (q <= quantity) {
            quantity -= q;
        }
        else {
            cout << "You are trying to purchase more than there is: available - " << quantity << endl;
            return;
        }
        if (quantity == 0)
            available = 0;
    }
    else
        cout << "There are no avaiable items of this product!" << endl;
}

void Product::increaseQuantity(int q) {
    quantity += q;
    if (!available && quantity > 0)
        available = 1;
}

void Product::rate(int stars) {
    if (stars >= 1 && stars <= 5) {
        rating = ((rating * ratingCount) + stars) / (ratingCount + 1);
        ratingCount++;
    }
}

String Product::saveData()
{
    String item = String();
    String charId;
    convertToString(id, charId);
    item.append(charId);
    item.append(":");
    item.append(businessEgn);
    item.append(":");
    item.append(name);
    item.append(":");
    String charPrice;
    convertDoubleToString(price, charPrice);
    item.append(charPrice);
    item.append(":");
    String charQuantity;
    convertToString(quantity, charQuantity);
    item.append(charQuantity);
    item.append(":");
    item.append(description);
    item.append(":");
    String charRating;
    convertDoubleToString(rating, charRating);
    item.append(charRating);
    item.append(":");
    String charRatingCount;
    convertToString(ratingCount, charRatingCount);
    item.append(charRatingCount);
    item.append(":");
    String charAvailable;
    convertToString(available, charAvailable);
    item.append(charAvailable);

    return item;
}

void Product::printSummary() const {
    std::cout << id << " | " << name.data << " | " << price << " BGN | "
        << getRating() << " star | " << quantity << " quantity\n";
}

void Product::printDetailed() const {
    std::cout << "ID: " << id << "\n"
        << "Product Name: " << name.data << "\n"
        << "Price: " << price << " BGN\n"
        << "Stock: " << quantity << " pcs\n"
        << "Rating: " << getRating() << " stars\n"
        << "Description: " << description.data << "\n";
}

int Product::getLatestId()
{
    ifstream file(PRODUCTS_FILE);
    if (!file.is_open()) {
        cout << "Failed to open file!" << endl;
        return -1;
    }
    int tempId = 0;
    file >> tempId;
    file.close();
    return tempId;
}
