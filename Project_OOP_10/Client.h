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
};
