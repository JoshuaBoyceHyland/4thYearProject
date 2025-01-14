#include "BaseBuilderScene.h"

BaseBuilderScene::BaseBuilderScene(sf::RenderWindow& t_window) : 
<<<<<<< Updated upstream
Scene(t_window), m_camera(m_window), m_job("Water Filtration", { 300, 300 }), m_room({ 500, 500 }), m_grid(50, 50, 100, 100, {0,0})
{
	m_rect.setFillColor(sf::Color::Yellow);
	m_rect.setSize({ 50, 50 });
	m_rect.setPosition({ Globals::SCREEN_WIDTH / 2,Globals::SCREEN_HEIGHT / 2 });
=======
Scene(t_window), 
m_camera(m_window), 
m_job("Water Filtration", { 300, 300 }), 
m_room({ 500, 500 }), 
m_grid(50, 50, 100, 100, {0,0})
{	
	saver.saveMap(m_grid);
>>>>>>> Stashed changes
}

void BaseBuilderScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
<<<<<<< Updated upstream
=======
	m_editorBox.updatePosition(m_window.mapPixelToCoords({0,0}));
>>>>>>> Stashed changes
}

void BaseBuilderScene::render()
{
	
	m_window.clear();
	m_grid.draw(m_window);
<<<<<<< Updated upstream
=======
	m_editorBox.draw(m_window);

	if (tile != nullptr)
	{
		tile->draw(m_window);
	}
>>>>>>> Stashed changes
	m_window.display();
}

void BaseBuilderScene::processKeys(sf::Event t_event)
{
}

void BaseBuilderScene::processMousePress(sf::Event t_event)
{
<<<<<<< Updated upstream
=======

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

		if (m_editorBox.contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			m_editorBox.checkForInteraction(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			Tile* possibleTile = m_editorBox.partSelectionCheck(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			if (possibleTile != nullptr)
			{
				tile = possibleTile;
			}
		}
		else if (tile != nullptr)
		{
			m_grid.placePiece(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)), tile->m_textures, tile->m_property);
		}
		
		
	}
>>>>>>> Stashed changes
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}
	
	
}

void BaseBuilderScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.endMove();
	}
}

void BaseBuilderScene::processMouseMove(sf::Event t_event)
{

	m_camera.move();

	if (tile != nullptr)
	{
		tile->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	}
}

void BaseBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

<<<<<<< Updated upstream
	m_camera.zoom(delta);
=======
	float zoomValue = m_camera.zoom(delta);
	std::cout << zoomValue << std::endl;
	m_editorBox.updateScale(zoomValue);
	m_editorBox.updatePosition(m_window.mapPixelToCoords({ 0,0 }));

>>>>>>> Stashed changes
	
}
