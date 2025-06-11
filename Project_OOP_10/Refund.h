#pragma once
#include "Order.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
using namespace std;
class Refund
{
private:
	int id;
	int orderId;
	bool approved;
public:
	Refund();
	Refund(int _orderId, bool _approved);

	String saveData();
};

int getLatestRefundId();

