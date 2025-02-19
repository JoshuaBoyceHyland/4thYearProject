#pragma once
#include "Ship/Ship.h"
#include "World/Grid.h"
/// <summary>
/// Holds pieces of data that need to be transfered between scenes
/// </summary>
class GameData
{
	public:

		GameData(const GameData& other) = delete;

		static GameData* getInstance();

		Ship* m_player;

		Grid* m_currentMap;

		

		Ship* getPlayerShip();

	private:

		GameData();

		static GameData* instance;
		
};

