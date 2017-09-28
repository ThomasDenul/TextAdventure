#include "Connection.h"

Connection::Connection(const location *currentRoom, const location *connectedRoom, direction direction, bool isOpen)
	: m_CurrentRoom(currentRoom),
	m_ConnectedRoom(connectedRoom),
	m_Direction(direction)
{
	for (int i = 0; i <= 7; ++i)
	{
		m_IsOpen.push_back(isOpen);
	}
}

Connection::~Connection()
{
}
