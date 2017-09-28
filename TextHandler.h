#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Helpers.h"
#include <map>
#include <unordered_map>
#include "Connection.h"
#include "Inventory.h"
#include <functional>

using namespace std;

class TextHandler
{
public:
	TextHandler(function<void(ifstream&, string)>f);
	~TextHandler();
	void CommandFile();
	void ItemFile();
	void ConnectionFile();
	void BooleanFile();
	const vector<string>* GetCommands() { return &m_Commands; }
	const unordered_map<string, item>* GetItems() { return &m_ItemMap; }
	const unordered_map<string, location>* GetLocations() { return &m_LocationMap; }
	const vector<Connection>* GetConnections() { return &m_ConnectionVec; }
	const map<string, bool>* GetBools() { return &m_BoolMap; }
	void Save(const vector<Connection> &connectionVec, const map<string, bool> &boolMap, const reality &currentReality, const location &currentLocation, const reality &monsterReality, const location &monsterLocation, Inventory &inventory);
	void Load(vector<Connection> &connectionVec, map<string, bool> &boolMap, reality &currentReality, location &currentLocation, reality &monsterReality, location &monsterLocation, Inventory &inventory);

private:
	string m_Str;
	string m_Name1;
	string m_Name2;
	ifstream m_Ifs;
	ofstream m_Ofs;
	int m_Amount;
	item m_Item;
	location m_Location;
	direction m_Direction;
	bool m_Bool;
	Connection *m_Connection;

	vector<string> m_Commands;
	unordered_map<string, item> m_ItemMap;
	unordered_map<string, location> m_LocationMap;
	map<string, bool> m_BoolMap;
	vector<Connection> m_ConnectionVec;

	function<void(ifstream&, string)> m_Function;
};

