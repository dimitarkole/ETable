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

void FloatItem::Print(ostream& out, const size_t len) const {
	out << number << setw(len - getValueLen());
};

void FloatItem::Read(istream& in) {
	cin >> number;
};

float FloatItem::getValue() const {
	return number;
}

size_t FloatItem::getValueLen() const {
	int copyNumber = abs(number);
	size_t pow = 1;
	//int count = 0;
	while (round(copyNumber * pow) != number * pow) {
		pow *= 10;
		//count++;
	}

	return trunc(log10(abs(copyNumber))) + 1 + (number < 0); // number len + sign
}

string FloatItem::getData() const {
	return to_string(number);
}