#pragma once

#define MAX_ORDER_ITEMS 100

enum OrderStatus {
    PENDING,
    SHIPPED,
    DELIVERED
};

class Order {
private:
    int productIds[MAX_ORDER_ITEMS];
    int quantities[MAX_ORDER_ITEMS];
    int itemCount;

    double totalPrice;
    int earnedPoints;

    OrderStatus status;

    char clientEGN[15]; // link to client who made the order

public:
    Order();
    void addItem(int productId, int quantity);
    void setClientEGN(const char* egn);
    const char* getClientEGN() const;

    void setTotal(double price);
    double getTotal() const;

    void setPoints(int points);
    int getPoints() const;

    void setStatus(OrderStatus s);
    OrderStatus getStatus() const;

    void printSummary() const;
    void printDetailed() const;

    int getItemCount() const;
    int getProductIdAt(int index) const;
    int getQuantityAt(int index) const;
};
