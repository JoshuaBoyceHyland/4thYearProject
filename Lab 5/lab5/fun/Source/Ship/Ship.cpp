#include "Ship/Ship.h"

Ship::Ship()
{
	m_tag = Player_ship;
}

void Ship::update(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += 10;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= 10;
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



	std::vector<Cell*> projectedCells = getCurrentCells(m_position + m_velocity);


	if (projectPositionIsCollision())
	{
		m_velocity *= -0.3f;
		m_speed *= 0.5f;
		m_position += m_velocity;
	}
	
	m_position += m_velocity;
	for (int i = 0; i < m_parts.size(); i++)
	{
		m_parts[i].setPosition(m_position + RotationMath::rotatedVector(m_offsets[i], m_rotation));
		m_parts[i].m_body.setRotation(m_rotation);
		m_parts[i].update();
	}

	m_speed *= 0.99f;
	// not used for actual ship, used for minimap to gather info
	m_body.setPosition(m_position);
	m_body.setRotation(m_rotation);

	for (int i = 0; i < m_currentCells.size(); i++)
	{
		m_currentCells[i]->removeGameObject(this);
	}

	m_currentCells = getCurrentCells(m_position);

	for (int i = 0; i < m_currentCells.size(); i++)
	{
		m_currentCells[i]->addToGameObjects(this);
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
	//t_window.draw(display);



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

void Ship::collisionWith(Tag t_tag)
{

}

std::vector<Cell*> Ship::getCurrentCells(sf::Vector2f t_position)
{
	std::vector<Cell*> currentCells;

	
	for (int i = 0; i < m_grids.size(); i++)
	{
		for (int k = 0; k < m_parts.size(); k++)
		{

		

			sf::Vector2f partCenter = t_position + RotationMath::rotatedVector(m_offsets[k], m_rotation);
			sf::Vector2f halfBounds(m_parts[k].m_body.getGlobalBounds().width / 2.f, m_parts[k].m_body.getGlobalBounds().height / 2.f);
			std::vector<sf::Vector2f> boundsCourners = {
														{ -halfBounds.x, -halfBounds.y },  
														{  halfBounds.x, -halfBounds.y },
														{ -halfBounds.x,  halfBounds.y },
														{  halfBounds.x,  halfBounds.y }
													};

			for (int j = 0; j < boundsCourners.size(); j++)
			{
				sf::Vector2f rotatedCorner = RotationMath::rotatedVector(boundsCourners[j], m_rotation);
				sf::Vector2f worldCorner = partCenter + rotatedCorner;
			
				Cell* cell = m_grids[i]->cellSelection(worldCorner);

				if (cell != nullptr)
				{
					if (std::find(currentCells.begin(), currentCells.end(), cell) == currentCells.end())
					{
						currentCells.push_back(cell);
					}
				}
			
			}
		

		}
	}
	
	return  currentCells;
}

bool Ship::projectPositionIsCollision()
{

	sf::Vector2f projectedPos = m_position + m_velocity;
	
	std::vector<Cell*> projectedCells = getCurrentCells(projectedPos);

	for (int  i = 0; i < projectedCells.size(); i++)
	{
		if (projectedCells[i]->getTexture() != nullptr)
		{

			return true;
				
		}
	}
	return false;
}








