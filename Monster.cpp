#include "Monster.h"

Monster::Monster(const unordered_map<string, location> locationMap)
{
	m_MonsterReality = RED;
	m_MonsterLocation = locationMap.at("room01");
	m_Directions = { "NORTH", "NORTH_EAST", "EAST", "SOUTH_EAST", "SOUTH", "SOUTH_WEST", "WEST", "NORTH_WEST" };
}


Monster::~Monster()
{
}

void Monster::Update(map<string, bool> &boolMap, const vector<Connection> &connections, const reality &currentReality, const location &currentLocation)
{
	if (boolMap.at("monster"))
		{
			if (m_MonsterReality != currentReality)
			{
				m_MonsterReality = static_cast<reality>(rand() % 4);
			}
			else
			{
				m_MonsterDirection = static_cast<direction>(rand() % 8);
				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == m_MonsterLocation.name && connections[i].m_Direction == m_MonsterDirection)
					{
						if (connections[i].m_IsOpen[m_MonsterReality])
						{
							m_MonsterLocation = *connections[i].m_ConnectedRoom;
						}
					}
				}
			}
			if (currentReality == m_MonsterReality)
			{
				cout << "You sence a presence in this reality.\n\n";
				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == currentLocation.name && connections[i].m_ConnectedRoom->name == m_MonsterLocation.name)
					{
						cout << "The presence seems to be directly to the " << m_Directions[connections[i].m_Direction] << " of you.\n\n";
					}
				}
				if (currentLocation.name == m_MonsterLocation.name)
				{
					boolMap.at("monsterInRoom") = true;
					boolMap.at("matchLit") = false;
					cout << "Your match dies out and you're in total darkness again.\nYou sence the presence is right there with you\n" << endl;
				}
				else
					boolMap.at("monsterInRoom") = false;
			}
		}
}
