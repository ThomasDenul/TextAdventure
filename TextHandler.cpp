#include "TextHandler.h"

TextHandler::TextHandler(function<void(ifstream&, string)>f)
{
	m_Function = f;
}


TextHandler::~TextHandler()
{
}

void TextHandler::CommandFile()
{
	m_Function(m_Ifs, "Commands.txt");

	while (!m_Ifs.eof())
	{
		getline(m_Ifs, m_Str);
		m_Commands.push_back(m_Str);
	}
	m_Ifs.close();
}

void TextHandler::ItemFile()
{
	m_Function(m_Ifs, "Items.txt");

	while (!m_Ifs.eof())
	{
		getline(m_Ifs, m_Str);
		m_Item.name = m_Str;

		getline(m_Ifs, m_Str);
		m_Item.description = m_Str;

		m_ItemMap.insert(pair<string, item>(m_Item.name, m_Item));
	}
	m_Ifs.close();
}

void TextHandler::ConnectionFile()
{
	m_Function(m_Ifs, "Connections.txt");

	getline(m_Ifs, m_Str);
	m_Amount = stoi(m_Str);
	for (int i = 0; i < m_Amount; ++i)
	{
		getline(m_Ifs, m_Str);
		m_Location.name = m_Str;
		m_LocationMap.insert(pair<string, location>(m_Location.name, m_Location));
	}

	while (!m_Ifs.eof())
	{
		getline(m_Ifs, m_Str);
		m_Name1 = m_Str;
		getline(m_Ifs, m_Str);
		m_Amount = stoi(m_Str);
		for (int i = 0; i < m_Amount; ++i)
		{
			getline(m_Ifs, m_Str);
			m_Name2 = m_Str;
			getline(m_Ifs, m_Str);
			m_Direction = static_cast<direction>(stoi(m_Str));
			getline(m_Ifs, m_Str);
			if (stoi(m_Str) == 0)
				m_Bool = false;
			else
				m_Bool = true;
			m_Connection = new Connection(&m_LocationMap.at(m_Name1), &m_LocationMap.at(m_Name2), m_Direction, m_Bool);
			m_ConnectionVec.push_back(*m_Connection);
		}
	}
	m_Ifs.close();
}

void TextHandler::BooleanFile()
{
	m_Function(m_Ifs, "Booleans.txt");

	while (!m_Ifs.eof())
	{
		getline(m_Ifs, m_Str);
		m_Name1 = m_Str;
		getline(m_Ifs, m_Str);
		m_Amount = stoi(m_Str);
		m_Bool = bool(m_Amount);
		m_BoolMap.insert(pair<string, bool>(m_Name1, m_Bool));
	}

	m_Ifs.close();
}

void TextHandler::Save(const vector<Connection> &connectionVec, const map<string, bool> &boolMap, const reality &currentReality, const location &currentLocation, const reality &monsterReality, const location &monsterLocation, Inventory &inventory)
{
	m_Ofs.open("Save.txt");
	m_Ofs << inventory.Size() << "\n";
	for (auto const &item : inventory.GetMap())
		m_Ofs << item.second.name << "\n";
	m_Ofs << currentLocation.name << "\n";
	m_Ofs << int(currentReality) << "\n";
	m_Ofs << monsterLocation.name << "\n";
	m_Ofs << int(monsterReality) << "\n";

	for (auto const &boolean : boolMap)
	{
		m_Ofs << int(boolean.second) << "\n";
	}

	for (auto const &connection : connectionVec)
	{
		for (auto const &open : connection.m_IsOpen)
		{
			m_Ofs << int(open) << "\n";
		}
	}

	m_Ofs.close();
}

void TextHandler::Load(vector<Connection> &connectionVec, map<string, bool> &boolMap, reality &currentReality, location& currentLocation, reality& monsterReality, location& monsterLocation, Inventory& inventory)
{
	m_Ifs.open("Save.txt");

	if (m_Ifs.fail())
	{
		cout << "Error: No save file found" << endl;
		return;
	}

	getline(m_Ifs, m_Str);
	m_Amount = stoi(m_Str);
	inventory.Clear();
	for (int i = 0; i < m_Amount; ++i)
	{
		getline(m_Ifs, m_Str);
		inventory.Add(m_ItemMap.at(m_Str));
	}
	getline(m_Ifs, m_Str);
	currentLocation = m_LocationMap.at(m_Str);
	getline(m_Ifs, m_Str);
	m_Amount = stoi(m_Str);
	currentReality = reality(m_Amount);
	getline(m_Ifs, m_Str);
	monsterLocation = m_LocationMap.at(m_Str);
	getline(m_Ifs, m_Str);
	m_Amount = stoi(m_Str);
	monsterReality = reality(m_Amount);

	for (auto &boolean : boolMap)
	{
		getline(m_Ifs, m_Str);
		m_Amount = stoi(m_Str);
		boolean.second = bool(m_Amount);
	}

	for (auto &connection : connectionVec)
	{
		for (auto &open : connection.m_IsOpen)
		{
			getline(m_Ifs, m_Str);
			m_Amount = stoi(m_Str);
			open = bool(m_Amount);
		}
	}

	m_Ifs.close();
}
