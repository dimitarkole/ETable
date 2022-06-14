#pragma once
#include "Item.h"
#include<iostream>
#include<string>
using namespace std;
class FloatItem : public Item
{
	float number;
public:
	FloatItem(const float number = 0);
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
	FloatItem& operator=(const FloatItem& other) = default;
};

