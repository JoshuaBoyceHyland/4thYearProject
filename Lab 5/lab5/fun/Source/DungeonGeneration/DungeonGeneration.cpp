#include "DungeonGeneration/DungeonGeneration.h"

void DungeonGeneration::step1RandomRooms()
{
	radius.setRadius(1000);
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

	for (int i = 0; i < 10; i++)
	{

		int randWidth = rand() % maxWidth + minWidth;
		int randHeight = rand() % maxHeight + minHeight;
		sf::CircleShape t(5);


		t.setPosition( sf::Vector2f(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2) + getRandomPointInARadius(radius.getRadius()));

		m_roomsGenerated.push_back(new Grid(randWidth, randHeight,100 , 100, t.getPosition()));

		t.setFillColor(sf::Color::Yellow);
		t.setOrigin({ 2.5, 2.5 });
		t_visuals.push_back(t);

		
	}




}

void DungeonGeneration::step2Direction()
{
	sf::Vector2f radiusCenter = radius.getPosition();
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		int xCenter = static_cast<int>(m_roomsGenerated[i]->m_cells[0].size() / 2);
		int yCenter = static_cast<int>(m_roomsGenerated[i]->m_cells.size() / 2);
		
		sf::Vector2f directionVector = { 0, 0 } /*VectorMath::directionVector(radiusCenter, m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition())*/;
		
		
		
		m_directions.push_back(directionVector);



	}
}

void DungeonGeneration::step3gatherNeighbours()
{
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		int seped = 0;
		for (int k = 0; k < m_roomsGenerated.size(); k++)
		{
			if (m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition() != m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition()) 
			{

				float biggestDimension = std::max(m_roomsGenerated[k]->m_cells.size(), m_roomsGenerated[k]->m_cells[0].size());
				biggestDimension *= 100;
				if (VectorMath::vectorLength(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition(), m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition()) < biggestDimension)
				{
					m_directions[i] += m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition() - m_roomsGenerated[k]->m_cells[0][0].m_body.getPosition();
					seped++;
				}				

			
				
			}
		}

		if (seped != 0)
		{
			m_directions[i].x = m_directions[i].x / (m_roomsGenerated.size() - 2);
			m_directions[i].y = m_directions[i].y / (m_roomsGenerated.size() - 2);

			m_directions[i] = VectorMath::unitVector(m_directions[i]);
		}
		else
		{
			m_directions[i] = { 0,0 };
		}

	}
	
}


void DungeonGeneration::step4Seperation()
{
	step3gatherNeighbours();
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		
		m_roomsGenerated[i]->setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition() + m_directions[i]);


	}
}





void DungeonGeneration::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
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
