#include "InputHandler.h"
#include <algorithm>
#include <string>

InputHandler::InputHandler()
{
	m_Match = false;
}

InputHandler::~InputHandler()
{
}

void InputHandler::Input(const string *input, vector<string> commands, map<string, bool> &boolMap, Inventory &inventory, vector<Connection> &connections, unordered_map<string, item> &items, const unordered_map<string, location> &locations, reality &currentReality, location &currentLocation, TextHandler &textHandler, Monster &monster)
{
	//Convert to lower case without spaces
	m_InputHolder = *input;

	for_each(begin(m_InputHolder), end(m_InputHolder),
		[&](char c)
	{
		if (c != ' ' && c != '_' && c != '-')
			m_Input.push_back(tolower(c));
	}
	);

	//Compare and set command
	if (commands.size() > 0)
	{
		for (int i = 0; i < int(commands.size()); ++i)
		{
			m_CurCommand = commands[i];
			if (m_CurCommand == m_Input)
			{
				m_Match = true;
			}
			if (m_CurCommand[0] == '*' && m_Match)
			{
				for_each(begin(m_CurCommand), end(m_CurCommand),
					[&](char c)
				{
					if (c != '*')
						m_SIndex.push_back(c);
				}
				);
				m_Index = stoi(m_SIndex);

				m_Command = static_cast<command>(m_Index);
				break;
			}
		}
		if (!m_Match)
			m_Command = NONE;
		else
			m_Match = false;
		m_SIndex.clear();
	}
	else
	{
		cout << "InputHandler: Commands vector incorrect size" << endl;
		return;
	}

	//Input

	switch (m_Command)
	{
	case(MATCH) :
		if (boolMap.at("monsterInRoom"))
		{
			boolMap.at("gameOver") = true;
			boolMap.at("matchLit") = true;
			boolMap.at("validDirection") = false;
			boolMap.at("validInput") = true;
		}
		else
		{
			cout << endl << "You can now see." << endl;
			boolMap.at("matchLit") = true;
			boolMap.at("validDirection") = false;
			boolMap.at("validInput") = true;
			boolMap.at("directionMatch") = true;
		}
				break;

	case(INVENTORY) :
		cout << endl;
		cout << "----------------------------\n";
		for (auto &invItem : inventory.GetMap())
		{
			cout << invItem.second.name << endl;
		}
		cout << "----------------------------\n";
		cout << endl;
		boolMap.at("validDirection") = false;
		boolMap.at("validInput") = true;
		break;

	case(LOAD) :
		textHandler.Load(connections, boolMap, currentReality, currentLocation, monster.m_MonsterReality, monster.m_MonsterLocation, inventory);
		cout << "Loading game... \n";
		boolMap.at("validDirection") = false;
		boolMap.at("validInput") = true;
		break;

	case(SAVE) :
		textHandler.Save(connections, boolMap, currentReality, currentLocation, monster.m_MonsterReality, monster.m_MonsterLocation, inventory);
		cout << "Saving game... \n";
		boolMap.at("validDirection") = false;
		boolMap.at("validInput") = true;
		break;
	default:
		break;
	}


	if (boolMap.at("matchLit"))
	{
		switch (m_Command)
		{
		case (LOOKAROUND) :
			boolMap.at("validDirection") = false;
			boolMap.at("validInput") = true;
			boolMap.at("directionMatch") = true;
			break;

		case(INORTH) :
			m_InputDirection = NORTH;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case (INORTHEAST) :
			m_InputDirection = NORTH_EAST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case (IEAST) :
			m_InputDirection = EAST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case (ISOUTHEAST) :
			m_InputDirection = SOUTH_EAST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case (ISOUTH) :
			m_InputDirection = SOUTH;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case(ISOUTHWEST) :
			m_InputDirection = SOUTH_WEST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case(IWEST) :
			m_InputDirection = WEST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case(INORTHWEST) :
			m_InputDirection = NORTH_WEST;
			boolMap.at("validDirection") = true;
			boolMap.at("validInput") = true;
			break;

		case(EATMUSHROOM) :
			cout << endl << "Which one?\n" << endl;
			boolMap.at("mushroom") = true;
			boolMap.at("validDirection") = false;
			boolMap.at("validInput") = true;
			break;

		case(EATNORMAL) :
			if (currentReality == NORMAL && boolMap.at("normalMushroom"))
			{
				cout << endl << "You take a bite from the mushroom. \nIt doesn't really taste like anything...\n" << endl;
				currentReality = NORMAL;
			}
			else if (currentReality == RED && boolMap.at("normalMushroom") || currentReality == YELLOW && boolMap.at("normalMushroom") || currentReality == BLUE && boolMap.at("normalMushroom") || currentReality == PURPLE && boolMap.at("normalMushroom") || currentReality == GREEN && boolMap.at("normalMushroom") || currentReality == ORANGE && boolMap.at("normalMushroom"))
			{
				cout << "\nYou take a bite from the mushroom. \nIt doesn't really taste like anything...\nYou feel reality changing around you. \nEverything around you turns back to normal.\n " << endl;
				currentReality = NORMAL;
				boolMap.at("ogp") = false;
			}
			else if (!boolMap.at("normalMushroom"))
			{
				cout << endl << "It's gone...\nThe normal mushroom is gone!\nWhere did it go?\n" << endl;
			}
			boolMap.at("mushroom") = false;
			boolMap.at("validDirection") = false;
			boolMap.at("validInput") = true;
			break;

		case(INORMAL) :
			if (boolMap.at("mushroom"))
			{
				if (currentReality == NORMAL && boolMap.at("normalMushroom"))
				{
					cout << endl << "You take a bite from the mushroom. \nIt doesn't really taste like anything...\n" << endl;
					currentReality = NORMAL;
				}
				else if (currentReality == RED && boolMap.at("normalMushroom") || currentReality == YELLOW && boolMap.at("normalMushroom") || currentReality == BLUE && boolMap.at("normalMushroom") || currentReality == PURPLE && boolMap.at("normalMushroom") || currentReality == GREEN && boolMap.at("normalMushroom") || currentReality == ORANGE && boolMap.at("normalMushroom"))
				{
					cout << "\nYou take a bite from the mushroom. \nIt doesn't really taste like anything...\nYou feel reality changing around you. \nEverything around you turns back to normal.\n " << endl;
					currentReality = NORMAL;
					boolMap.at("ogp") = false;
				}
				else if (!boolMap.at("normalMushroom"))
				{
					cout << endl << "It's gone...\nThe normal mushroom is gone!\nWhere did it go?\n" << endl;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}

					  break;

		case(EATRED) :
			if (boolMap.at("redMushroom"))
			{
				if (!boolMap.at("monster"))
					boolMap.at("monster") = true;

				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == NORTH || connections[i].m_CurrentRoom->name == "room04" && connections[i].m_Direction == SOUTH)
					{
						connections[i].m_IsOpen[0] = true;
					}
				}

				if (currentReality == RED)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes like shit...\n" << endl;
					currentReality = RED;
				}
				else if (currentReality == NORMAL || currentReality == PURPLE || currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color red.\n " << endl;
					currentReality = RED;
					boolMap.at("ogp") = false;
				}
				else if (currentReality == YELLOW)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color orange.\n " << endl;
					currentReality = ORANGE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == BLUE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color purple.\n " << endl;
					currentReality = PURPLE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == GREEN)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
					 break;

		case(IRED) :
			if (boolMap.at("mushroom") && boolMap.at("redMushroom"))
			{
				if (!boolMap.at("monster"))
					boolMap.at("monster") = true;

				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom == &locations.at("room02") && connections[i].m_Direction == NORTH || connections[i].m_CurrentRoom == &locations.at("room04") && connections[i].m_Direction == SOUTH)
					{
						connections[i].m_IsOpen[0] = true;
					}
				}

				if (currentReality == RED)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes like shit...\n" << endl;
					currentReality = RED;
				}
				else if (currentReality == NORMAL || currentReality == PURPLE || currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color red.\n " << endl;
					currentReality = RED;
					boolMap.at("ogp") = false;
				}
				else if (currentReality == YELLOW)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color orange.\n " << endl;
					currentReality = ORANGE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == BLUE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns a slight color purple.\n " << endl;
					currentReality = PURPLE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == GREEN)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like shit...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
				   break;

		case(EATBLUE) :
			if (boolMap.at("blueMushroom"))
			{
				if (currentReality == BLUE)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes sweet...\n" << endl;
					currentReality = BLUE;
				}
				else if (currentReality == NORMAL || currentReality == PURPLE || currentReality == GREEN)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color blue.\n " << endl;
					currentReality = BLUE;
					boolMap.at("ogp") = false;
				}
				else if (currentReality == YELLOW)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color green.\n " << endl;
					currentReality = GREEN;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == RED)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color purple.\n " << endl;
					currentReality = PURPLE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
					  break;

		case(IBLUE) :
			if (boolMap.at("mushroom") && boolMap.at("blueMushroom"))
			{
				if (currentReality == BLUE)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes sweet...\n" << endl;
					currentReality = BLUE;
				}
				else if (currentReality == NORMAL || currentReality == PURPLE || currentReality == GREEN)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color blue.\n " << endl;
					currentReality = BLUE;
					boolMap.at("ogp") = false;
				}
				else if (currentReality == YELLOW)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color green.\n " << endl;
					currentReality = GREEN;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == RED)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns a slight color purple.\n " << endl;
					currentReality = PURPLE;
					boolMap.at("ogp") = true;
				}
				else if (currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes sweet...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
					break;

		case(EATYELLOW) :
			if (boolMap.at("yellowMushroom"))
			{
				if (currentReality == YELLOW)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\n" << endl;
					currentReality = YELLOW;
				}
				else if (currentReality == NORMAL || currentReality == GREEN || currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color yellow.\nYou feel like something's missing...\n " << endl;
					currentReality = YELLOW;
					boolMap.at("ogp") = false;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == BLUE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color green.\nYou feel like something's missing...\n " << endl;
					currentReality = GREEN;
					boolMap.at("ogp") = true;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == RED)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color orange.\nYou feel like something's missing...\n " << endl;
					currentReality = ORANGE;
					boolMap.at("ogp") = true;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == PURPLE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
						break;

		case(IYELLOW) :
			if (boolMap.at("mushroom") && boolMap.at("yellowMushroom"))
			{
				if (currentReality == YELLOW)
				{
					cout << endl << "You take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\n" << endl;
					currentReality = YELLOW;
				}
				else if (currentReality == NORMAL || currentReality == GREEN || currentReality == ORANGE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color yellow.\nYou feel like something's missing...\n " << endl;
					currentReality = YELLOW;
					boolMap.at("ogp") = false;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == BLUE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color green.\nYou feel like something's missing...\n " << endl;
					currentReality = GREEN;
					boolMap.at("ogp") = true;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == RED)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns a slight color orange.\nYou feel like something's missing...\n " << endl;
					currentReality = ORANGE;
					boolMap.at("ogp") = true;

					if (boolMap.at("normalMushroom"))
					{
						inventory.Remove(items.at("normal mushroom"));
					}

					boolMap.at("normalMushroom") = false;
				}
				else if (currentReality == PURPLE)
				{
					cout << "\nYou take a bite from the mushroom. \nIt tastes like it was intended to be eaten 10 years ago...\nYou feel reality changing around you. \nEverything around you turns white...\n " << endl;
					currentReality = WHITE;
				}
				boolMap.at("mushroom") = false;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
					  break;

		case(BROOMSTICK) :
			if (currentReality == NORMAL && currentLocation.name == "corridor02" && !boolMap.at("broomStick"))
			{
				cout << "\nIt feels light and strong. Perfect for hitting something. \n" << endl;
				inventory.Add(items.at("broomstick"));
				boolMap.at("broomStick") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
						 break;

		case(SMASHLIGHT) :
			if (currentReality == NORMAL && currentLocation.name == "room01" && boolMap.at("broomStick") && !boolMap.at("lightBulb"))
			{
				cout << "\nYou smash the light with the broomstick. \nThe glass shards go flying everywhere. \nIn between the shards you see a key falling out of the broken light onto the ground. \n" << endl;
				boolMap.at("lightBulb") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
						 break;

		case(KEY) :
			if (currentReality == NORMAL && currentLocation.name == "room01" && boolMap.at("lightBulb") && !boolMap.at("keyNE"))
			{
				cout << "\nYou pick up the key. It might open one of the locked doors. \n" << endl;
				inventory.Add(items.at("blackened key"));
				boolMap.at("keyNE") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
				  break;

		case(GLASS) :
			if (currentReality == NORMAL && currentLocation.name == "room01" && boolMap.at("lightBulb") && !boolMap.at("glassShard"))
			{
				cout << "\nYou pick up one of the shards of glass.\n" << endl;
				inventory.Add(items.at("shard of glass"));
				boolMap.at("glassShard") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room01" && boolMap.at("lightBulb") && boolMap.at("glassShard"))
			{
				cout << "\nWhy would you want an other one?\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;

		case(UNLOCK) :
			if (currentReality == NORMAL && currentLocation.name == "splitsing01" && boolMap.at("keyNE"))
			{
				cout << "\nThe blackened key unlocks the door to the North-East. \n" << endl;
				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == "splitsing01" || connections[i].m_CurrentRoom->name == "room03")
					{
						if (connections[i].m_Direction == NORTH_EAST || connections[i].m_Direction == SOUTH)
						{
							connections[i].m_IsOpen[0] = true;
						}
					}
				}

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == RED && currentLocation.name == "room03" && boolMap.at("keyNE"))
			{
				cout << "\nThe blackened key unlocks the door to the West. \n" << endl;
				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == "room03" && connections[i].m_Direction == WEST || connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == EAST)
					{
						connections[i].m_IsOpen[1] = true;
					}
				}

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;

		case(OPENCHEST) :
			if (currentReality == NORMAL && currentLocation.name == "room03" && !boolMap.at("chest1Open"))
			{
				cout << "\nIt won't open.\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room04" && !boolMap.at("chest2Open"))
			{
				cout << "\nIt's tied shut.\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room05" && !boolMap.at("chest3Open"))
			{
				cout << "\nIt won't open.\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == BLUE && currentLocation.name == "room05" && !boolMap.at("chest3Open"))
			{
				cout << "\nYou open the chest, but there's nothing inside.\n" << endl;
				boolMap.at("chest3Open") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;

		case(SMASHCHEST) :
			if (currentReality == NORMAL && currentLocation.name == "room03" && !boolMap.at("chest1Open"))
			{
				cout << "\nYou beat the living crap out of this poor little chest with your broomstick.\nBetween the pieces of broken chest you see a mushroom that looks like the one you found in your pocket before, but with a slight red shine to it.\n" << endl;
				boolMap.at("chest1Open") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room04" && !boolMap.at("chest2Open"))
			{
				cout << "\nIt seems to be made out of steel.\nNo violent chest murder this time\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room05" && !boolMap.at("chest3Open"))
			{
				cout << "\nIt seems to be made out of steel.\nAgain, no violent chest murder for you.\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == BLUE && currentLocation.name == "room05" && !boolMap.at("chest3Open"))
			{
				cout << "\nIt seems to be made out of steel.\nAgain, no violent chest murder for you.\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;

		case(PICKUPMUSHROOM) :
			if (currentReality == NORMAL && currentLocation.name == "room03" && boolMap.at("chest1Open") && !boolMap.at("redMushroom"))
			{
				cout << "\nYou pick up the mushroom. It has a red shine to it and it smells funny.\n" << endl;
				inventory.Add(items.at("red mushroom"));
				boolMap.at("redMushroom") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room04" && boolMap.at("chest2Open") && !boolMap.at("blueMushroom"))
			{
				cout << "\nYou pick up the mushroom. It has a blue shine to it and it smells rather nice.\n" << endl;
				inventory.Add(items.at("blue mushrooms"));
				boolMap.at("blueMushroom") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room05" && boolMap.at("chest3Open") && !boolMap.at("yellowMushroom"))
			{
				cout << "\nYou pick up the mushroom. It has a yellow shine to it and it smells old.\n" << endl;
				inventory.Add(items.at("yellow mushroom"));
				boolMap.at("yellowMushroom") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;
		case(CUTROPE) :
			if (currentReality == NORMAL && currentLocation.name == "room04" && !boolMap.at("chest2Open") && boolMap.at("glassShard"))
			{
				cout << "\nYou cut the rope with the shard of glass and open the chest. There's a mushroom inside with a blue shine to it\n" << endl;
				boolMap.at("chest2Open") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else if (currentReality == NORMAL && currentLocation.name == "room04" && !boolMap.at("chest2Open") && !boolMap.at("glassShard"))
			{
				cout << "\nYou have nothing to cut the rope with\n" << endl;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
			break;

		case(DYNAMITE) :
			if (currentReality == BLUE && currentLocation.name == "room01" && !boolMap.at("dynamite"))
			{
				cout << "\nYou pick up the stick of dynamite. \nIt's to small to give a big bang, but it might do some damage to something that's already weakened.\n" << endl;
				inventory.Add(items.at("stick of dynamite"));
				boolMap.at("dynamite") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
					   break;

		case(EXPLODE) :
			if (currentReality == RED && currentLocation.name == "room02" && !boolMap.at("wallExploded"))
			{
				cout << "\nYou put the stick of dynamite in the crack in the wall and light the fuse with your match.\nYou take a few steps back and watch as the explosive blows a hole in the wall.\n" << endl;

				for (size_t i = 0; i < connections.size(); i++)
				{
					if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST || connections[i].m_CurrentRoom->name == "room05" && connections[i].m_Direction == EAST)
					{
						connections[i].m_IsOpen[1] = true;
					}
				}

				inventory.Remove(items.at("stick of dynamite"));

				boolMap.at("wallExploded") = true;

				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
			else
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = false;
			}
					  break;
		default:
			break;
		}
	}
	else
	{
		cout << endl << "It's to dark to see or do anything.\n" << endl;
		boolMap.at("validInput") = true;
	}


		for (auto &invItem : inventory.GetMap())
		{
			m_InventoryNameHolder = invItem.second.name;
			m_InventoryName.clear();

			for_each(begin(m_InventoryNameHolder), end(m_InventoryNameHolder),
				[&](char c)
			{
				if (c != ' ')
					m_InventoryName.push_back(tolower(c));
			}
			);

			if (m_Input == "lookat" + m_InventoryName || m_Input == "look" + m_InventoryName)
			{
				cout << "\n" << invItem.second.description << "\n" << endl;
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}

			else if (m_Input == "eat" + m_InventoryName)
			{
				boolMap.at("validDirection") = false;
				boolMap.at("validInput") = true;
			}
		}

		if (!boolMap.at("validInput"))
		{
			cout << "\nI don't know what you're trying to do here.\n" << endl;
			boolMap.at("validDirection") = false;
		}

		m_Input.clear();
		boolMap.at("validInput") = false;
}