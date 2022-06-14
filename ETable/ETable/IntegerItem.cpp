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
