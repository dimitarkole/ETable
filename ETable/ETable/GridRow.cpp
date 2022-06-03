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
		//addItem(*other.items[i]);
	}
}

GridRow::GridRow(const size_t size) {
	items = new Item * [size];
	this->size = size;
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