#pragma once
#include <SFML/Graphics.hpp>

class Particle
{


	public:

		Particle(int t_millisecondsToLive,sf::Vector2f t_velocity, sf::Vector2f t_position,float t_rotation, sf::Color t_color, float width, float height );

		void update(int t_timePassed);

		void draw(sf::RenderWindow& t_window);
	private:
		bool m_alive = true;
		int m_millisecondsToLive;
		float m_speed;
		sf::RectangleShape m_body;
		sf::Vector2f m_position;
		sf::Vector2f m_velocity;
};

