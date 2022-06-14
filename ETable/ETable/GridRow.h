#pragma once
#include "Item.h"
class GridRow
{	
	Item** items;
	size_t size;
	void free();
	void copyFrom(const GridRow& other);
	void deleteItems();
public:
	GridRow(size_t size);
	GridRow(const GridRow& other);
	GridRow(const GridRow&& other) = delete;
	const GridRow& operator=(const GridRow& other);
	const GridRow& operator=(const GridRow&& other) = delete;
	~GridRow();

	void setItem(const Item& item, const size_t index);
	void Print(ostream& out) const;
	const Item* operator[](const size_t index) const;
	Item* operator[](const size_t index);
	// virtual void Read(istream& in) = 0;
};
