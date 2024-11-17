#pragma once
#include "Scene.h"

class GameplayScene : public Scene
{
	public:
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;

	private:


};

