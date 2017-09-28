#include "GameManager.h"

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Start()
{
	srand(time(NULL));

	auto openFile = [](ifstream& iStream, string fileName)
	{
		iStream.open(fileName);

		if (iStream.fail())
		{
			cout << "Error Opening File: " << fileName << endl;
		}
	};

	m_TextHandler = new TextHandler(openFile);

	m_TextHandler->CommandFile();
	m_CommandVec = *m_TextHandler->GetCommands();
	m_TextHandler->ItemFile();
	m_ItemMap = *m_TextHandler->GetItems();
	m_TextHandler->ConnectionFile();
	m_LocationMap = *m_TextHandler->GetLocations();
	m_ConnectionVec = *m_TextHandler->GetConnections();
	m_TextHandler->BooleanFile();
	m_BoolMap = *m_TextHandler->GetBools();

	m_InputHandler = new InputHandler;
	m_RoomHandler = new RoomHandler;
	m_Monster = new Monster(m_LocationMap);


	// INVENTORY
	// *********
	m_Inventroy = new Inventory;
	m_Inventroy->Add(m_ItemMap.at("normal mushroom"));
	m_Inventroy->Add(m_ItemMap.at("box of matches"));

	m_CurrentLocation = &m_LocationMap.at("corridor01");
	m_CurrentReality = NORMAL;

	cout << "You wake up in total darkness. \nAll you see is blackness.\n" << endl;
}

void GameManager::Update()
{
	cout << "\n";

	// GAME OVER
	// *********
	if (m_BoolMap.at("gameOver"))
	{
		cout << "\nYou feel yourself getting consumed by darkness.\n\nGAME OVER\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		m_BoolMap.at("quit") = true;
		return;
	}

	// END
	// ***
	if (m_CurrentReality == WHITE)
	{
		cout << "\nEverything is white...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nEverything is bright...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nYou feel no pain...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nNo los...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nNo gain...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nYou feel at ease...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nFinally...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		cout << "\nYou can rest in peace...\n";
		cin.getline(m_InChar, sizeof(m_InChar));
		m_BoolMap.at("quit") = true;
		return;
	}

	// MATCH
	// *****
	int match = rand() % 6;
	if (match == 0 && m_BoolMap.at("matchLit"))
	{
		m_BoolMap.at("matchLit") = false;
		cout << "Your match dies out and you're in total darkness again.\n" << endl;
	}

	// MONSTER
	// *******
	m_Monster->Update(m_BoolMap, m_ConnectionVec, m_CurrentReality, *m_CurrentLocation);

	// INPUT
	// *****
	std::cin.getline(m_InChar, sizeof(m_InChar));
	m_Input = m_InChar;

	m_InputHandler->Input(&m_Input, m_CommandVec, m_BoolMap, *m_Inventroy, m_ConnectionVec, m_ItemMap, m_LocationMap, m_CurrentReality, *m_CurrentLocation, *m_TextHandler, *m_Monster);


	// ROOMS
	// *****
	m_RoomHandler->Update(m_BoolMap, m_ConnectionVec, m_CurrentReality, *m_CurrentLocation, *m_InputHandler);


	cout << "---------------------------------------------\n";

	// ChECK QUIT
	// **********
	if (m_Input == "quit" || m_Input == "exit" || m_Input == "stop")
	{
		m_BoolMap.at("quit") = true;
	}
}
