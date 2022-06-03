#pragma once
#include "Item.h"
#include<iostream>
#include<string>
using namespace std;
class NumberItem : Item
{
	int number;
public:
	NumberItem(const int number = 0);
	Item* Clone() const override;
	void Print(ostream& out) const override;
	void Read(istream& in) override;
};
