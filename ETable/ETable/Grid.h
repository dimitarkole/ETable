#pragma once
#include "Item.h"
#include "GridRow.h"
#include<vector>
#include<iostream>
#include<ostream>
using namespace std;
class Grid
{
	GridRow** rows;
	size_t size;
	void copyFrom(const Grid& other);
	void free();
public:
	Grid(const size_t size);
	Grid(const Grid& other);
	~Grid();
	const Grid& operator=(const Grid& other);
	const GridRow& operator[](const size_t index) const;
	GridRow& operator[](const size_t index);
	void setItem(const size_t row, const size_t col, const Item* item);
	void Print(ostream& out) const;
};

