#include "Check.h"
#include "Constants.h"


Check::Check(const String _code, const String _clientEgn, double _amount, bool _isUsed)
{
    id = getLatestCheckId() + 1;
    code = _code;
    clientEgn = _clientEgn;
    amount = _amount;
    used = _isUsed;
}

void Check::redeem(const String _code, const String _clientEgn)
{
    if (used) {
        cout << "Code already used!" << endl;
        return;
    }
    if (alreadyExists(_code) || userAuthorized(_clientEgn)) {
        used = true;
        cout << "Code successfully used!" << endl;
        return;
    }
    cout << "Code or information about the cheque is incorrect!" << endl;
    return;
}

bool Check::isUsed()
{
    return used;
}

bool Check::userAuthorized(const String _clientEgn) {
    return clientEgn.compare(_clientEgn);
}

String Check::saveData() const
{
    String item = String();
    String charId;
    convertToString(id, charId);
    item.append(charId);
    item.append(":");
    item.append(code);
    item.append(":");
    String charAmount;
    convertDoubleToString(amount, charAmount);
    item.append(charAmount);
    item.append(":");
    String charUsed;
    convertToString(used, charUsed);
    item.append(charUsed);

    return item;
}

int Check::getId()
{
    return id;
}

int getLatestCheckId() {
    ifstream file("data/cheques.txt");
    if (!file.is_open()) {
        cout << "Failed to open file!";
        return false;
    }
    int tempId = 0;
    file >> tempId;
    file.close();
    return tempId;
}

bool alreadyExists(const String _code)
{
    ifstream file(CHEQUES_FILE);
    if (!file.is_open()) {
        cout << "File failed to open!" << endl;
        return false;
    }
    int latestId = 0;
    int length = 0;

    file >> latestId >> length;

    for (int i = 0; i < length; i++) {
        String in;
        file >> in.data;
        String* arr = stringToArray(in, ':');
        if (arr[1].compare(_code)) {
            return true;
        }
    }
    return false;
}
