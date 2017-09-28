#pragma once
#include <iostream>
#include "Helpers.h"
#include <unordered_map>
#include "Connection.h"
#include <map>

class Monster
{
public:
	Monster(const unordered_map<string, location> locationMap);
	~Monster();
	void Update(map<string, bool> &boolMap, const vector<Connection> &connections, const reality &currentReality, const location &currentLocation);
	location m_MonsterLocation;
	reality m_MonsterReality;

private:
	direction m_MonsterDirection;
	vector<string> m_Directions;
};

