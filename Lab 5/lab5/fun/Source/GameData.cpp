#include "GameData.h"
GameData* GameData::instance = nullptr;

GameData::GameData()
{
    m_currentMap = new Grid(50, 50, 100, 100, { 0,0 });
}

GameData* GameData::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameData();
    }
    return instance;
}

Ship* GameData::getPlayerShip()
{
    return m_playerShip;
}
