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

	if (VectorMath::vectorLength({ 0, 0 }, m_velocity) > 0.01f)
	{
		m_lastDirection = VectorMath::unitVector(m_velocity);
	}

	
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


	sf::CircleShape movementMarker(5.f);
	movementMarker.setFillColor(sf::Color::Green);
	movementMarker.setOrigin(5.f, 5.f);
	movementMarker.setPosition(m_position + m_lastDirection * 100.f); // adjust scale for clarity

	t_window.draw(movementMarker);


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

float Ship::getRadius()
{

	float maxRadius = 0.0f;
	sf::Vector2f shipPos = getPosition();

	for (int i = 0; i < m_parts.size(); ++i)
	{
	
		float distance = VectorMath::vectorLength(shipPos, m_parts[i].getPosition());

		sf::Vector2f size = { m_parts[i].m_texture->texture.getSize().x * m_parts[i].m_body.getScale().x,m_parts[i].m_texture->texture.getSize().y * m_parts[i].m_body.getScale().y };
		
		float radius = std::sqrt(size.x * size.x + size.y * size.y) / 2.0f;

		// finding the bigest distance to base radus off
		maxRadius = std::max(maxRadius, distance + radius);
	}
	
	return maxRadius;
}






