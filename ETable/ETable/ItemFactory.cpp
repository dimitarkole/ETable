#include "ItemFactory.h"
#include "Common.h"
const size_t ITEM_MAX_LEN = 1024;

ItemType ItemFactory::getItemType(const string& item) const {
	if (item[0] == '=') {
		return ItemType::Formula;
	}

	if (isContainsNumbers(item))
	{
		if (isContainsOnlyNumbers(item)) {
			return ItemType::Integer;
		}

		return ItemType::Float;
	}

	return ItemType::String;
}

Item* ItemFactory::createItem(const string& item) const {
	ItemType type = getItemType(item);
	switch (type)
	{
	case ItemType::Integer:
		return new IntegerItem(convertToNumber(item));
	case ItemType::Float:
		return new FloatItem(convertToFloatNumber(item));
	case ItemType::String:
		return new StringItem(item);
	}
}

void ItemFactory::writeItem(ostream& out, const Item* item) const{
	item->Print(out);
	out << '|';
}

Item* ItemFactory::readItem(istream& in) const
{
	string item;
	getline(in, item, '|');
	return createItem(item);
}
