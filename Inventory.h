#pragma once
#include "Helpers.h"
#include <map>
#include <unordered_map>

class Inventory
{
public:
	Inventory();
	~Inventory();
	void Add(const item &iItem);
	void Remove(const item &iItem);
	void Clear();
	int Size();
	unordered_map<string, item> GetMap() { return inventoryMap; }
private:
	unordered_map<string, item> inventoryMap;
};

