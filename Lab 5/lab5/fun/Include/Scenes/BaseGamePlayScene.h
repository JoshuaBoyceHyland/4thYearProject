#pragma once
#include "Scene.h"
#include "GameData.h"
#include "Grid.h"
#include "MovableCamera.h"
#include "NPC/NPC.h"
class BaseGameplayScene : public Scene
{

	public :
		BaseGameplayScene(sf::RenderWindow& t_window);

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;

	private:
		Grid* m_grid;
		MovableCamera m_camera;
		NPC* m_npc;
};

