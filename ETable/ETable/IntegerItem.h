#pragma once
#include "Item.h"
#include<iostream>
#include<cmath>
#include<string>
#include <iomanip>
using namespace std;
class IntegerItem : public Item
{
	int number;
public:
	IntegerItem(const int number = 0);
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
	float getValue() const override;
	IntegerItem& operator=(const IntegerItem& other) = default;
	size_t getValueLen() const override;
	void Print(ostream& out, const size_t len) const;
	string getData() const override;
};
