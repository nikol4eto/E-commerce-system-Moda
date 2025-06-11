#pragma once
#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

int const CODE_LENGTH = 5;
int const EGN_LENGTH = 11;

class Check {
private:
	int id;
	String code;
	double amount;
	String clientEgn;
	bool used;
public:
	Check(const String _code, const String _clientEgn, double _amount, bool _isUsed);

	void redeem(const String _code, const String _clientEgn);
	bool isUsed();
	bool userAuthorized(const String _clientEgn);
	String saveData() const;

	int getId();
};

bool alreadyExists(const String _code);
int getLatestCheckId();