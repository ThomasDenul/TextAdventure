#pragma once
#include "time.h"
#include "TextHandler.h"
#include "InputHandler.h"
#include "RoomHandler.h"
#include "Monster.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Start();
	void Update();
	map<string, bool> m_BoolMap;

private:
	TextHandler *m_TextHandler;
	vector<string> m_CommandVec;
	unordered_map<string, item> m_ItemMap;
	unordered_map<string, location> m_LocationMap;
	vector<Connection> m_ConnectionVec;
	InputHandler *m_InputHandler;
	RoomHandler *m_RoomHandler;
	Monster *m_Monster;
	Inventory *m_Inventroy;
	location* m_CurrentLocation;
	reality m_CurrentReality;
	string m_Input;
	char m_InChar[100];
};

