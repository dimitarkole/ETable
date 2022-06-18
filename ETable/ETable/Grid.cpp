#include "Grid.h"

void Grid::copyFrom(const Grid& other) {
	size = other.size;
	rows = new GridRow * [size];
	maxLenInCol = new size_t[size];
	for (size_t i = 0; i < size; i++)
	{
		maxLenInCol[i] = 0;
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
		delete[] maxLenInCol;
	}
}

Grid::Grid(const size_t size) {
	this->size = size;
	rows = new GridRow*[size];
	maxLenInCol = new size_t[size];
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(size);
		maxLenInCol[i] = 0;
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
	if (row == size)
	{
		throw "Wrong row";
	}
	
	if (item->GetType() == ItemType::Formula)
	{
		Item* formulaResult = calculateWithFormula(item->getData());
		// formulaResult->Print(cout);
		cout << endl;
		setItem(row, col, formulaResult);
		this->rows[row - 1]->setItem(*item, col);
		size_t dataLen = formulaResult->getValueLen();
		if (maxLenInCol[col - 1] < dataLen)
		{
			maxLenInCol[col - 1] = dataLen;
		}
		delete formulaResult;
	}
	else {

		this->rows[row - 1]->setItem(*item, col);
		size_t dataLen = item->getValueLen();
		if (maxLenInCol[col - 1] < dataLen)
		{
			maxLenInCol[col - 1] = dataLen;
		}
	}

}

void Grid::print(ostream& out) const {
	out << size << endl;
	for (size_t i = 0; i < size; i++)
	{
		rows[i]->Print(out);
		out << endl;
	}
}

void Grid::printWithSpaces(ostream& out) const {
	out << size << endl;
	for (size_t i = 0; i < size; i++)
	{
		rows[i]->Print(out, maxLenInCol);
	}
	out << endl;
}

void Grid::read(istream& in) {
	char newLine = '\n';
	in.get(newLine);
	for (size_t i = 0; i < size; i++)
	{
		rows[i] = new GridRow(size);
		this->size = size;
		for (size_t j = 0; j < size; j++)
		{
			string itemData;
			getline(in, itemData, '|');
			if (itemData != "")
			{
				GridRow* row = rows[i];
				Item* newItem = itemFactory.createItem(itemData);
				rows[i]->setItem(newItem, j);
				size_t dataLen = newItem ->getValueLen();
				if (maxLenInCol[j] < dataLen)
				{
					maxLenInCol[j] = dataLen;
				}
			}
			else 
			{
				Item* gridItem = rows[i]->operator[](j);
				gridItem = nullptr;
			}
		}

		/*rows[i]->read(in);
		size_t dataLen = rows[i]->getValueLen();
		if (maxLenInCol[col - 1] < dataLen)
		{
			maxLenInCol[col - 1] = dataLen;
		}
		in.get(newLine);*/
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
	if (row == 0 || row > size)
	{
		throw "Wrong row";
	}

	return rows[row-1]->getItemValue(col);
}