#pragma once
#include "Scene.h"
#include "GameData.h"
#include "Grid.h"
#include "MapSaver.h"
class BaseGamePlayScene : public Scene
{
	public:
		BaseGamePlayScene(sf::RenderWindow& t_window);
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;
	private: 
		Grid* m_map;
		MapSaver saver;
};

