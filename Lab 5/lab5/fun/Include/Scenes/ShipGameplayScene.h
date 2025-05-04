#pragma once
#include "Ship/Ship.h"
#include "Scene.h"
#include "UI/UIEditorBox.h"
#include "UI/UIScreenBorder.h"
#include "World/Grid.h"
#include "MovableCamera.h"
#include "Minimap.h"
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
		Grid* m_grid = nullptr;
		MovableCamera m_camera;
		MiniMap m_minimap;
		// Inherited via Scene
		
};

