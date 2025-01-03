#pragma once
#include "Ship.h"
#include "Scene.h"
#include "UIEditorBox.h"
#include "UIScreenBorder.h"

class ShipGameplayScene : public Scene
{
	public:
		ShipGameplayScene(sf::RenderWindow& t_window);

		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;
	private:

		UIScreenBorder m_uiBorder;
		Ship m_player;

		// Inherited via Scene
		
};

