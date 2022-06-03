#pragma once
#include "Item.h"
class GridRow
{	
	Item** items;
	size_t size;
	void free();
	void copyFrom(const GridRow& other);
	//void changeItem();
	void deleteItems();
public:
	GridRow(size_t size);
	GridRow(const GridRow& other);
	GridRow(const GridRow&& other) = delete;
	const GridRow& operator=(const GridRow& other);
	const GridRow& operator=(const GridRow&& other) = delete;
	~GridRow();
};
