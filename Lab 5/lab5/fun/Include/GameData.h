#pragma once
#include "DungeonGeneration/Dungeon.h"
#include "Ship/Ship.h"
#include "World/Grid.h"
#include "BasePlayer.h"

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
/// <summary>
/// Holds pieces of data that need to be transfered between scenes
/// </summary>
class GameData
{
	public:

		GameData(const GameData& other) = delete;

		static GameData* getInstance();

		BasePlayer* m_player;

		Ship* m_playerShip;

		Grid* m_currentMap;

		Ship* getPlayerShip();
		
		Dungeon* m_currentDungeon;

		std::vector<Dungeon*> m_dungeons;
	private:

		GameData();

		static GameData* instance;
		
};

