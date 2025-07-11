#include "Scenes/BaseBuilderScene.h"

BaseBuilderScene::BaseBuilderScene(sf::RenderWindow& t_window, std::function<void(SceneType)> t_sceneChangeFunction) :
Scene(  t_window), 
m_camera(m_window)
{
	GameData* gameData = GameData::getInstance();

	m_grid = gameData->m_currentMap;
	saver.loadMap(m_grid);

	RoomLibrary* library = RoomLibrary::getInstance();
	m_room = library->getRoom(ResourceType(0), 0);

	m_editor.setButtonFunction(t_sceneChangeFunction);
}

BaseBuilderScene::~BaseBuilderScene()
{
	saver.saveMap(m_grid);
}

void BaseBuilderScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
	m_editor.updatePosition(m_window.mapPixelToCoords({ 0,0 }));
	
}

void BaseBuilderScene::render()
{
	m_window.clear();
	m_grid->draw(m_window);
	m_editor.draw(m_window);
	m_window.display();
}

void BaseBuilderScene::processKeys(sf::Event t_event)
{
}

void BaseBuilderScene::processMousePress(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

		if (m_editor.contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			
			Room* possibleRoom = m_editor.roomSelectionCheck(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			if (possibleRoom != nullptr)
			{
				m_room = possibleRoom;
				m_room->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			}

			m_editor.checkForInteraction(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
		}
		else
		{
			m_room->emplaceOnGrid(m_grid, m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			saver.saveMap(m_grid);
		}

		
	}
	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.startMove();
	}

	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		m_room->rotate();
		m_room->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
		m_room->projectOnGrid(m_grid, m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
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
	m_room->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	m_room->projectOnGrid(m_grid, m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
}

void BaseBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
	//std::cout << zoomValue << std::endl;
	m_editor.updateScale(zoomValue);
	m_editor.updatePosition(m_window.mapPixelToCoords({ 0,0 }));
}
