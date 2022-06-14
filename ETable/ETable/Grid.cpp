#include "Grid.h"
#include "StringItem.h"
#include "IntegerItem.h"

void Grid::copyFrom(const Grid& other) {
	size = other.size;
	rows = new GridRow * [size];
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(*other.rows[i]);
	}
}

void Grid::free() {
	for (size_t i = 0; i < size; i++)
	{
		delete rows[i];
	}

	delete[] rows;
}

Grid::Grid(const size_t size) {
	this->size = size;
	rows = new GridRow*[size];
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(size);
	}
}

Grid::Grid(const Grid& other) {
	copyFrom(other);
}

Grid::~Grid() {
	free();
}

const Grid& Grid::operator=(const Grid& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

void Grid::setItem(const size_t row, const size_t col, const Item* item) {
	if (row >= size)
	{
		throw "Wrong row";
	}

	this->rows[row]->setItem(*item, col);
}

void Grid::Print(ostream& out) const {
	out << size << endl;
	for (size_t i = 0; i < size; i++)
	{
		rows[i]->Print(out);
		out << endl;
	}
}

const GridRow& Grid::operator[](const size_t index) const{
	if (index >= size)
	{
		throw "Wrong row";
	}

	return *rows[index];
}

GridRow& Grid::operator[](const size_t index) {
	if (index >= size)
	{
		throw "Wrong row";
	}

	return *rows[index];
}