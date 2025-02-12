#include "Scenes/RoomBuilderScene.h"

RoomBuilderScene::RoomBuilderScene(sf::RenderWindow& t_window, std::function<void(SceneType)> t_sceneChangeFunction) :
Scene(t_window), 
m_camera(m_window)
{	
	GameData* gameData = GameData::getInstance();
	
	m_grid = gameData->m_currentMap;
	saver.loadMap(m_grid);

	RoomLibrary* library = RoomLibrary::getInstance();
	m_editorBox.setButtonFunction(t_sceneChangeFunction);
	setUpButton(t_sceneChangeFunction);


}

RoomBuilderScene::~RoomBuilderScene()
{
	if (m_room != nullptr)
	{
		// clears cells that are possible bcurrently being projected on 
		m_room->cleanUpProjection();
	}
	saver.saveMap(m_grid);
}

void RoomBuilderScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
	m_editorBox.updatePosition(m_window.mapPixelToCoords({0,0}));

}

void RoomBuilderScene::render()
{
	
	sf::CircleShape t;

	t.setPosition({0,0});
	t.setFillColor(sf::Color::Yellow);
	t.setRadius(10);
	t.setOrigin({ 5, 5 });
	m_window.clear();
	m_grid->draw(m_window);
	m_editorBox.draw(m_window);
	m_gameplayTransition.draw(m_window);
	if (m_selectedTiles != nullptr)
	{
		m_selectedTiles->draw(m_window);
	}

	m_window.draw(t);
	m_window.display();
}

void RoomBuilderScene::processKeys(sf::Event t_event)
{
}

void RoomBuilderScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

		if (m_editorBox.contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			
			Tile* possibleTile = m_editorBox.partSelectionCheck(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));

			if (possibleTile != nullptr)
			{
				m_selectedTiles = possibleTile;
			}

			m_editorBox.checkForInteraction(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
			
		}
		else if (m_gameplayTransition.getShape()->getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			m_gameplayTransition.checkForInteraction(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
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

	if (sf::Mouse::Right == t_event.mouseButton.button)
	{
		std::vector<Texture*> null;
		null.push_back(nullptr);
		m_grid->deletePiece(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	}
	
	
}

void RoomBuilderScene::processMouseRelease(sf::Event t_event)
{
	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

	}

	if (sf::Mouse::Middle == t_event.mouseButton.button)
	{
		m_camera.endMove();
	}
}

void RoomBuilderScene::processMouseMove(sf::Event t_event)
{

	m_camera.move();
	if (m_selectedTiles != nullptr)
	{
		m_selectedTiles->setPosition(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)));
	}
}

void RoomBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
	std::cout << zoomValue << std::endl;
	m_editorBox.updateScale(zoomValue);
	m_editorBox.updatePosition(m_window.mapPixelToCoords({ 0,0 }));

}

void RoomBuilderScene::setUpButton(std::function<void(SceneType)> t_sceneChangeFunction)
{
	m_gameplayTransition.setTargetScene(SceneType::BaseGameplay);
	m_gameplayTransition.setFunction(t_sceneChangeFunction);

	m_gameplayTransition.setShapeType(new sf::RectangleShape({ Globals::SCREEN_WIDTH / 15, Globals::SCREEN_HEIGHT / 35 }));
	m_gameplayTransition.getShape()->setFillColor(sf::Color(209, 255, 255));
	m_gameplayTransition.getShape()->setOutlineColor(sf::Color(14, 34, 99));
	m_gameplayTransition.getShape()->setOutlineThickness(Globals::SCREEN_WIDTH / 200);
	m_gameplayTransition.getShape()->setPosition({ Globals::SCREEN_WIDTH  - Globals::SCREEN_WIDTH / 15 - Globals::SCREEN_WIDTH / 200, Globals::SCREEN_HEIGHT - Globals::SCREEN_HEIGHT / 35 -Globals::SCREEN_WIDTH / 200 });

	m_gameplayTransition.setText("Gameplay");
}
