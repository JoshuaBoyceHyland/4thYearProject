#pragma once
#include "Scene.h"
#include "DungeonGeneration/DungeonGeneration.h"
#include "MovableCamera.h"

class DungeonGenerationTestScene : public Scene
{
	public:

		// Inherited via Scene
		DungeonGenerationTestScene(sf::RenderWindow& t_window);
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;

	private:
		MovableCamera m_camera;
		DungeonGeneration m_dg;
		Dungeon* dungeon;
};