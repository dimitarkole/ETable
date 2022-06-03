#include "StringItem.h"

const int MAX_DATA_SIZE = 1024;

StringItem::StringItem(const string data) : Item(ItemType::String) {
	this->data = data;
}

Item* StringItem::Clone() const {
	return new StringItem(*this);
}

void StringItem::Print(ostream& out) const {
	out << data;
};

void StringItem::Read(istream& in) {
	getline(cin, data, '|');
};