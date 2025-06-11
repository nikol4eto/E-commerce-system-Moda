#pragma once
#include "User.h"
#include "Cart.h"
#include "String.h"
#include "Check.h" 



class Client : public User {
private:
    double balance;
    double points;
    Cart cart;
public:
    Client(const String name, const String egn, const String password, double _balance, int _points, Cart _cart);
    void help() const override;
    void logout() override;    
    String getRole() const override;

    Cart& getCart();
    double getBalance();
    String saveData() const override;

    void addToCart(int productId, int quantity);
    void removeFromCart(int productId, int quantity);
    void viewCart(Product* products, int productCount) const;
    void redeemCheque(Check cheque, String _code);
    void ckeckBalance();
};
