#pragma once
#include "Item.h"
#include<iostream>
#include<string>
using namespace std;
class StringItem : public Item
{
	string data;
public:
	StringItem(const string data = "");
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
	float getValue() const override;
	StringItem& operator=(const StringItem& other) = default;
};
