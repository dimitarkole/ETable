#pragma once
#include "Item.h"
#include<iostream>
#include<string>
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
};
