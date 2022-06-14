#pragma once
#include "Item.h"
#include<iostream>
#include<string>
using namespace std;
class FormulaItem : public Item
{
	string data;
public:
	FormulaItem(const string data = "");
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
	float getValue() const override;
	FormulaItem& operator=(const FormulaItem& other) = default;
};
