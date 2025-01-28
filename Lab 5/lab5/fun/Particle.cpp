#include "Include/Particle.h"

Particle::Particle(int t_millisecondsToLive, sf::Vector2f t_velocity, sf::Vector2f t_position, float t_rotation, sf::Color t_color, float width, float height) :m_millisecondsToLive(t_millisecondsToLive),m_velocity( t_velocity), m_position( t_position)
{
	m_body.setSize({ width, height });
	m_body.setOrigin({ width / 2, height / 2 });
	m_body.setFillColor(t_color);
	m_body.setPosition(m_velocity);
	m_body.setRotation(t_rotation);
	m_speed= rand() % 5 + 1    ;
}

void Particle::update(int t_timePassedInMiliseconds)
{
	if (t_timePassedInMiliseconds > m_millisecondsToLive)
	{
		m_alive = false;
	}

	if (m_alive)
	{
		m_position += m_velocity * m_speed;
		m_body.setPosition(m_position);
	}
	
}

void Particle::draw(sf::RenderWindow& t_window)
{
	if (m_alive)
	{
		t_window.draw(m_body);
	}
	
}
