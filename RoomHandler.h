#pragma once
#include "Helpers.h"
#include <iostream>
#include "Connection.h"
#include "InputHandler.h"

class RoomHandler
{
public:
	RoomHandler();
	~RoomHandler();
	void Update(map<string, bool> &boolMap, const vector<Connection> &connections, const reality &currentReality, location &currentLocation, const InputHandler &inputHandler);
};

