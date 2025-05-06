#include "Scenes/EnemyBaseScene.h"

EnemyBaseScene::EnemyBaseScene(sf::RenderWindow& t_window, std::function<void(SceneType)> t_sceneChangeFunction) :
	Scene(t_window),
	m_camera(m_window), 
	m_sceneChangeFunction(t_sceneChangeFunction)
{
	GameData* gameData = GameData::getInstance();
	m_dungeon = gameData->m_currentDungeon;
	m_player = gameData->m_player;
	m_ship = gameData->m_playerShip;
	m_player->setMap(m_dungeon->m_grid);
	std::vector<GameObject*> upcastedNpcs;

	m_ship->update(0.0f);
	for (int i = 0; i < 1; i++)
	{

		Cell* randCell = m_dungeon->m_grid->getRandomTraverableCell();
		m_npc.push_back(new NPC(m_dungeon->m_grid, m_player, randCell->m_body.getPosition()));

		upcastedNpcs.push_back(m_npc[i]);
	}
	upcastedNpcs.push_back(m_ship);
	m_minimap = new MiniMap(m_window, 2, m_player, upcastedNpcs, { m_dungeon->m_grid });
}

void EnemyBaseScene::update(sf::Time t_deltaTime)
{
	//for (int i = 0; i < m_npc.size(); i++)
	//{
	//	m_npc[i]->update(t_deltaTime.asMilliseconds());
	//}

	m_camera.follow(m_player->getPosition());
	m_camera.update();
	m_player->update(t_deltaTime.asMilliseconds());
	m_minimap->update();
}

void EnemyBaseScene::render()
{
	m_window.clear();
	m_window.setView(m_camera.getView());
	m_dungeon->m_grid->draw(m_window);
	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->draw(m_window);
	}
	m_player->draw(m_window);
	m_ship->draw(m_window);
	m_minimap->drawBackground();
	m_minimap->drawContents();
	m_minimap->drawBorder();

	m_window.display();
}

void EnemyBaseScene::processKeys(sf::Event t_event)
{
	
}

void EnemyBaseScene::processMousePress(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_player->fireWeapon();
	}
}

void EnemyBaseScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_npc.push_back(new NPC(m_dungeon->m_grid, m_player, m_dungeon->m_grid->cellSelection(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)))->getNode()->getPosition()));
	}
}

void EnemyBaseScene::processMouseMove(sf::Event t_event)
{
	m_window.setView(m_camera.getView());
	m_player->rotateWeapon(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
}

void EnemyBaseScene::processMouseWheel(sf::Event t_event)
{

	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
