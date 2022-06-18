#pragma once
#include "Item.h"
#include<iostream>
#include<cmath>
#include<string>
#include <iomanip>
using namespace std;
class FloatItem : public Item
{
	float number;
public:
	FloatItem(const float number = 0);
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
	void Print(ostream& out, const size_t len) const;
	FloatItem& operator=(const FloatItem& other) = default;
	float getValue() const override;
	size_t getValueLen() const override;
	string getData() const override;
};
