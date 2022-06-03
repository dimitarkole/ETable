#pragma once
#include "Item.h"
#include "GridRow.h"
#include<vector>
using namespace std;
class Grid
{
	vector<GridRow> rows;
	
	void addRow(const GridRow& row);
public:
	Grid() = default;
};

