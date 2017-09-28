#include "RoomHandler.h"

RoomHandler::RoomHandler()
{
}


RoomHandler::~RoomHandler()
{
}

void RoomHandler::Update(map<string, bool> &boolMap, const vector<Connection> &connections, const reality &currentReality, location &currentLocation, const InputHandler &inputHandler)
{
	if (boolMap.at("validDirection"))
	{
		for (size_t i = 0; i < connections.size(); i++)
		{
			if (connections[i].m_CurrentRoom->name == currentLocation.name && !boolMap.at("ogp"))
			{
				if (connections[i].m_Direction == inputHandler.m_InputDirection)
				{
					if (currentReality == 0)
					{
						if (connections[i].m_IsOpen[0])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 1)
					{
						if (connections[i].m_IsOpen[1])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can't fit through that tiny crack. \nMaybe you can find a way to make it larger\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 2)
					{
						if (connections[i].m_IsOpen[2])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 3)
					{
						if (connections[i].m_IsOpen[3])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 4)
					{
						if (connections[i].m_IsOpen[4])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 5)
					{
						if (connections[i].m_IsOpen[5])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{

							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
					else if (currentReality == 6)
					{
						if (connections[i].m_IsOpen[6])
						{
							currentLocation = *connections[i].m_ConnectedRoom;
							boolMap.at("directionMatch") = true;
							break;
						}
						else
						{
							if (connections[i].m_CurrentRoom->name == "room02" && connections[i].m_Direction == WEST)
							{
								cout << "\nYou can not go that way.\n" << endl;
							}
							else
							{
								cout << "\nThe door seems to be locked or jammed. \n" << endl;
							}
							break;
						}
					}
				}
			}
			if (i == connections.size() - 1 && !boolMap.at("directionMatch"))
			{
				cout << "\nYou can not go that way.\n" << endl;
			}
		}
	}

	// ROOM TEXT
	// *********
	if (boolMap.at("directionMatch"))
	{
		if (boolMap.at("ogp"))
		{
			if (currentReality == ORANGE)
			{
				cout << "\nAll you see around you is a thick orange fog.\nThere is no floor or ceiling and there are no walls." << endl;
			}
			else if (currentReality == PURPLE)
			{
				cout << "\nAll you see around you is a thick purple fog.\nThere is no floor or ceiling and there are no walls." << endl;
			}
			else if (currentReality == GREEN)
			{
				cout << "\nAll you see around you is a thick green fog.\nThere is no floor or ceiling and there are no walls." << endl;
			}
		}

		else if (currentLocation.name == "corridor01")
		{
			cout << "\nYou are in a dark corridor. \nThere is darkness in front of you (NORTH) and behind you (SOUTH).\n" << endl;
		}

		else if (currentLocation.name == "corridor02")
		{
			cout << "\nYou are in a dark corridor. \nThere is darkness in front of you (NORTH) and behind you (SOUTH).\n";
			if (currentReality == NORMAL)
			{
				if (!boolMap.at("broomStick"))
				{
					cout << "There's something on the ground. \nIt looks like a broomstick. \n" << endl;
				}
			}
		}

		else if (currentLocation.name == "splitsing01")
		{
			cout << "\nYou are at a splitsing. \nThere is a dark hallway going SOUTH. \nThere are two doors, one to the NORTH_WEST and one to the NORTH_EAST.\n" << endl;
		}

		else if (currentLocation.name == "room01")
		{
			cout << "\nYou are in a dark room. \nThere is a dark hallway to the NORTH.\n";
			if (currentReality == NORMAL)
			{
				if (!boolMap.at("lightBulb"))
				{
					cout << "The room is empty with a dimly flickering light bulb hanging from the center of the ceiling. \n" << endl;
				}
				else if (!boolMap.at("keyNE"))
				{
					cout << "The room is empty with a broken light bulb hanging from the center of the ceiling. \nThere's shards of glas on the floor with a key in between them. \n" << endl;
				}
				else
				{
					cout << "The room is empty with a broken light bulb hanging from the center of the ceiling. \nThere's shards of glas on the floor. \n" << endl;
				}
			}
			else if (currentReality == BLUE)
			{
				if (!boolMap.at("dynamite"))
				{
					cout << "There's what appears to be a stick of dynamite on the ground here. \n" << endl;
				}
				else
				{
					cout << "The room is empty. \n" << endl;
				}
			}
		}

		else if (currentLocation.name == "room02")
		{
			//NW
			cout << "\nYou are in a dark room. \nThere is a door to the SOUTH, a door to the EAST and one to the NORTH.\n" << endl;
			if (currentReality == RED && !boolMap.at("wallExploded"))
			{
				cout << "The room is completely empty, but you can see that the wall to WEST has a crack in it.\n" << endl;
			}
			else if (currentReality == RED && boolMap.at("wallExploded"))
			{
				cout << "The room is completely empty. \nThere is now a Large hole in the wall to the WEST. \nIt leads to an other room.\n" << endl;
			}
		}

		else if (currentLocation.name == "room03")
		{
			//NE
			cout << "\nYou are in a dark room. \nThere is a door to the SOUTH and a door to the WEST.\n";
			if (currentReality == NORMAL && !boolMap.at("chest1Open"))
			{
				cout << "The room is completely empty except for a small wooden chest in the corner. \n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest1Open") && !boolMap.at("redMushroom"))
			{
				cout << "The room is completely empty except for the remains of the chest, which you brutally murdered, in the corner. \nThere's a mushroom in between the pieces.\n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest1Open") && boolMap.at("redMushroom"))
			{
				cout << "The room is completely empty except for the remains of the chest, which you brutally murdered, in the corner.\n" << endl;
			}
		}

		else if (currentLocation.name == "room04")
		{
			//N
			cout << "\nYou are in a dark room. \nThere is a door to the SOUTH.\n";
			if (currentReality == NORMAL && !boolMap.at("chest2Open"))
			{
				cout << "There's an other chest in this room, but this one seems to been made from steel. \nThere's no lock on it, but it is tied shut with a thick rope. \n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest2Open") && !boolMap.at("blueMushroom"))
			{
				cout << "There's an open steel chest in this room. \nThere's a mushroom inside of it with a blue shine to it. \n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest2Open") && boolMap.at("blueMushroom"))
			{
				cout << "There's an open steel chest in this room.\n" << endl;
			}
		}

		else if (currentLocation.name == "room05")
		{
			//W
			cout << "\nYou are in a dark room. \nThere is a hole in the wall to the EAST.\n";
			if (currentReality == NORMAL && !boolMap.at("chest3Open"))
			{
				cout << "There's a chest in this room. \nThis one is made from steel again, but this time it's painted blue. \nIt seems to be locked, but there's no keyhole. \n" << endl;
			}
			else if (currentReality == BLUE && !boolMap.at("chest3Open"))
			{
				cout << "There's a chest in this room. \nThis one is made from steel again but this time it's painted blue. \nIt seems to be unlocked in this reallity. \n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest3Open") && !boolMap.at("yellowMushroom"))
			{
				cout << "There's an open steel chest in this room. \nThere's a mushroom inside of it with a yellow shine to it. \n" << endl;
			}
			else if (currentReality == BLUE && boolMap.at("chest3Open") && !boolMap.at("yellowMushroom"))
			{
				cout << "There's an open steel chest in this room. \nIt's empty. \n" << endl;
			}
			else if (currentReality == NORMAL && boolMap.at("chest3Open") && boolMap.at("yellowMushroom") || currentReality == BLUE && boolMap.at("chest3Open") && boolMap.at("yellowMushroom"))
			{
				cout << "There's an open steel chest in this room.\n" << endl;
			}
		}
	}
	boolMap.at("directionMatch") = false;
}
