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

float StringItem::getValue() const {
	return 0;
}

size_t StringItem::getValueLen() const {
	return data.length();
}

void StringItem::Print(ostream& out, const size_t len) const {
	out << data << setw(len - getValueLen());
};

string StringItem::getData() const {
	return data;
}
