#pragma once
#include "String.h"

using namespace std;
void String::copyDynamicMemory(const String& other)
{
    this->length = other.length;
    this->data = new char[length + 1];

    for (int i = 0; i < length; i++) {
        this->data[i] = other.data[i];
    }

    data[length] = '\0';
}

void String::free()
{
    delete[] this->data;
}

String::String()
{
    data = nullptr;
    length = 0;
}

int getLength(const char* data) {
    int i = 0;
    while (data[i] != '\0') {
        i++;
    }
    i++;
    return i;
}

String::String(const char* _data)
{
    length = getLength(data);
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[i] = _data[i];
    }
}

String::String(char* _data, int _length)
{
    int k = 0;
    while (_data[k] != '\0') {
        k++;
    }
    data = new char[k];
    for (int i = 0; i < k; i++) {
        this->data[i] = _data[i];
    }
    length = _length;
}

String::String(const String& other)
{
    copyDynamicMemory(other);
}

String::~String()
{
    free();
}

String& String::operator=(const String& other)
{
    if (this != &other) {
        free();
        copyDynamicMemory(other);
    }
    return *this;
}

String& String::operator=(char* other)
{
    if (data != other) {
        free();
        copyDynamicMemory(String(other, getLength(other)));
    }
    return *this;
}

bool String::operator==(const String& other) const
{
    if (length != other.length) return false;
    for (int i = 0; i < length; i++)
        if (data[i] != other.data[i])
            return false;
    
    return true;
}

String& String::append(char* other, int length)
{
    char* temp = new char[length + this->length - 1];
    int i = 0;
    while (i < this->length) {
        if (this->data[i] == '\0') {
            break;
        }
        temp[i] = this->data[i];
        i++;
    }
    for (int a = 0; a < length; a++) {
        temp[i] = other[a];
        i++;
    }

    free();
    this->length += length - 1;
    this->data = temp;

    return *this;
}

bool String::compare(const String& other)
{
    if (length != other.length)
        return false;

    for (int i = 0; i < other.length; i++) {
        if (data[i] != other.data[i])
            return false;
    }
    return true;
}

String& String::append(const char* other)
{
    int length = getLength(other);
    this->append((char*)other, length);
    return *this;
}

String& String::append(const String& other)
{
    this->append(other.data, other.length);
    return *this;
}

char* String::getString() const
{
    return this->data;
}

String* stringToArray(const String& input, char delimiter, int& outSize)
{
    int segments = 1;
    for (int i = 0; i < input.length; i++) {
        if (input.data[i] == delimiter)
            segments++;
    }

    String* res = new String[segments];
    outSize = segments;

    int currentWord = 0;
    int currentLength = 0;

    for (int i = 0; i <= input.length; i++) {
        if (input.data[i] == delimiter || input.data[i] == '\0') {
            char* word = new char[currentLength + 1];
            for (int j = 0; j < currentLength; j++) {
                word[j] = input.data[i - currentLength + j];
            }
            word[currentLength] = '\0';

            res[currentWord] = word;
            delete[] word;

            currentWord++;
            currentLength = 0;
        }
        else {
            currentLength++;
        }
    }

    return res;
}

String* stringToArray(const String& input, char delimiter)
{
    int segments = 1;
    for (int i = 0; i < input.length; i++) {
        if (input.data[i] == delimiter)
            segments++;
    }

    String* res = new String[segments];

    int currentWord = 0;
    int currentLength = 0;

    for (int i = 0; i <= input.length; i++) {
        if (input.data[i] == delimiter || input.data[i] == '\0') {
            char* word = new char[currentLength + 1];
            for (int j = 0; j < currentLength; j++) {
                word[j] = input.data[i - currentLength + j];
            }
            word[currentLength] = '\0';

            res[currentWord] = word;
            delete[] word;

            currentWord++;
            currentLength = 0;
        }
        else {
            currentLength++;
        }
    }

    return res;
}

bool tryConvertToInt(const char* str, int& result) {
    if (str == nullptr) return false;

    result = 0;
    bool isNegative = false;
    int i = 0;

    if (str[i] == '-') {
        isNegative = true;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }

    if (str[i] == '\0') return false;

    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (isNegative) result = -result;
    return true;
}

bool convertToString(int num, String& res) {
    // Handle 0 explicitly
    if (num == 0) {
        char* str = new char[2];
        str[0] = '0';
        str[1] = '\0';
        res = str;
        delete[] str;
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
    char* str = new char[totalLength + 1];
    str[totalLength] = '\0';

    for (int i = totalLength - 1; i >= (isNegative ? 1 : 0); i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }

    if (isNegative) {
        str[0] = '-';
    }

    res = str;
    delete[] str;
    return true;
}

bool convertDoubleToString(double value, String& result, int precision) {
    char buffer[64];  // enough space for typical doubles
    int i = 0;

    // Handle negative
    if (value < 0) {
        buffer[i++] = '-';
        value = -value;
    }

    // Integer part
    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;

    // Convert integer part to string (reverse it first)
    char temp[32];
    int tempIndex = 0;

    if (intPart == 0)
        temp[tempIndex++] = '0';
    else {
        while (intPart > 0) {
            temp[tempIndex++] = '0' + (intPart % 10);
            intPart /= 10;
        }
    }

    // Copy reversed integer part into buffer
    for (int j = tempIndex - 1; j >= 0; --j)
        buffer[i++] = temp[j];

    // Decimal point
    buffer[i++] = '.';

    // Convert fractional part
    for (int p = 0; p < precision; ++p) {
        fracPart *= 10;
        int digit = static_cast<int>(fracPart);
        buffer[i++] = '0' + digit;
        fracPart -= digit;
    }

    buffer[i] = '\0';  // null-terminate

    result = String(buffer);
    return true;
}

bool tryConvertToDouble(const String& input, double& result) {
    const char* str = input.data;
    if (!str || *str == '\0') return false;

    result = 0.0;
    bool isNegative = false;
    bool seenDot = false;
    double fraction = 0.0;
    double divisor = 10.0;

    int i = 0;

    if (str[i] == '-') {
        isNegative = true;
        i++;
    }

    bool valid = false;

    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            if (seenDot) {
                fraction += digit / divisor;
                divisor *= 10.0;
            }
            else {
                result = result * 10.0 + digit;
            }
            valid = true;
        }
        else if (str[i] == '.') {
            if (seenDot) return false; // multiple dots
            seenDot = true;
        }
        else {
            return false; // invalid character
        }
    }

    if (isNegative) result = -result;
    result += isNegative ? -fraction : fraction;
    return valid;
}
