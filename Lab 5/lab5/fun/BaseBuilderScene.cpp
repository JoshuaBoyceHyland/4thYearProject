#include "BaseBuilderScene.h"

BaseBuilderScene::BaseBuilderScene(sf::RenderWindow& t_window) : Scene(t_window)
{
	m_rect.setFillColor(sf::Color::Yellow);
	m_rect.setSize({ 50, 50 });
	m_rect.setPosition({ Globals::SCREEN_WIDTH / 2,Globals::SCREEN_HEIGHT / 2 });

	m_camera.setSize(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
	m_camera.setCenter({ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });

	m_window.setView(m_camera);
}

void BaseBuilderScene::update(sf::Time t_deltaTime)
{

	if (m_mouseDown)
	{
		m_mouseClickPoint = { (float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y };
	}

}

void BaseBuilderScene::render()
{
	m_window.setView(m_camera);
	m_window.clear();
	m_window.draw(m_rect);
	m_window.display();
}

void BaseBuilderScene::processKeys(sf::Event t_event)
{
}

void BaseBuilderScene::processMousePress(sf::Event t_event)
{

	m_mouseDown = true;
	m_mouseClickPoint = { (float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y };
}

void BaseBuilderScene::processMouseRelease(sf::Event t_event)
{
	m_mouseDown = false;
}

void BaseBuilderScene::processMouseMove(sf::Event t_event)
{
	m_mouseCurrentPosition = { (float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y };

	if (m_mouseDown)
	{
		m_mouseDelta = m_mouseCurrentPosition - m_mouseClickPoint;

		m_mouseDelta.x *= -1;
		m_mouseDelta.y *= -1;
	

		m_camera.move(m_mouseDelta);
	}
}

void BaseBuilderScene::processMouseWheel(sf::Event t_event)
{
	float delta = t_event.mouseWheel.delta;
	
	if (delta != -1)
	{
		m_currentZoom++;
	}
	else
	{
		m_currentZoom--;
	}

	// should we zoom
	if (m_currentZoom >= MAX_ZOOM_IN)
	{
		m_currentZoom = MAX_ZOOM_IN;
	}
	else if (m_currentZoom <= MAX_ZOOM_OUT)
	{
		m_currentZoom = MAX_ZOOM_OUT;
	}
	else
	{
		float zoomValue = 1 + (delta * -0.1f);

		m_camera.zoom(zoomValue);
	}

	std::cout << "CurrentZoom:: " << m_currentZoom << " Delta: "<<delta<< std::endl;
	

	
	

}
