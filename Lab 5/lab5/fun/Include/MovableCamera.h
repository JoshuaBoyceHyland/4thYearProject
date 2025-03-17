#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"

class MovableCamera
{
	public:

		MovableCamera(sf::RenderWindow& t_window);

		void update();

		void startMove();
		
		void move();

		void endMove();

		void follow(sf::Vector2f t_position);

		float zoom(float t_mouseWheelDelta);

		void setPosition(sf::Vector2f t_position); 

		sf::Vector2f getPosition();

		
	private:

		/// <summary>
		/// Window out camera is displaying to
		/// </summary>
		sf::RenderWindow& m_window;

		/// <summary>
		/// Camer for view
		/// </summary>
		sf::View m_camera;

		/// <summary>
		/// Whether the player has the mouse held down
		/// </summary>
		bool m_mouseDown = false;

		float m_literalZoom = 1;

		/// <summary>
		/// Current zoom of the camera
		/// </summary>
		int m_currentZoom = 0;

		/// <summary>
		/// Max zoom in we can have
		/// </summary>
		const int MAX_ZOOM_IN = 10;

		/// <summary>
		/// Max xoom out we can have
		/// </summary>
		const int MAX_ZOOM_OUT = -10;


		sf::Vector2f m_mouseClickPoint;
		sf::Vector2f m_mouseDelta;
		sf::Vector2f m_mouseCurrentPosition;
};

