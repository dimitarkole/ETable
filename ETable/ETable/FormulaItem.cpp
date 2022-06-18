#include "FormulaItem.h"
const int MAX_FORMULA_SIZE = 1024;

FormulaItem::FormulaItem(const string data) : Item(ItemType::Formula) {
	this->data = data;
}

Item* FormulaItem::Clone() const {
	return new FormulaItem(*this);
}

void FormulaItem::Print(ostream& out) const {
	out << data;
};

void FormulaItem::Print(ostream& out, const size_t len) {
	out << data;
}

void FormulaItem::Read(istream& in) {
	getline(cin, data, '|');
};

float FormulaItem::getValue() const {
	return 0;
}

size_t FormulaItem::getValueLen() const {
	return 0;
}

void FormulaItem::Print(ostream& out, const size_t len) const {
	out << data << setw(len - getValueLen());
};

string FormulaItem::getData() const {
	return data;
}
