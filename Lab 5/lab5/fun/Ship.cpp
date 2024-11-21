#include "Ship.h"

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
		m_rotation -= 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 4;
	}

	float radian = (m_rotation + 270.0f) * (3.14159265359f / 180.0f);
	m_velocity.x = std::cos(radian) * m_speed * (deltaTime / 1000);
	m_velocity.y = std::sin(radian) * m_speed * (deltaTime / 1000);


	m_position += m_velocity;

	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i].move(m_position, m_rotation);
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
	display.setSize({ 100, 100, });
	display.setOrigin(50, 50);
	display.setPosition(m_position);
	t_window.draw(display);



}

void Ship::setPart(ShipPart t_part)
{
	m_parts.push_back(t_part);
}

void Ship::creatOrigin()
{
	std::vector<ShipPart*> hulls;

	for (int i = 0; i < m_parts.size(); i++)
	{
		if (m_parts[i].m_type == PartType::Hull)
		{
			hulls.push_back(&m_parts[i]);
		}
	}
	
	std::vector<ShipPart*> sortedHulls;

	sortedHulls.reserve(sortedHulls.size());

	sortedHulls.push_back(hulls[0]);

	for (int i = 1; i < hulls.size(); i++)
	{
		float current = abs(hulls[i]->getPosition().x + hulls[i]->getPosition().y);

		for (int k = 0; k < sortedHulls.size(); k++)
		{
			float list = abs(sortedHulls[k]->getPosition().x + sortedHulls[k]->getPosition().y);

			if (current < list)
			{
				ShipPart* prev = &(*sortedHulls[k]);
				sortedHulls[k] = hulls[i];

				for (int j = k + 1 ; j < sortedHulls.size() + 1; j++)
				{
					Ship* next = &(*sortedHulls[j+1]);
					sortedHulls[j] = prev;


				
				}
									


			}
	
		}
		
	}

	for (int i = 0; i < sortedHulls.size(); i++)
	{
		std::cout << "X: " << sortedHulls[i]->getPosition().x << " Y: " << sortedHulls[i]->getPosition().y << std::endl; 
	}
	int i = 0;
	i++;

	m_position = (*sortedHulls[static_cast<int>(sortedHulls.size() / 2)]->getConnectors()->anchorPoint);

}




