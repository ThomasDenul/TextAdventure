#pragma once
#include "Helpers.h"

class Connection
{
public:
	Connection(const location *currentRoom, const location *connectedRoom, direction direction, bool isOpen);

	~Connection();

	const location *m_CurrentRoom;
	const location *m_ConnectedRoom;
	direction m_Direction;
	vector<bool> m_IsOpen;
};

