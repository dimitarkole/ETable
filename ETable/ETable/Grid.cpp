#include "Grid.h"

void Grid::copyFrom(const Grid& other) {
	size = other.size;
	rows = new GridRow * [size];
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(*other.rows[i]);
	}
}

void Grid::free() {
	if (this != nullptr) {
		for (size_t i = 0; i < size; i++)
		{
			delete rows[i];
		}

		delete[] rows;
	}
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

void Grid::print(ostream& out) const {
	out << size << endl;
	for (size_t i = 0; i < size; i++)
	{
		rows[i]->Print(out);
		out << endl;
	}
}

void Grid::read(istream& in) {
	char newLine = '\n';
	in.get(newLine);
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(size);
		rows[i]->read(in);
		in.get(newLine);
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

Item* Grid::calculateWithFormula(const string& formula) const {
	float result = 0;
	size_t formulaLen = formula.length(), index = 1, row = 0, col = 0;
	bool hasCell;
	int number = 1;
	float value = 1;
	char sign = '*';
	while(index < formulaLen)
	{
		//if (formula[index] == ' ' || formula[index] != '+' || formula[index] != '-') index++;
		hasCell = false;
		while (index < formulaLen && formula[index] != '+' && formula[index] != '-')
		{
			if (formula[index] == '*' || formula[index] == '/') sign = formula[index];
			if (formula[index] == ' ' && formula[index + 1] != 'R')
			{
				number = 0;
				index++;
				while (index < formulaLen && formula[index] != 'R' && formula[index] != ' ')
				{
					number += formula[index] - '0';
					index++;
				}
			}

			if (formula[index] == 'R')
			{
				hasCell = true;
				index++;
				row = 0;
				while (index < formulaLen && formula[index] != 'C')
				{
					row += formula[index] - '0';
					index++;
				}
			}

			if (formula[index] == 'C')
			{
				index++;
				col = 0;
				while (index < formulaLen && formula[index] != ' ')
				{
					col += formula[index] - '0';
					index++;
				}
			}

			if (formula[index] == '+' || formula[index] == '-')
			{
				row--;
				col--;
				if (hasCell) {
					if (sign == '*')
					{
						value *= number * this->rows[row]->getItemValue(col);
					}
					else value /= number * this->rows[row]->getItemValue(col);
				}
				else value *= number;
				number = 1;
			}
			index++;
		}

		if (index >= formulaLen)
		{
			row--;
			col--;
			if (hasCell) {
				if (sign == '*')
				{
					value *= number * this->rows[row]->getItemValue(col);
				}
				else value /= number * this->rows[row]->getItemValue(col);
			}
			else value *= number;
			number = 1;
		}


		result += value;
	}

	return new FloatItem(result);
}

float Grid::getItemValue(const size_t row, const size_t col) const {
	return rows[row]->getItemValue(col);
}