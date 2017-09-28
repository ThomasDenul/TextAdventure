#include <iostream>
#include <fstream>
#include "Connection.h"
#include "time.h"
#include <algorithm>
#include <map>
#include "TextHandler.h"
#include "RoomHandler.h"
#include "Monster.h"
#include "GameManager.h"

using namespace std;

void main()
{
	GameManager *gameManager = new GameManager;

	gameManager->Start();

	// GAME LOOP
	// *********
	while (!gameManager->m_BoolMap.at("quit"))
	{
		gameManager->Update();
	}
}