#pragma once
#include "Item.h"
#include "Common.h"
#include "IntegerItem.h"
#include "FloatItem.h"
#include "StringItem.h"
#include <iostream>
#include <string>
using namespace std;

class ItemFactory
{
public:
	ItemType getItemType(const string& item) const;
	Item* createItem(const string& itemData) const;
	Item* readItem(istream& in) const;
	void writeItem(ostream& out, const Item* item) const;
};