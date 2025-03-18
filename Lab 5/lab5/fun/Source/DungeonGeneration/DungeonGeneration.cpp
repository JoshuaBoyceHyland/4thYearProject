#include "DungeonGeneration/DungeonGeneration.h"

DungeonGeneration::DungeonGeneration() : lines( sf::Lines), superTriangle(sf::LineStrip)
{
}

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

	for (int i = 0; i < 20; i++)
	{

		int randWidth = rand() % maxWidth + minWidth;
		int randHeight = rand() % maxHeight + minHeight;
		sf::CircleShape t(5);


		t.setPosition( sf::Vector2f(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2) + getRandomPointInARadius(radius.getRadius()));

		m_roomsGenerated.push_back(new Grid(randWidth, randHeight,100 , 100, t.getPosition()));


		m_roomCollider.push_back(sf::RectangleShape({ (float)randHeight * 100, (float)randWidth * 100 }));
		m_roomCollider[i].setPosition(m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().x - 50, m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().y - 50);
		m_roomCollider[i].setFillColor(sf::Color::Red);
		m_seperation.push_back({0.01f,0.1f});
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
			m_seperation[i].x *= 10;
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

	switch (state)
	{
		case GenerationState::RoomSeperation:
			if (allRoomsAreSeperated())
			{
				state = GenerationState::RoomCulling;
				break;
			}
			seperateRooms();
			break;

		case GenerationState::RoomCulling:
			cullRooms();
			triangulate();
			state = GenerationState::Triangle;
			break;
		case GenerationState::Triangle:
			break;
		default:
			break;
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
		if (m_seperation[i].x == 0 && m_seperation[i].y == 0) 
		{
			roomsSeperated++;
		}
		else
		{
			return false;
		}
	}
	return roomsSeperated == m_seperation.size();
}

void DungeonGeneration::AssignCorners()
{
	Grid* furthersLeftRoom = m_roomsGenerated[0];

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		if (m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().x < furthersLeftRoom->m_cells[0][0].m_body.getPosition().x ) 
		{
			furthersLeftRoom = m_roomsGenerated[i];
		}
	}


	for (int rows = 0; rows < furthersLeftRoom->m_cells.size(); rows++)
	{
		for (int columns = 0; columns < furthersLeftRoom->m_cells[0].size(); columns++)
		{
			furthersLeftRoom->m_cells[rows][columns].setColor(sf::Color::Yellow);
		}
	}
	

	Grid* furthersRightRoom = m_roomsGenerated[0];

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{

		int furthestX = furthersRightRoom->m_cells[0].size() - 1;
		int currentX = m_roomsGenerated[i]->m_cells[0].size() - 1;
		if (m_roomsGenerated[i]->m_cells[0][currentX].m_body.getPosition().x > furthersRightRoom->m_cells[0][furthestX].m_body.getPosition().x)
		{
			furthersRightRoom = m_roomsGenerated[i];
		}
	}


	for (int rows = 0; rows < furthersRightRoom->m_cells.size(); rows++)
	{
		for (int columns = 0; columns < furthersRightRoom->m_cells[0].size(); columns++)
		{
			furthersRightRoom->m_cells[rows][columns].setColor(sf::Color::Blue);
		}
	}


	Grid* topRoom = m_roomsGenerated[0];

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		if (m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().y < topRoom->m_cells[0][0].m_body.getPosition().y)
		{
			topRoom = m_roomsGenerated[i];
		}
	}


	for (int rows = 0; rows < topRoom->m_cells.size(); rows++)
	{
		for (int columns = 0; columns < topRoom->m_cells[0].size(); columns++)
		{
			topRoom->m_cells[rows][columns].setColor(sf::Color::Magenta);
		}
	}


	Grid* bottomRoom = m_roomsGenerated[0];

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{

		int furthestY = bottomRoom->m_cells.size() - 1;
		int currentY = m_roomsGenerated[i]->m_cells.size() - 1;

		if (m_roomsGenerated[i]->m_cells[currentY][0].m_body.getPosition().y > bottomRoom->m_cells[furthestY][0].m_body.getPosition().y)
		{
			bottomRoom = m_roomsGenerated[i];
		}
	}


	for (int rows = 0; rows < bottomRoom->m_cells.size(); rows++)
	{
		for (int columns = 0; columns < bottomRoom->m_cells[0].size(); columns++)
		{
			bottomRoom->m_cells[rows][columns].setColor(sf::Color::White);
		}
	}

}


