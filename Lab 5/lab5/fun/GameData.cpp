#include "GameData.h"
GameData* GameData::instance = nullptr;

GameData* GameData::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameData;
    }
    return instance;
}

Ship* GameData::getPlayerShip()
{
    return m_player;
}
