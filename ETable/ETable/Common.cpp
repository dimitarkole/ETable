#include "Common.h"

bool isContainsNumbers(const string& str) {
	size_t strLen = str.length();
	if (str == "") return false;
	char digit = str[1];
	if (!(digit >= '0' && digit <= '9')) {
		return false;
	}

	for (size_t i = 1; i < strLen; i++)
	{
		digit = str[i];
		if (!(digit >= '0' && digit <= '9') && !(digit == '.' || digit == ','))
		{
			return false;
		}
	}

	return true;
}

bool isContainsOnlyNumbers(const string& str) {
	size_t strLen = str.length();
	if (str == "") return false;
	for (size_t i = 1; i < strLen; i++)
	{
		char digit = str[i];
		if (!(digit >= '0' && digit <= '9'))
		{
			return false;
		}
	}

	return true;
}

bool isNumberInteger(const string& str) {
	if (str.find('.') != string::npos || str.find(',') != string::npos) {
		return false;
	}

	return true;
}

bool isNumberFloat(const string& str) {
	int count = 0;
	for (size_t i = 0; (i = str.find('.', i)) != std::string::npos; i++) {
		count++;
		if (count > 1) return false;
	}

	for (size_t i = 0; (i = str.find(',', i)) != std::string::npos; i++) {
		count++;
		if (count > 1) return false;
	}

	return true;
}

int convertToNumber(const string& str) {
	int result = 0;
	size_t strLen = str.length();
	for (size_t i = 0; i < strLen; i++)
	{
		result = result * 10 + (str[i] - '0');
	}

	return result;
}

float convertToFloatNumber(const string& str) {
	int result = 0;
	float realNumber = 0;
	size_t strLen = str.length(), pointIndex = 0, count = 1;
	for (size_t i = 0; i < strLen; i++)
	{
		if (str[i] == '.' || str[i] == ',') {
			pointIndex = i;
			break;
		}

		result = result * 10 + (str[i] - '0');
	}

	for (size_t i = pointIndex + 1; i < strLen; i++)
	{
		realNumber = realNumber + (str[i] - '0') / (pow(10, count));
		count++;
	}

	return result + realNumber;
}