void DungeonGeneration::cullRooms()
{
	int minRoomWidth = 10;
	int minRoomHeight = 6;

	for (int i = 0; i < m_roomsGenerated.size(); i++)
	{
		if (m_roomsGenerated[i]->m_cells[0].size() < minRoomWidth || m_roomsGenerated[i]->m_cells.size() < minRoomHeight)
		{
			m_subRoomCollider.push_back(m_roomCollider[i]);
			m_subRooms.push_back(m_roomsGenerated[i]);
			
		}
		else
		{
			sf::CircleShape t;
			t.setRadius(10);
			t.setOrigin(10, 10);
			t.setPosition({ m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().x + ( m_roomCollider[i].getSize().x / 2) -50, m_roomsGenerated[i]->m_cells[0][0].m_body.getPosition().y + (m_roomCollider[i].getSize().y / 2) -50 });
			t.setFillColor(sf::Color::Yellow);
			m_centers.push_back(t);
			m_roomCollider[i].setFillColor(sf::Color::Yellow);
			m_mainRoomCollider.push_back(m_roomCollider[i]);
			m_mainRooms.push_back(m_roomsGenerated[i]);
		}
	}
}

void DungeonGeneration::triangulate()
{


	std::vector<PointEdge> edges;

	sort();
	superTrianglePoints = createSuperTriangle();


	// super triangle
	for (int i = 0; i < superTrianglePoints.size(); i++)
	{
		superTriangle.append(sf::Vertex(superTrianglePoints[i], sf::Color::Green));
	}
	superTriangle.append(sf::Vertex(superTrianglePoints[0], sf::Color::Green));

	

	for (int centerI = 0; centerI < m_centers.size(); centerI++)
	{
		std::vector<CircumCircle> circs;
		std::vector<Triangle> triangles;

		// create triangles
		for (int i = 0; i < superTrianglePoints.size(); i++)
		{
			
			// super triangle
			for (int k = 0; k < superTrianglePoints.size(); k++)
			{
				Triangle currentTriangle;


				edges.emplace_back(m_centers[centerI].getPosition(), superTriangle[k].position);

				// add core point
				currentTriangle.addPoint(m_centers[centerI].getPosition());
				// first point of triangle
				currentTriangle.addPoint(superTriangle[k].position);
				currentTriangle.addPoint(superTriangle[k + 1].position);
				// next point is either the next point or the base point
			
				triangles.push_back(currentTriangle);

			}

			//// each other points
			//for (int k = 0; k < m_centers.size(); k++)
			//{
			//	
			//	// dont want to connect to our own point
			//	if (k != centerI) 
			//	{

			//		// current point
			//		sf::Vector2f core = m_centers[centerI].getPosition();

			//		// iterate for next step
			//		for (int n = 0; n < m_centers.size(); n++)
			//		{
			//			Triangle t;

			//			// make usre we are not connecting back to oursleves
			//			if (n != k && n!= centerI)
			//			{
			//				// next step
			//				sf::Vector2f step = m_centers[n].getPosition();

			//				// start triangle
			//				t.addPoint(core);
			//				// step 
			//				t.addPoint(step);

			//				// look for last step
			//				for (int l = 0; l < m_centers.size(); l++)
			//				{
			//					// make sure we are not connect back to our selves
			//					if (l != n && l != centerI && l != k) 
			//					{
			//						t.addPoint(m_centers[l].getPosition());
			//						triangles.push_back(t);
			//					
			//					}
			//				}
			//				

			//				

			//				
			//			}
			//		}

			//		
			//		
			//		
			//	}
			//}


		}





		for (int i = 0; i < triangles.size(); i++)
		{

			circs.emplace_back(triangles[i].points[0], triangles[i].points[1], triangles[i].points[2]);

		}


		//// checking if the circs over lap with the triangles
		for (int i = 0; i < triangles.size(); i++)
		{
			for (int k = 0; k < m_centers.size(); k++)
			{
				if (!triangles[i].isPartOfTriangle( m_centers[k].getPosition()))
				{
					if (circs[i].inCircumCircle(m_centers[k].getPosition()))
					{

						triangles[i].drawVis = false;

					}
				}

			}
		}

		for (int i = 0; i < triangles.size(); i++)
		{
			if (triangles[i].drawVis) 
			{
				trianglesF.push_back(triangles[i]);
			}
			circsF.push_back(circs[i]);
		}
	}
	

	


	//for (int i = 0; i < edges.size(); i++)
	//{



	//	

	//	lines.append(sf::Vertex(edges[i].m_roomIdA, sf::Color::Red));
	//	lines.append(sf::Vertex(edges[i].m_roomIdB, sf::Color::Red));


	//}
}

