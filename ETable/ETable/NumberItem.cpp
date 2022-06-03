#include "NumberItem.h"

NumberItem::NumberItem(const int number) : Item(ItemType::Integer) {
	this->number = number;
}

Item* NumberItem::Clone() const {
	return new NumberItem(*this);
}

void NumberItem::Print(ostream& out) const {
	out << number;
};

void NumberItem::Read(istream& in) {
	cin >> number;
};