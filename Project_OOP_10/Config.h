#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
using namespace std;
void replaceLineInFile(const String filename, int targetLine, const String newLine);
void deleteLineFromFile(const String filename, int targetLine);
