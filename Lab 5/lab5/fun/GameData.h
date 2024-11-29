#pragma once
#include "Ship.h"

/// <summary>
/// Holds pieces of data that need to be transfered between scenes
/// </summary>
class GameData
{


	public:

		GameData(const GameData& other) = delete;

		static GameData* getInstance();

		Ship* m_player;

		Ship* getPlayerShip();
	private:

		GameData() = default;

		static GameData* instance;
		
		

};

