#pragma once
#include "Item.h"
#include "GridRow.h"
#include<vector>
#include<iostream>
#include<ostream>
using namespace std;
class Grid
{
	ItemFactory itemFactory;
	GridRow** rows;
	size_t* maxLenInCol;
	size_t rowsCount;
	size_t colsCount;
	void copyFrom(const Grid& other);
	void free();
public:
	Grid(const size_t rows, const size_t cols);
	Grid(const Grid& other);
	Grid(const Grid&& other) = delete;
	~Grid();
	const Grid& operator=(const Grid& other);
	const Grid& operator=(const Grid&& other) = delete;
	const GridRow& operator[](const size_t index) const;
	GridRow& operator[](const size_t index);
	void setItem(const size_t row, const size_t col, const Item* item);
	void setItem(const size_t row, const size_t col, const string& data);
	void print(ostream& out) const;
	void printWithSpaces(ostream& out) const;
	void read(istream& in);
	float getItemValue(const size_t row, const size_t col) const;
	Item* calculateFormula(const string& formula) const;
};
