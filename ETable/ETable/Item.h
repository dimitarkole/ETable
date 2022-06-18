#pragma once
#include<iostream>
#include<fstream>
#include <iomanip>
using namespace std;

enum ItemType {
	Integer = 1,
	Float = 2,
	String = 3,
	Formula = 4,
};

class Item
{
	ItemType type;
public:
	Item(const ItemType type);
	//virtual Item* operator= (const Item* other) = 0;
	virtual Item* Clone() const = 0;
	virtual ~Item() = default;
	const ItemType GetType() const;
	virtual void Print(ostream& out) const = 0;
	virtual void Print(ostream& out, const size_t len) const = 0;
	virtual void Read(istream& in) = 0;
	virtual float getValue() const = 0;
	virtual string getData() const = 0;
	virtual size_t getValueLen() const = 0;
};
