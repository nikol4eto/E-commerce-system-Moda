#pragma once

#include "String.h"
#include <fstream>

using namespace std;

int const MAX_ORDER_ITEMS = 100;

enum OrderStatus {
    PENDING,
    SHIPPED,
    DELIVERED
};

class Order {
private:
    int id;
    int productIds[MAX_ORDER_ITEMS];
    int quantities[MAX_ORDER_ITEMS];
    int itemCount;

    double totalPrice;
    int earnedPoints;

    OrderStatus status;

    String clientEGN; // link to client who made the order

public:
    Order();
    Order(int _id, int* _productIds, int* _quantities, int _itemCount, double _totalPrice, int _earnedPoints, OrderStatus _status, String _clientEGN);
    void addItem(int productId, int quantity);
    void setClientEGN(const String egn);
    const String getClientEGN() const;

    void setTotal(double price);
    double getTotal() const;

    void setPoints(int points);
    int getPoints() const;

    void setStatus(OrderStatus s);
    OrderStatus getStatus() const;
    String* saveData(int& length) const;

    void printSummary() const;
    void printDetailed() const;

    int getItemCount() const;
    int getId() const;
    int getProductIdAt(int index) const;
    int getQuantityAt(int index) const;
};
int getLatestOrderId();
