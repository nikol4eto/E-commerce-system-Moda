#include "Refund.h"

Refund::Refund()
{
	id = getLatestRefundId() + 1;
	orderId = -1;
	approved = 0;
}

Refund::Refund(int _orderId, bool _approved)
{
	id = getLatestRefundId() + 1;
	orderId = _orderId;
	approved = _approved;
}

String Refund::saveData()
{
	String item;
	String charId;
	convertToString(id, charId);
	item.append(charId);
	item.append(":");
	String charOrderId;
	convertToString(orderId, charOrderId);
	item.append(charOrderId);
	item.append(":");
	String charApproved;
	convertToString(approved, charApproved);
	item.append(charApproved);

	return item;
}

int getLatestRefundId()
{
	ifstream file(REFUNDS_FILE);
	if (!file.is_open()) {
		cout << "File failed to open!" << endl;
		return -1;
	}
	int tempId;
	file >> tempId;
	file.close();
	return tempId;
}
