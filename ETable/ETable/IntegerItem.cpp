#include "IntegerItem.h"

IntegerItem::IntegerItem(const int number) : Item(ItemType::Integer) {
	this->number = number;
}

Item* IntegerItem::Clone() const {
	return new IntegerItem(*this);
}

void IntegerItem::Print(ostream& out) const {
	out << number;
};

void IntegerItem::Read(istream& in) {
	cin >> number;
};

float IntegerItem::getValue() const {
	return number;
}

size_t IntegerItem::getValueLen() const {
	return trunc(log10(abs(number))) + 1 + (number < 0); // number len + sign
}

void IntegerItem::Print(ostream& out, const size_t len) const {
	size_t newLen = len - getValueLen();
	out << number << setw(len - getValueLen());
};

string IntegerItem::getData() const {
	return to_string(number);
}
