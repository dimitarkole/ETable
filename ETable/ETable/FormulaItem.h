#pragma once
#include "Item.h"
#include<iostream>
#include<string>
#include <iomanip>
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
	void Print(ostream& out, const size_t len);
	FormulaItem& operator=(const FormulaItem& other) = default;
	size_t getValueLen() const override;
	void Print(ostream& out, const size_t len) const;
	string getData() const override;
};
