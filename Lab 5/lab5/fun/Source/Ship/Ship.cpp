#include "Ship/Ship.h"

Ship::Ship()
{
	
}

void Ship::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 1;
	}

	float radian = (m_rotation + 270.0f) * (3.14159265359f / 180.0f);
	m_velocity.x = std::cos(radian) * m_speed * (deltaTime / 1000);
	m_velocity.y = std::sin(radian) * m_speed * (deltaTime / 1000);


	m_position += m_velocity;
	std::cout << "X: " << m_velocity.x << " Y: "<<m_velocity.y << std::endl;
	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i].setPosition(m_position + RotationMath::rotatedVector( m_offsets[i], m_rotation));
		m_parts[i].m_body.setRotation( m_rotation);
		m_parts[i].update();
	}

	m_speed *= 0.99f;

	
}
	

void Ship::draw(sf::RenderWindow& t_window)
{

	for ( ShipPart& part : m_parts  )
	{
		part.draw(t_window);
	}


	sf::RectangleShape display;

	display.setFillColor(sf::Color::Yellow);
	display.setSize({ 10, 10, });
	display.setOrigin(50, 50);
	display.setPosition(m_position);
	t_window.draw(display);



}

void Ship::setPart(ShipPart t_part)
{
	sf::Vector2f offset = m_position - t_part.m_body.getPosition();
	offset.x *= -1;
	offset.y *= -1;
	m_offsets.push_back(offset);
	m_parts.push_back(t_part);
	
}

void Ship::setOrigin(sf::Vector2f t_originPos)
{
	m_position = t_originPos;
}





