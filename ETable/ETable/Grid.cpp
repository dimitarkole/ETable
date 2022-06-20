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

void Grid::setItem(const size_t row, const size_t col, const string& data) {
	if (row == size && row == 0)
	{
		throw "Wrong row";
	}

	Item* item = itemFactory.createItem(data);
	if (item->GetType() == ItemType::Formula)
	{
		Item* formulaResult = calculateFormula(item->getData());
		formulaResult->Print(cout);
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
	delete item;
}

void Grid::setItem(const size_t row, const size_t col, const Item* item) {
	if (row == size && row == 0)
	{
		throw "Wrong row";
	}
	
	if (item->GetType() == ItemType::Formula)
	{
		Item* formulaResult = calculateFormula(item->getData());
		formulaResult->Print(cout);
		setItem(row, col, formulaResult);
		this->rows[row - 1]->setItem(*formulaResult, col);
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

Item* Grid::calculateFormula(const string& formula) const
{
	size_t formulaLen = formula.length();
	int sum = 0;
	char sign = '+';
	for (size_t i = 0; i < formulaLen; i++)
	{
		if (formula[i] == '+' || formula[i] == '-')
		{
			sign = formula[i];
		}

		if ((formula[i] >= '0' && formula[i] <= '9') || formula[i] == 'R')
		{
			int value = 1;
			char signV = '*';
			do {
				while (formula[i] == '*' || formula[i] == '/' || formula[i] == ' ') {
					i++;
				}

				size_t number = 1;
				if (formula[i] != 'R')
				{
					number = getNumberFromFormula(formula, i);
				}
				else if (formula[i] == 'R')
				{
					i++;
					size_t row = getNumberFromFormula(formula, i);
					i++;
					size_t col = getNumberFromFormula(formula, i);
					number = this->getItemValue(row, col);
				}

				signV = formulaLen > i + 1 && formula[i + 1] == '/' ? '/' : '*';
				if (signV == '/')
				{
					if (number == 0) {
						throw "Err: / 0 is unccurrect!";
					}
					value /= number;
				}
				else value *= number;
			} while (formulaLen > i + 1 && (formula[i + 1] == '*' || formula[i + 1] == '/'));

			if (sign == '+') sum += value;
			else sum -= value;
		}
	}

	return new IntegerItem(sum);
}

float Grid::getItemValue(const size_t row, const size_t col) const {
	if (row == 0 || row > size)
	{
		throw "Wrong row";
	}

	return rows[row-1]->getItemValue(col);
}