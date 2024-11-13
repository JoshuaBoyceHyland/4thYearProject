#pragma once
#include "Scene.h"
#include "EditorMouse.h"
#include "PartsLibarary.h"
#include "UIBox.h"



class EditorScene : public Scene
{
	public:
		EditorScene(sf::RenderWindow & t_window);

		virtual void update(sf::Time t_deltaTime);
		virtual void render();
		virtual void processKeys(sf::Event t_event);
		virtual void processMousePress(sf::Event t_event);
		virtual void processMouseRelease(sf::Event t_event);
		virtual void processMouseMove(sf::Event t_event);


	private:

		sf::RenderWindow& m_window;
		std::vector<ShipPart*> m_parts;
		EditorMouse m_mouse;
		UIBox ui;
};

