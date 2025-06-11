#include "Utils.h"

bool str_equal(const String a, const String b) {
    int i = 0;
    while (a.data[i] != '\0' && b.data[i] != '\0') {
        if (a.data[i] != b.data[i]) return false;
        i++;
    }
    return a.data[i] == b.data[i];
}

bool starts_with(const String str, const String prefix) {
    int i = 0;
    while (prefix.data[i] != '\0') {
        if (str.data[i] != prefix.data[i]) return false;
        i++;
    }
    return true;
}

bool convertToString(int num, String res) {
    // Handle 0 explicitly
    if (num == 0) {
        String str = new char[2];
        str.data[0] = '0';
        str.data[1] = '\0';
        res = str;
        return true;
    }

    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    // Count digits
    int temp = num;
    int length = 0;
    while (temp > 0) {
        temp /= 10;
        length++;
    }

    int totalLength = length + (isNegative ? 1 : 0);
    String str = new char[totalLength + 1];
    str.data[totalLength] = '\0';

    for (int i = totalLength - 1; i >= (isNegative ? 1 : 0); i--) {
        str.data[i] = (num % 10) + '0';
        num /= 10;
    }

    if (isNegative) {
        str.data[0] = '-';
    }

    res = str;
    return true;
}