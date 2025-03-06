#include "DungeonGeneration/DungeonGeneration.h"

void DungeonGeneration::generateRooms()
{
	radius.setRadius(500);
	radius.setFillColor(sf::Color::Transparent);
	radius.setOutlineThickness(1);
	radius.setOutlineColor(sf::Color::Red);
	radius.setOrigin( radius.getRadius() / 2, radius.getRadius() / 2);
	radius.setPosition({Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2});
	radius.setOrigin(radius.getRadius() , radius.getRadius() );

	int x = Globals::SCREEN_WIDTH / 2;
	int y = Globals::SCREEN_HEIGHT / 2;

	int minWidth = 4;
	int maxWidth = 12;

	int minHeight = 4;
	int maxHeight = 12;

	for (int i = 0; i < 100; i++)
	{

		int randWidth = rand() % maxWidth + minWidth;
		int randHeight = rand() % maxHeight + minHeight;
		sf::CircleShape t(5);


		t.setPosition( sf::Vector2f(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2) + getRandomPointInARadius(radius.getRadius()));

		m_roomsGenerated.push_back(new Grid(randWidth, randHeight,100 , 100, t.getPosition()));


		m_roomCollider.push_back(sf::RectangleShape({ (float)randHeight * 100, (float)randWidth * 100 }));
		m_roomCollider[i].setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().x - 50, m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().y - 50);
		m_roomCollider[i].setFillColor(sf::Color::Red);
		m_seperation.push_back({0,0});
		t.setFillColor(sf::Color::Yellow);
		t.setOrigin({ 2.5, 2.5 });
		t_visuals.push_back(t);

		
	}




}


void DungeonGeneration::calculateSeperation()
{
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		m_roomCollider[i].setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().x - 50, m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().y - 50);
		int seped = 0;
		for (int k = 0; k < m_roomsGenerated.size(); k++)
		{
			if (m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition() != m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition()) 
			{

				float biggestDimension = std::max(m_roomsGenerated[k]->m_cells.size(), m_roomsGenerated[k]->m_cells[0].size());
				biggestDimension *= 100;
				//if (VectorMath::vectorLength(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition(), m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition()) < biggestDimension)
				
				if( m_roomCollider[i].getGlobalBounds().intersects(m_roomCollider[k].getGlobalBounds()))
				{
					m_seperation[i] += m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition() - m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition();
					seped++;
				}				

			
				
			}
		}

		if (seped != 0)
		{
			m_seperation[i].x = m_seperation[i].x / (m_roomsGenerated.size() - 2);
			m_seperation[i].y = m_seperation[i].y / (m_roomsGenerated.size() - 2);

			m_seperation[i] = VectorMath::unitVector(m_seperation[i]) ;
			m_seperation[i].x *=10;
			m_seperation[i].y *= 10;
		}
		else
		{
			m_seperation[i] = { 0,0 };

			
			m_roomsGenerated[i]->setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition());
		}

	}
	
}


void DungeonGeneration::update()
{
	if (!allRoomsAreSeperated())
	{
		seperateRooms();
	}
	else
	{
		emplaceRoomsInWorld();
	}
	
}

void DungeonGeneration::seperateRooms()
{
	calculateSeperation();

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		
		m_roomsGenerated[i]->setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition() + m_seperation[i]);


	}
}

bool DungeonGeneration::allRoomsAreSeperated()
{

	int roomsSeperated = 0;

	for (int i = 0; i < m_seperation.size(); i++)
	{
		if (m_seperation[i].x == 0 && m_seperation[i].y) 
		{
			roomsSeperated++;
		}
		else
		{
			return false;
		}
	}
	return roomsSeperated == m_seperation.size() - 1;
}

void DungeonGeneration::emplaceRoomsInWorld()
{
	

}


void DungeonGeneration::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		t_window.draw(m_roomCollider[i]);
		m_roomsGenerated[i]->draw(t_window);
		
	}

	t_window.draw(radius);

	for (int i = 0; i < t_visuals.size(); i++)
	{
		t_window.draw(t_visuals[i]);
	}
}

sf::Vector2f DungeonGeneration::getRandomPointInARadius(float t_radius)
{

	float randomAngle = 2 * RotationMath::PI * (static_cast<float>(rand()) / RAND_MAX); 

	float randomDistance = (static_cast<float>(rand()) / RAND_MAX) * (static_cast<float>(rand()) / RAND_MAX);

	float scalingFactor;
	
	if (randomDistance > 1)
	{
		scalingFactor = 2 - randomDistance;
	}
	else
	{
		scalingFactor = randomDistance;
	}


	sf::Vector2f randPoint = { t_radius * scalingFactor * std::cos(randomAngle), t_radius * scalingFactor * std::sin(randomAngle) };


	return randPoint;
}
