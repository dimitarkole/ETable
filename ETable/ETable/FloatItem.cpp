#include "FloatItem.h"

FloatItem::FloatItem(const float number) : Item(ItemType::Float) {
	this->number = number;
}

Item* FloatItem::Clone() const {
	return new FloatItem(*this);
}

void FloatItem::Print(ostream& out) const {
	out << number;
};

void FloatItem::Read(istream& in) {
	cin >> number;
};
