#include "BaseBuilderScene.h"

BaseBuilderScene::BaseBuilderScene(sf::RenderWindow& t_window) : 
Scene(t_window), m_camera(m_window), m_job("Water Filtration", { 300, 300 }), m_room({ 500, 500 }), m_grid(50, 50, 100, 100, {0,0})
{
	m_rect.setFillColor(sf::Color::Yellow);
	m_rect.setSize({ 50, 50 });
	m_rect.setPosition({ Globals::SCREEN_WIDTH / 2,Globals::SCREEN_HEIGHT / 2 });


}

void BaseBuilderScene::update(sf::Time t_deltaTime)
{
	m_camera.update();
	m_editorBox.updatePosition(m_camera.getPosition());
}

void BaseBuilderScene::render()
{
	m_window.clear();
	m_window.draw(m_rect);
	m_job.draw(m_window);
	m_room.draw(m_window);
	m_grid.draw(m_window);
	m_editorBox.draw(m_window);
	m_window.draw(sprite);
	m_window.display();
}

void BaseBuilderScene::processKeys(sf::Event t_event)
{
}

void BaseBuilderScene::processMousePress(sf::Event t_event)
{

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{

		Loader* instance = Loader::getInstance();
		sf::Texture* text = instance->loadTexture("ASSETS/IMAGES/floor.png");


		texture = instance->splitAndLoadTexture("ASSETS/IMAGES/floor.png", 32, 32);
		
		m_grid.placePiece(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)), texture);


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

}

void BaseBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;

	float zoomValue = m_camera.zoom(delta);
	m_editorBox.updateScale(zoomValue);
	
}
