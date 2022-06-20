#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool isContainsOnlyNumbers(const string& str);
bool isNumberInteger(const string& str);
bool isNumberFloat(const string& str);
int convertToNumber(const string& str);
bool isContainsNumbers(const string& str);
float convertToFloatNumber(const string& str);
size_t getNumberFromFormula(const string& formula, size_t& startIndex);