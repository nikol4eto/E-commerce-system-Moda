#pragma once
#ifndef STRING_H
#define STRING_H
class String
{
private:
    void copyDynamicMemory(const String& other);
    void free();
public:
    int length;
    char* data;
    String();
    String(const char* data);
    String(char* data, int length);
    String(const String& other);
    ~String();
    String& operator=(const String& other);
    String& operator=(char* other);
    bool operator==(const String& other) const;
    String& append(const char* other);
    String& append(char* other, int length);
    String& append(const String& other);
    bool compare(const String& other);

    //String & append(const String & other);
    char* getString() const;
};
String* stringToArray(const String& input, char delimiter, int& outSize);
String* stringToArray(const String& input, char delimiter);
bool tryConvertToInt(const char* str, int& result);
bool convertToString(int num, String& res);
int getLength(const char* data);
bool convertDoubleToString(double value, String& result, int precision = 2);
bool tryConvertToDouble(const String& input, double& result);

#endif