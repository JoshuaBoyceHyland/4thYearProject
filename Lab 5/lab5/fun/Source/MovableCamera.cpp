#include "MovableCamera.h"

MovableCamera::MovableCamera(sf::RenderWindow& t_window) : m_window( t_window )
{
	m_camera.setSize(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT);
	m_camera.setCenter({ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });

	m_window.setView(m_camera);
	
}

void MovableCamera::update()
{
	m_window.setView(m_camera);

	if (m_mouseDown)
	{
		m_mouseClickPoint = { (float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y };
	}
}

void MovableCamera::startMove()
{
	m_mouseDown = true;
	m_mouseClickPoint = { (float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y };
}

void MovableCamera::move()
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

void MovableCamera::endMove()
{
	m_mouseDown = false;
}

void MovableCamera::follow(sf::Vector2f t_position)
{

	m_camera.setCenter(t_position);
}

float MovableCamera::zoom(float t_mouseWheelDelta)
{
	float zoomValue = 1;
	if (t_mouseWheelDelta != -1)
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
		zoomValue = 1 + (t_mouseWheelDelta * -0.1f);

		m_camera.zoom(zoomValue);

	}


	return zoomValue;
}

void MovableCamera::setPosition(sf::Vector2f t_position)
{
	m_camera.setCenter(t_position);
}

sf::Vector2f MovableCamera::getPosition() 
{

	sf::Vector2f pos = m_window.mapPixelToCoords({ (int)m_camera.getCenter().x - ((Globals::SCREEN_WIDTH / 2)) , (int)m_camera.getCenter().y - (Globals::SCREEN_HEIGHT / 2) });

	return pos;
}
