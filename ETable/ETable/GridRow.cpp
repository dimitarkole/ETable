#include "GridRow.h"

void GridRow::free() {
	deleteItems();
}

void GridRow::deleteItems() {
	for (size_t i = 0; i < size; i++)
	{
		delete items[i];
	}

	delete[] items;
}

void GridRow::copyFrom(const GridRow& other) {
	for (size_t i = 0; i < other.size; i++)
	{
		if (other.items[i] != nullptr)
		{
			this->items[i] = other.items[i];
		}
	}
}

GridRow::GridRow(const size_t size) {
	items = new Item * [size];
	this->size = size;
	for (size_t i = 0; i < size; i++)
	{
		items[i] = nullptr;
	}
}

GridRow::GridRow(const GridRow& other) {
	copyFrom(other);
}

const GridRow& GridRow::operator=(const GridRow& other) {
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}

GridRow::~GridRow() {
	free();
}

void GridRow::Print(ostream& out) const {
	for (size_t i = 0; i < size; i++)
	{
		if (items[i] != nullptr)
		{
			(*items[i]).Print(out);
		}

		out << "|";
	}
}

void  GridRow::Print(ostream& out, const size_t* lens) const {
	for (size_t i = 0; i < size; i++)
	{
		if (items[i] != nullptr)
		{
			(*items[i]).Print(out, lens[i]);
		}
		else {
			out<<setw(lens[i]);
		}

		out << "|";
	}
}


void GridRow::setItem(const Item& item, const size_t col) {
	if (col >= size) throw "Wrong col";
	delete this->items[col - 1];
	this->items[col -1] = item.Clone();
}

void GridRow::setItem(const Item* item, const size_t col) {
	if (col >= size) throw "Wrong col";
	delete this->items[col];
	this->items[col] = item->Clone();
}

const Item* GridRow::operator[](const size_t index) const {
	if (index >= size)
	{
		throw "Wrong row";
	}

	return items[index];
}

Item* GridRow::operator[](const size_t index) {
	if (index > size)
	{
		throw "Wrong row";
	}

	return items[index];
}

void GridRow::read(istream& in) {
	items = new Item * [size];
	this->size = size;
	for (size_t i = 0; i < size; i++)
	{
		string itemData;
		getline(in, itemData, '|');
		if (itemData != "")
		{
			items[i] = itemFactory.createItem(itemData);
		}
		else items[i] = nullptr;
	}
}

float GridRow::getItemValue(const size_t col) const {
	if (col == 0 || col > size)
	{
		throw "Wrong row";
	}

	return this->items[col - 1]->getValue();
}
