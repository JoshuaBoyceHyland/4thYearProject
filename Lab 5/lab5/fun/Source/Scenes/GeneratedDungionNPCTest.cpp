#include "Scenes/GeneratedDungionNPCTest.h"

GeneratedDungionNPCTestScene::GeneratedDungionNPCTestScene(sf::RenderWindow& t_window) : 
Scene( t_window), 
m_camera(m_window)
{
	m_dungeon = m_dungeonGenerator.generate();
	m_dungeon->m_grid->setForGamePlay();
	m_player = new BasePlayer(m_dungeon->m_grid);

	Cell* randCell = m_dungeon->m_grid->getRandomTraverableCell();
	m_player->setPosition(randCell->getNode()->getPosition());


	std::vector<GameObject*> upcastedNpcs;
	for (int i = 0; i < 10; i++)
	{

		
		Cell* randCell = m_dungeon->m_grid->getRandomTraverableCell();
		m_npc.push_back(new NPC(m_dungeon->m_grid, m_player, randCell->m_body.getPosition()));
	
		upcastedNpcs.push_back(m_npc[i]);
	}

	m_minimap = new MiniMap(m_window,2,m_player, upcastedNpcs, { m_dungeon->m_grid });

}

void GeneratedDungionNPCTestScene::update(sf::Time t_deltaTime)
{


	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->update(t_deltaTime.asMilliseconds());
	}

	m_camera.follow(m_player->getPosition());
	m_camera.update();
	m_player->update(t_deltaTime.asMilliseconds());
	m_minimap->update();
}

void GeneratedDungionNPCTestScene::render()
{
	m_window.clear();
	m_window.setView(m_camera.getView());
	m_dungeon->m_grid->draw(m_window);
	for (int i = 0; i < m_npc.size(); i++)
	{
		m_npc[i]->draw(m_window);
	}
	m_player->draw(m_window);

	m_minimap->drawBackground();
	m_minimap->drawContents();
	m_minimap->drawBorder();

	m_window.display();
}

void GeneratedDungionNPCTestScene::processKeys(sf::Event t_event)
{

}

void GeneratedDungionNPCTestScene::processMousePress(sf::Event t_event)
{
	Cell* cell = m_dungeon->m_grid->cellSelection(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_player->fireWeapon();
	}


	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		if (prev)
		{
			prev->setColor(sf::Color::White);
		}
		cell->setColor(sf::Color::Red);
		prev = cell;
	}
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}

}

void GeneratedDungionNPCTestScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_npc.push_back(new NPC(m_dungeon->m_grid, m_player, m_dungeon->m_grid->cellSelection(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)))->getNode()->getPosition()));
	}
}

void GeneratedDungionNPCTestScene::processMouseMove(sf::Event t_event)
{
	m_window.setView(m_camera.getView());
	m_player->rotateWeapon(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	//m_camera.move();
}

void GeneratedDungionNPCTestScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
}
