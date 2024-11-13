#pragma once
#include <SFML/Graphics.hpp>
class Scene
{
	public:

		virtual void update(sf::Time t_deltaTime) = 0;

		virtual void render() = 0;

		virtual void processKeys(sf::Event t_event)=0;

		virtual void processMousePress(sf::Event t_event)=0;

		virtual void processMouseRelease(sf::Event t_event) =0;

		virtual void processMouseMove(sf::Event t_event)=0;



};

