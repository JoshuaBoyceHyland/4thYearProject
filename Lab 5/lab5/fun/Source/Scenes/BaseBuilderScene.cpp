#include "Scenes/BaseBuilderScene.h"

BaseBuilderScene::BaseBuilderScene(sf::RenderWindow& t_window) : 
Scene(t_window), 
m_camera(m_window)
{	
	GameData* gameData = GameData::getInstance();
	
	m_grid = gameData->m_currentMap;
	saver.loadMap(m_grid);

}

BaseBuilderScene::~BaseBuilderScene()
{
	saver.saveMap(m_grid);
}

void BaseBuilderScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
	m_editorBox.updatePosition(m_window.mapPixelToCoords({0,0}));

}

void BaseBuilderScene::render()
{

	sf::CircleShape t;

	t.setPosition({0,0});
	t.setFillColor(sf::Color::Yellow);
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	m_window.clear();
	m_grid->draw(m_window);
	m_editorBox.draw(m_window);

	if (m_selectedTiles != nullptr)
	{
		m_selectedTiles->draw(m_window);
	}
	m_window.draw(t);
	m_window.display();
}

void BaseBuilderScene::processKeys(sf::Event t_event)
{
}

void BaseBuilderScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

		if (m_editorBox.contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			m_editorBox.checkForInteraction(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			Tile* possibleTile = m_editorBox.partSelectionCheck(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			if (possibleTile != nullptr)
			{
				m_selectedTiles = possibleTile;
			}

		}
		else if (m_selectedTiles != nullptr)
		{
			m_grid->placePiece(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)), m_selectedTiles->m_textures, m_selectedTiles->m_property);
			saver.saveMap(m_grid);
		}
		
		
	}

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}
	
	
}

void BaseBuilderScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

	}

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.endMove();
	}
}

void BaseBuilderScene::processMouseMove(sf::Event t_event)
{

	m_camera.move();

	if (m_selectedTiles != nullptr)
	{
		m_selectedTiles->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	}
}

void BaseBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
	std::cout << zoomValue << std::endl;
	m_editorBox.updateScale(zoomValue);
	m_editorBox.updatePosition(m_window.mapPixelToCoords({ 0,0 }));

	
}