void DungeonGeneration::draw(sf::RenderWindow& t_window)
{


	switch (state)
	{
	case GenerationState::RoomSeperation:
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
		break;

	case GenerationState::RoomCulling:
		for (int i = 0; i < m_mainRooms.size(); i++)
		{
			m_mainRooms[i]->draw(t_window);
		}
		break;
	case GenerationState::Triangle:
		for (int i = 0; i < m_mainRooms.size(); i++)
		{
			//t_window.draw(m_mainRoomCollider[i]);
			m_mainRooms[i]->draw(t_window);

			
				
			
			//t_window.draw(lines);
			t_window.draw(superTriangle);

			t_window.draw(m_centers[i]);

		
		}
		for (int i = 0; i < trianglesF.size(); i++)
		{

			trianglesF[i].draw(t_window);
			circsF[i].draw(t_window);
		}
		break;
	default:
		break;
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

std::vector<sf::Vector2f> DungeonGeneration::createSuperTriangle()
{

	float minX = m_centers[0].getPosition().x;
	float minY = m_centers[0].getPosition().y;
	float maxX = m_centers[0].getPosition().x;
	float maxY = m_centers[0].getPosition().y;


	for (int i = 0; i <  m_centers.size(); i++)
	{
		minX = std::min(minX, m_centers[i].getPosition().x);
		maxX = std::max(maxX, m_centers[i].getPosition().x);
		minY = std::min(minY, m_centers[i].getPosition().y);
		maxY = std::max(maxY, m_centers[i].getPosition().y);
	}

	sf::Vector2f center = { (minX + maxX) / 2.0f, (minY + maxY) / 2.0f };
	float width = maxX - minX;
	float height = maxY - minY;
	float maxSize = std::max(width, height);


	float offset = maxSize * 2; // Adjust multiplier if necessary

	sf::Vector2f p1(center.x, center.y - offset);      // Top vertex
	sf::Vector2f p2(center.x - offset, center.y + offset); // Bottom left
	sf::Vector2f p3(center.x + offset, center.y + offset); // Bottom right

	
	return { p1, p2, p3 };
}



void DungeonGeneration::sort()
{

	for (int i = 0; i < m_centers.size(); i++)
	{
		std::cout <<"Old: " << m_centers[i].getPosition().x << std::endl;
	}
	std::cout << "\n";

	std::sort(m_centers.begin(), m_centers.end(), [](const auto& a, const auto& b) { return a.getPosition().x < b.getPosition().x; });
	std::sort(m_centers.begin(), m_centers.end(), [](const auto& a, const auto& b) { return a.getPosition().x < b.getPosition().x; });
	for (int i = 0; i < m_centers.size(); i++)
	{
		std::cout << "New: " << m_centers[i].getPosition().x << std::endl;
	}
}

std::vector<sf::CircleShape> DungeonGeneration::sortByDistance(sf::Vector2f position)
{
	std::vector<sf::CircleShape> shortest = m_centers;
	std::sort(shortest.begin(), shortest.end(), [position](const auto& a, const auto& b) { return VectorMath::vectorLength(position, a.getPosition()) < VectorMath::vectorLength(position, b.getPosition()); });
	std::sort(shortest.begin(), shortest.end(), [position](const auto& a, const auto& b) {  return VectorMath::vectorLength(position, a.getPosition()) < VectorMath::vectorLength(position, b.getPosition()); });


	return shortest;
}

bool DungeonGeneration::inCircle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P)
{
	double ax = A.x - P.x;
	double ay = A.y - P.y;
	double bx = B.x - P.x;
	double by = B.y - P.y;
	double cx = C.x - P.x;
	double cy = C.y - P.y;

	double a2 = ax * ax + ay * ay;
	double b2 = bx * bx + by * by;
	double c2 = cx * cx + cy * cy;

	double det = ax * (by * c2 - cy * b2)
		- ay * (bx * c2 - cx * b2)
		+ a2 * (bx * cy - cx * by);

	return det > 1e-9;  // Ensure correct precision handling
}







