#pragma once
#include "Ship.h"
#include "Scene.h"
#include "UIEditorBox.h"
#include "UIScreenBorder.h"

class GameplayScene : public Scene
{
	public:
		GameplayScene(sf::RenderWindow& t_window, Ship t_player);
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;

	private:

		UIScreenBorder m_uiBorder;
		Ship m_player;
};
