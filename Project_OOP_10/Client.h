#pragma once
#include "User.h"
#include "Cart.h"



class Client : public User {
private:
    Cart cart;
public:
    Client(const char* name, const char* egn, const char* password);
    void help() const override;
    void logout() override;

    Cart& getCart();

    void addToCart(int productId, int quantity);
    void removeFromCart(int productId, int quantity);
    void viewCart(Product* products, int productCount) const;

};
