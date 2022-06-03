#include "Item.h"
Item::Item(const ItemType type) : type(type) {}
const ItemType Item::GetType() const {
	return type;
}