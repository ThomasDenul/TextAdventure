#pragma once
#include "TextHandler.h"
#include "Inventory.h"
#include "Connection.h"
#include "Monster.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	void Input(const string *input, vector<string> commands, map<string, bool> &boolMap, Inventory &inventory, vector<Connection> &connections, unordered_map<string, item> &items, const unordered_map<string, location> &locations, reality &currentReality, location &currentLocation, TextHandler &textHandler, Monster &monster);

	direction m_InputDirection;

private:

	enum command
	{
		MATCH,
		INVENTORY,
		LOOKAROUND,
		INORTH,
		INORTHEAST,
		IEAST,
		ISOUTHEAST,
		ISOUTH,
		ISOUTHWEST,
		IWEST,
		INORTHWEST,
		EATMUSHROOM,
		INORMAL,
		EATNORMAL,
		IRED,
		EATRED,
		IBLUE,
		EATBLUE,
		IYELLOW,
		EATYELLOW,
		BROOMSTICK,
		SMASHLIGHT,
		KEY,
		GLASS,
		UNLOCK,
		OPENCHEST,
		SMASHCHEST,
		PICKUPMUSHROOM,
		CUTROPE,
		DYNAMITE,
		EXPLODE,
		LOAD,
		SAVE,
		NONE
	};

	command m_Command;
	string m_InputHolder;
	string m_Input;
	string m_CurCommand;
	string m_SIndex;
	int m_Index;
	bool m_Match;
	string m_InventoryNameHolder;
	string m_InventoryName;
};
