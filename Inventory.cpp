#include "Inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::Add(const item &iItem)
{
	inventoryMap.insert(pair<string, item>(iItem.name, iItem));
}

void Inventory::Remove(const item &item)
{
	inventoryMap.erase(item.name);
}

void Inventory::Clear()
{
	inventoryMap.clear();
}

int Inventory::Size()
{
	return inventoryMap.size();
}