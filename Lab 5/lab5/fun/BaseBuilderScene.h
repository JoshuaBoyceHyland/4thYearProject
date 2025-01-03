#pragma once
#include "Scene.h"
#include "Globals.h"
#include "VectorMath.h"

class BaseBuilderScene : public Scene
{
	public:
		BaseBuilderScene(sf::RenderWindow& t_window);

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;

		void render() override;

		void processKeys(sf::Event t_event) override;

		void processMousePress(sf::Event t_event) override;

		void processMouseRelease(sf::Event t_event) override;

		void processMouseMove(sf::Event t_event) override;

		void processMouseWheel(sf::Event t_event) override;

	private:

		sf::View m_camera;

		sf::RectangleShape m_rect;

		bool m_mouseDown = false;

		int m_currentZoom = 0;
		const int MAX_ZOOM_IN = 10;
		const int MAX_ZOOM_OUT = -10;

		


		sf::Vector2f m_mouseClickPoint;
		sf::Vector2f m_mouseDelta;
		sf::Vector2f m_mouseCurrentPosition;
		

		

};

