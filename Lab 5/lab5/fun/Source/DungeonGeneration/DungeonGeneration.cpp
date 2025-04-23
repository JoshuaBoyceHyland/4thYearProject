#include "DungeonGeneration/DungeonGeneration.h"

DungeonGeneration::DungeonGeneration() : m_superTriangleVisual(sf::LineStrip)
{
}

void DungeonGeneration::generateInitialGrids()
{
	m_spawnRadius.setRadius(500);
	m_spawnRadius.setFillColor(sf::Color::Transparent);
	m_spawnRadius.setOutlineThickness(1);
	m_spawnRadius.setOutlineColor(sf::Color::Red);
	m_spawnRadius.setOrigin( m_spawnRadius.getRadius() / 2, m_spawnRadius.getRadius() / 2);
	m_spawnRadius.setPosition({Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2});
	m_spawnRadius.setOrigin(m_spawnRadius.getRadius() , m_spawnRadius.getRadius() );

	int x = Globals::SCREEN_WIDTH / 2;
	int y = Globals::SCREEN_HEIGHT / 2;

	int minWidth = 4;
	int maxWidth = 12;

	int minHeight = 4;
	int maxHeight = 12;

	for (int i = 0; i < 35; i++)
	{

		int randWidth = rand() % maxWidth + minWidth;
		int randHeight = rand() % maxHeight + minHeight;
		sf::CircleShape circle(5);


		circle.setPosition( sf::Vector2f(Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2) + getRandomPointInARadius(m_spawnRadius.getRadius()));

		m_gridsGenerated.push_back(new Grid(randWidth, randHeight,100 , 100, circle.getPosition()));


		m_roomCollider.push_back(sf::RectangleShape({ ((float)randHeight * 100) * 2, ((float)randWidth * 100 ) *2  }));

		m_roomCollider[i].setPosition(m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().x - 50, m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().y - 50);
		m_roomCollider[i].setFillColor(sf::Color::Red);
		m_seperationForces.push_back({0.01f,0.1f});
		circle.setFillColor(sf::Color::Yellow);
		circle.setOrigin({ 2.5, 2.5 });
		m_spawnPointVisual.push_back(circle);

		
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

void DungeonGeneration::generationLoop()
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
			delauneyTriangle();
			cullDuplicateVisulalTriangles();

			state = GenerationState::DelauneyTriangulation;
			break;
		case GenerationState::DelauneyTriangulation:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				state = GenerationState::MinSpanningTree;
				AddEdgesToRooms();
				AssignCorners();
			}
			break;
		case GenerationState::MinSpanningTree:
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_visulalisedEdges = minSpanning();
				placeEnclosingGrid();

				state = GenerationState::HallwayGen;
				generateHallways();
				cellCheckIsWalkable();




			}
			break;

		case GenerationState::HallwayGen:
	
			
			break;

		case GenerationState::Done:
			break;
		default:
			break;
	}

	
}



void DungeonGeneration::seperateRooms()
{
	calculateSeperation();

	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{
		
		m_gridsGenerated[i]->setPosition(m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition() + m_seperationForces[i]);


	}
}


void DungeonGeneration::calculateSeperation()
{
	for (int currentRoom = 0; currentRoom < m_gridsGenerated.size(); currentRoom++)
	{
		// alligning the the collider with its room
		m_roomCollider[currentRoom].setPosition(m_gridsGenerated[currentRoom]->m_cells[0][0].m_body.getPosition().x - 50, m_gridsGenerated[currentRoom]->m_cells[0][0].m_body.getPosition().y - 50);
		
		// used to check if we havent needed to seperate
		int separationsCaluclated = 0;

		// check for collision with other rooms and calulate seperation force
		for (int otherRoom = 0; otherRoom < m_gridsGenerated.size(); otherRoom++)
		{
			// check we arent checking for collision with our selves
			if (m_gridsGenerated[otherRoom]->m_cells[0][0].m_body.getPosition() != m_gridsGenerated[currentRoom]->m_cells[0][0].m_body.getPosition())
			{
				// collision
				if (m_roomCollider[currentRoom].getGlobalBounds().intersects(m_roomCollider[otherRoom].getGlobalBounds()))
				{
					// add to the seperation force direction
					m_seperationForces[currentRoom] += m_gridsGenerated[currentRoom]->m_cells[0][0].m_body.getPosition() - m_gridsGenerated[otherRoom]->m_cells[0][0].m_body.getPosition();
					separationsCaluclated++;
				}



			}
		}

		// seperation force needs to be calulated
		if (separationsCaluclated != 0)
		{
			float seperationForceMultiplier = 10;
			// averaging the force down
			m_seperationForces[currentRoom].x = m_seperationForces[currentRoom].x / (m_gridsGenerated.size() - 2);
			m_seperationForces[currentRoom].y = m_seperationForces[currentRoom].y / (m_gridsGenerated.size() - 2);

			m_seperationForces[currentRoom] = VectorMath::unitVector(m_seperationForces[currentRoom]);

			m_seperationForces[currentRoom].x *= seperationForceMultiplier;
			m_seperationForces[currentRoom].y *= seperationForceMultiplier;
		}
		else // room has been seperated 
		{
			m_seperationForces[currentRoom] = { 0,0 };
			m_gridsGenerated[currentRoom]->setPosition(m_gridsGenerated[currentRoom]->m_cells[0][0].m_body.getPosition());
		}

	}

}

bool DungeonGeneration::allRoomsAreSeperated()
{

	int roomsSeperated = 0;

	for (int i = 0; i < m_seperationForces.size(); i++)
	{
		if (m_seperationForces[i].x == 0 && m_seperationForces[i].y == 0) 
		{
			roomsSeperated++;
		}
		else
		{
			return false;
		}
	}
	return roomsSeperated == m_seperationForces.size();
}


void DungeonGeneration::cullRooms()
{
	// desired min dimension of rooms
	int minRoomWidth = 10;
	int minRoomHeight = 6;

	// index to acces main rooms
	int mainRoomsCreated = 0;

	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{
		if (m_gridsGenerated[i]->m_cells[0].size() < minRoomWidth || m_gridsGenerated[i]->m_cells.size() < minRoomHeight)
		{
			// if we need to keep any subj rooms for later
		}
		else
		{



			m_roomCollider[i].setFillColor(sf::Color::Yellow); // debug

			m_mainRoomCollider.push_back(m_roomCollider[i]);
			m_mainRooms.push_back(new Room(*m_gridsGenerated[i]));
			m_mainRooms[mainRoomsCreated]->point = Point({ m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().x + (m_roomCollider[i].getSize().x / 4) - 50, m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().y + (m_roomCollider[i].getSize().y / 4) - 50 });
			m_mainRooms[mainRoomsCreated]->roomId = mainRoomsCreated;
			m_mainRooms[mainRoomsCreated]->setWalkable();
			mainRoomsCreated++;

		}
	}



}

void DungeonGeneration::delauneyTriangle()
{

	std::vector<PointEdge> edges;
	std::vector<Point> superTrianglePoints;

	// sort the rooms based on position on x axis
	auto xPosbasedSort = [](const Room* a, const Room* b) { return a->point.visual.getPosition().x < b->point.visual.getPosition().x; };
	std::sort(m_mainRooms.begin(), m_mainRooms.end(), xPosbasedSort);

	// get super triangle
	superTrianglePoints = createSuperTriangle();


	// create super triangle visual
	for (int i = 0; i < superTrianglePoints.size(); i++)
	{
		m_superTriangleVisual.append(sf::Vertex(superTrianglePoints[i].visual.getPosition(), sf::Color::Green));
	}
	m_superTriangleVisual.append(sf::Vertex(superTrianglePoints[0].visual.getPosition(), sf::Color::Green));


	// for every room we have
	for (int firstRoom = 0; firstRoom < m_mainRooms.size(); firstRoom++)
	{
		std::vector<CircumCircle> circumCirlces;
		std::vector<Triangle> triangles;

		// we create triangles between rooms and the super triangle
		for (int k = 0; k < superTrianglePoints.size(); k++)
		{
			Triangle currentTriangle;

			edges.emplace_back(firstRoom, m_mainRooms[firstRoom]->point.visual.getPosition(), k, m_superTriangleVisual[k].position);

			// add core point
			currentTriangle.addPoint(firstRoom, m_mainRooms[firstRoom]->point.visual.getPosition());
			// first point of triangle

			currentTriangle.addPoint(k, m_superTriangleVisual[k].position);
			currentTriangle.addPoint(k + 1, m_superTriangleVisual[k + 1].position);
			

			triangles.push_back(currentTriangle);


		}



		// Create triangles between rooms 
		for (int secondRoom = 0; secondRoom < m_mainRooms.size(); secondRoom++)
		{

			// dont want to connect to our own point
			if (secondRoom != firstRoom)
			{

				// core point for whole loop
				sf::Vector2f firstRoomPos = m_mainRooms[firstRoom]->point.visual.getPosition();

				// first step in triangle 
				sf::Vector2f secondRoomPos = m_mainRooms[secondRoom]->point.visual.getPosition();


				// look for last steps
				for (int thirdRoom = 0; thirdRoom < m_mainRooms.size(); thirdRoom++)
				{
					// make sure we are not connect back to our selves
					if (thirdRoom != firstRoom && thirdRoom != secondRoom)
					{
						Triangle triangle;

						triangle.addPoint(firstRoom, firstRoomPos);
						// step 
						triangle.addPoint(secondRoom, secondRoomPos);
						// last point 
						triangle.addPoint(thirdRoom, m_mainRooms[thirdRoom]->point.visual.getPosition());

						// visual
						triangle.visualiseation[0].color = sf::Color::Yellow;
						triangle.visualiseation[1].color = sf::Color::Yellow;
						triangle.visualiseation[2].color = sf::Color::Yellow;

						// check if triang already exists within rooms 
						if (!m_mainRooms[firstRoom]->point.hasTriangle(triangle) && !m_mainRooms[secondRoom]->point.hasTriangle(triangle) && !m_mainRooms[thirdRoom]->point.hasTriangle(triangle))
						{
							//give each room the the triangle
							m_mainRooms[firstRoom]->point.triangles.push_back(triangle);
							m_mainRooms[secondRoom]->point.triangles.push_back(triangle);
							m_mainRooms[thirdRoom]->point.triangles.push_back(triangle);
							triangles.push_back(triangle);
						}
					}
				}

			}
		}


		// for each triange create a circum circle
		for (int i = 0; i < triangles.size(); i++)
		{
			circumCirlces.emplace_back(triangles[i].points[0], triangles[i].points[1], triangles[i].points[2]);
		}


		// checking what triangles adhere to the delauney triangluation
		// if the circume circle doesnt contain any other points other than the points that make up the triangl
		for (int i = 0; i < triangles.size(); i++)
		{
			// checking all generated rooms
			for (int k = 0; k < m_mainRooms.size(); k++)
			{
				// if the room is not part of the trianle
				if (!triangles[i].isPartOfTriangle(m_mainRooms[k]->point.visual.getPosition()))
				{
					// check if the room appears with in the curcum circcle
					// if it does, this triangl is not valid
					if (circumCirlces[i].inCircumCircle(m_mainRooms[k]->point.visual.getPosition()))
					{

						triangles[i].drawVis = false;

					}
				}

			}
		}

		// gather our valid trianglation
		for (int i = 0; i < triangles.size(); i++)
		{
			if (triangles[i].drawVis)
			{
				m_finalTriangulations.push_back(triangles[i]);
			}


		}
	}



}

std::vector<Point> DungeonGeneration::createSuperTriangle()
{
	// set defaults
	float minX = m_mainRooms[0]->point.visual.getPosition().x;
	float minY = m_mainRooms[0]->point.visual.getPosition().y;
	float maxX = m_mainRooms[0]->point.visual.getPosition().x;
	float maxY = m_mainRooms[0]->point.visual.getPosition().y;


	// find max min dimesnions
	for (int i = 0; i < m_mainRooms.size(); i++)
	{
		minX = std::min(minX, m_mainRooms[i]->point.visual.getPosition().x);
		maxX = std::max(maxX, m_mainRooms[i]->point.visual.getPosition().x);
		minY = std::min(minY, m_mainRooms[i]->point.visual.getPosition().y);
		maxY = std::max(maxY, m_mainRooms[i]->point.visual.getPosition().y);
	}

	sf::Vector2f center = { (minX + maxX) / 2.0f, (minY + maxY) / 2.0f };
	float width = maxX - minX;
	float height = maxY - minY;
	float maxSize = std::max(width, height);

	// gives more room for triangle
	float sizeMultiplier = 2;
	float offset = maxSize * sizeMultiplier; // final offset for the triangle size

	sf::Vector2f p1(center.x, center.y - offset);      // top point
	sf::Vector2f p2(center.x - offset, center.y + offset); // bottom left point
	sf::Vector2f p3(center.x + offset, center.y + offset); // bottom right point


	return { p1, p2, p3 };
}

void DungeonGeneration::cullDuplicateVisulalTriangles()
{

	std::sort(m_finalTriangulations.begin(), m_finalTriangulations.end());   
	m_finalTriangulations.erase(std::unique(m_finalTriangulations.begin(), m_finalTriangulations.end()), m_finalTriangulations.end());
}


void DungeonGeneration::AddEdgesToRooms()
{


	std::vector<PointEdge> edgesL;

	// cutting down duplicate edges and adding them to list
	for (int i = 0; i < m_finalTriangulations.size(); i++)
	{
		for (int k = 0; k < m_finalTriangulations[i].edges.size(); k++)
		{

			if (!partOfSuperTriangle(m_finalTriangulations[i].edges[k]) && !listContainsEdge(edgesL, m_finalTriangulations[i].edges[k]))
			{
				edgesL.push_back(m_finalTriangulations[i].edges[k]);
			}
		}
	}

	// connect edges between rooms
	for (int i = 0; i < edgesL.size(); i++)
	{

		m_mainRooms[edgesL[i].m_roomAId]->point.edges.push_back({ edgesL[i].m_roomAId, edgesL[i].m_roomAPos, edgesL[i].m_roomBId, edgesL[i].m_roomBPos });
		m_mainRooms[edgesL[i].m_roomBId]->point.edges.push_back({ edgesL[i].m_roomBId, edgesL[i].m_roomBPos, edgesL[i].m_roomAId, edgesL[i].m_roomAPos });
	}


	m_visulalisedEdges = edgesL;



}

void DungeonGeneration::AssignCorners()
{

	Grid* furthersLeftRoom = m_gridsGenerated[0];
	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{
		if (m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().x < furthersLeftRoom->m_cells[0][0].m_body.getPosition().x ) 
		{
			furthersLeftRoom = m_gridsGenerated[i];
		}
	}
	gridstart.x =  furthersLeftRoom->m_cells[0][0].m_body.getPosition().x - 50;

	

	Grid* furthersRightRoom = m_gridsGenerated[0];
	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{

		int furthestX = furthersRightRoom->m_cells[0].size() - 1;
		int currentX = m_gridsGenerated[i]->m_cells[0].size() - 1;
		if (m_gridsGenerated[i]->m_cells[0][currentX].m_body.getPosition().x > furthersRightRoom->m_cells[0][furthestX].m_body.getPosition().x)
		{
			furthersRightRoom = m_gridsGenerated[i];
		}
	}
	int furthestX = furthersRightRoom->m_cells[0].size() - 1;
	gridEnd.x = furthersRightRoom->m_cells[0][furthestX].m_body.getPosition().x + 100;
	

	Grid* topRoom = m_gridsGenerated[0];
	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{
		if (m_gridsGenerated[i]->m_cells[0][0].m_body.getPosition().y < topRoom->m_cells[0][0].m_body.getPosition().y)
		{
			topRoom = m_gridsGenerated[i];
		}
	}
	gridstart.y = topRoom->m_cells[0][0].m_body.getPosition().y - 50;

	Grid* bottomRoom = m_gridsGenerated[0];
	for (int i = 0; i < m_gridsGenerated.size(); i++)
	{

		int furthestY = bottomRoom->m_cells.size() - 1;
		int currentY = m_gridsGenerated[i]->m_cells.size() - 1;

		if (m_gridsGenerated[i]->m_cells[currentY][0].m_body.getPosition().y > bottomRoom->m_cells[furthestY][0].m_body.getPosition().y)
		{
			bottomRoom = m_gridsGenerated[i];
		}
	}
	int furthestY = bottomRoom->m_cells.size() - 1;
	gridEnd.y = bottomRoom->m_cells[furthestY][0].m_body.getPosition().y + 100;
}



void DungeonGeneration::draw(sf::RenderWindow& t_window)
{


	switch (state)
	{
		case GenerationState::RoomSeperation:
			for (int i = 0; i < m_gridsGenerated.size(); i++)
			{
				t_window.draw(m_roomCollider[i]);
				m_gridsGenerated[i]->draw(t_window);
				t_window.draw(m_spawnPointVisual[i]);
			}

			t_window.draw(m_spawnRadius);

			break;

		case GenerationState::RoomCulling:
			for (int i = 0; i < m_mainRooms.size(); i++)
			{
				m_mainRooms[i]->draw(t_window);
			}
			break;
		case GenerationState::DelauneyTriangulation:
			for (int i = 0; i < m_mainRooms.size(); i++)
			{
		
				m_mainRooms[i]->draw(t_window);

				t_window.draw(m_superTriangleVisual);


			}
			for (int i = 0; i < m_finalTriangulations.size(); i++)
			{
			
				m_finalTriangulations[i].draw(t_window);
				
				

			}

			break;
		case GenerationState::MinSpanningTree:

			if (m_dungeon != nullptr)
			{
				m_dungeon->draw(t_window);
			}
			for (int i = 0; i < m_mainRooms.size(); i++)
			{
				m_mainRooms[i]->draw(t_window);
				
			}
			for (int i = 0; i < m_visulalisedEdges.size(); i++)
			{
				m_visulalisedEdges[i].draw(t_window);
			}
			break;

		case GenerationState::HallwayGen:

			if (m_dungeon != nullptr)
			{
				m_dungeon->draw(t_window);
			}

	
			for (int i = 0; i < m_mainRooms.size(); i++)
			{
				for (int k = 0; k < m_mainRooms[i]->point.edges.size(); k++)
				{
					m_mainRooms[i]->point.edges[k].draw(t_window);

				}
				t_window.draw(m_mainRooms[i]->point.m_text);
			}




			break;

		default:
			break;
	}
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

std::vector<PointEdge> DungeonGeneration::minSpanning()
{


	std::vector<PointEdge> finalEdges;
	std::vector<bool> visited(m_mainRooms.size(), false);
	std::priority_queue<PointEdge, std::vector<PointEdge>, pQPointEdgeComparer> remaingEdges;

	visited[0] = true;
	for (int i = 0; i < m_mainRooms[0]->point.edges.size(); i++)
	{
		remaingEdges.push(m_mainRooms[0]->point.edges[i]);
	}

	while (!remaingEdges.empty())
	{
		// next edge pop
		PointEdge currentEdge = remaingEdges.top();
		remaingEdges.pop();

		int nextRoom = currentEdge.m_roomBId;

		// if visited then we want to skip this edge
		if (visited[nextRoom]) { continue; }

		// mark it as visted now that we are looking at it
		visited[nextRoom] = true;

		finalEdges.push_back(currentEdge);

		// make sure the edge leading back to our current center are also set to false

		for (int i = 0; i < m_mainRooms[currentEdge.m_roomAId]->point.edges.size(); i++)
		{
			if (m_mainRooms[currentEdge.m_roomAId]->point.edges[i].m_roomBId == currentEdge.m_roomBId)
			{
				m_mainRooms[currentEdge.m_roomAId]->point.edges[i].visited = true;
				break;
			}
		}
		for (int i = 0; i < m_mainRooms[currentEdge.m_roomBId]->point.edges.size(); i++)
		{
			if (m_mainRooms[currentEdge.m_roomBId]->point.edges[i].m_roomBId == currentEdge.m_roomAId)
			{
				m_mainRooms[currentEdge.m_roomBId]->point.edges[i].visited = true;
				break;
			}
		}


		// add new edges
		for (int i = 0; i < m_mainRooms[nextRoom]->point.edges.size(); i++)
		{
			if (!visited[m_mainRooms[nextRoom]->point.edges[i].m_roomBId])
			{
				remaingEdges.push(m_mainRooms[nextRoom]->point.edges[i]);
			}
		}
	}

	// lambda for removing the edges not in min span 
	auto minSpanningClean = [](const PointEdge& edge) { return !edge.visited; };
	
	for (int i = 0; i < m_mainRooms.size(); i++)
	{
		m_mainRooms[i]->point.edges.erase(std::remove_if(m_mainRooms[i]->point.edges.begin(), m_mainRooms[i]->point.edges.end(), minSpanningClean), m_mainRooms[i]->point.edges.end());
	
		m_mainRooms[i]->point.m_text.setString(std::to_string(m_mainRooms[i]->point.edges.size()));
		m_mainRooms[i]->point.m_text.setPosition(m_mainRooms[i]->point.visual.getPosition());
	}

	return finalEdges;
}



bool DungeonGeneration::listContainsEdge(std::vector<PointEdge> edges, PointEdge e)
{

	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i] == e)
		{
			return true;
		}
	}
	return false;
}

bool DungeonGeneration::partOfSuperTriangle(PointEdge e)
{

	for (int i = 0; i < m_superTriangleVisual.getVertexCount(); i++)
	{
		if (e == m_superTriangleVisual[i].position)
		{
			return true;
		}
	}
	return false;
}

void DungeonGeneration::placeEnclosingGrid()
{

	int coluumnNum = (gridEnd.x - gridstart.x) / 100;
	int rowNum = (gridEnd.y - gridstart.y) / 100;

	m_dungeon = new Grid(rowNum, coluumnNum, 100, 100, { gridstart });


	for (int i = 0; i < m_mainRooms.size(); i++)
	{

		sf::Vector2f roomPos = m_mainRooms[i]->m_grid.m_cells[0][0].m_body.getPosition();
		sf::Vector2f localRoomPos = roomPos - gridstart;

		m_mainRooms[i]->emplaceOnGrid(m_dungeon, localRoomPos);

	}
}



void DungeonGeneration::generateHallways()
{

	for (int currentRoom = 0; currentRoom < m_mainRooms.size(); currentRoom++)
	{
		for (int currentEdge = 0; currentEdge < m_mainRooms[currentRoom]->point.edges.size(); currentEdge++)
		{

			Cell* startingCell = getHallywayEntry(currentRoom, m_mainRooms[currentRoom]->point.edges[currentEdge].m_roomBId);
			Cell* endingCell = getHallywayEntry(m_mainRooms[currentRoom]->point.edges[currentEdge].m_roomBId, currentRoom);
			

			Cell* midPointCell = nullptr;

			sf::Vector2f roomsAPos = m_mainRooms[currentRoom]->point.visual.getPosition();
			sf::Vector2f roomsBPos = m_mainRooms[m_mainRooms[currentRoom]->point.edges[currentEdge].m_roomBId]->point.visual.getPosition();

			sf::Vector2f direction = roomsBPos - roomsAPos;

			float angle = std::atan2(direction.y, direction.x) * 180 / RotationMath::PI;

			// only need to do bottom and right and each edge will be represented both way in rooms
			if (angle >= 45 && angle < 135) //bottom
			{
				int midPointRow = std::abs(startingCell->getNode()->m_row - endingCell->getNode()->m_row) / 2;
				midPointCell = &m_dungeon->m_cells[endingCell->getNode()->m_row - midPointRow][startingCell->getNode()->m_column];
				midPointCell->setColor(sf::Color::Green);

				verticalStrip(startingCell->getNode()->m_row, midPointCell->getNode()->m_row , startingCell->getNode()->m_column, false);
				horizontalStrip(midPointCell->getNode()->m_column , endingCell->getNode()->m_column , midPointCell->getNode()->m_row, true);
				verticalStrip(midPointCell->getNode()->m_row, endingCell->getNode()->m_row, endingCell->getNode()->m_column, false);

				startingCell->setColor(sf::Color(255, 127, 8));
				endingCell->setColor(sf::Color(255, 127, 8));
				midPointCell->setColor(sf::Color::Green);
				
			}
			else if (angle >= -45 && angle < 45) // right
			{
				int midPointCol = std::abs(startingCell->getNode()->m_column - endingCell->getNode()->m_column) / 2;
				midPointCell = &m_dungeon->m_cells[endingCell->getNode()->m_row ][startingCell->getNode()->m_column + midPointCol];
				midPointCell->setColor(sf::Color::Green);


				horizontalStrip(startingCell->getNode()->m_column , midPointCell->getNode()->m_column, startingCell->getNode()->m_row, false);
				verticalStrip(startingCell->getNode()->m_row , midPointCell->getNode()->m_row , midPointCell->getNode()->m_column, true);
				horizontalStrip(midPointCell->getNode()->m_column, endingCell->getNode()->m_column, endingCell->getNode()->m_row, false);

				startingCell->setColor(sf::Color(255, 127, 8));
				endingCell->setColor(sf::Color(255, 127, 8));
				midPointCell->setColor(sf::Color::Green);
			
			}
				
			
		}


	}

}

void DungeonGeneration::horizontalStrip(int xStart, int xEnd, int row, bool corner)
{


	if (xStart == xEnd) { return; }
	if (xStart > xEnd) std::swap(xStart, xEnd);

	if (corner)
	{
		xStart -= m_hallWayPadding;
		xEnd += m_hallWayPadding;
	}


	for (int x = xStart; x <= xEnd; ++x)
	{
		// create  halways with a thing nes of 3
		
		m_dungeon->m_cells[row][x].setColor(sf::Color::Cyan);
		m_dungeon->m_cells[row][x].setProperty(TraversalProperty::Walkable);

		for (int padding = 1; padding <= m_hallWayPadding; padding++)
		{
			m_dungeon->m_cells[row - padding][x ].setColor(sf::Color::Cyan);
			m_dungeon->m_cells[row - padding][x].setProperty(TraversalProperty::Walkable);
			m_dungeon->m_cells[row + padding][x ].setColor(sf::Color::Cyan);
			m_dungeon->m_cells[row + padding][x].setProperty(TraversalProperty::Walkable);
		}


	
	}
}

void DungeonGeneration::verticalStrip(int yStart, int yEnd, int col, bool corner)
{
	
	if (yStart == yEnd) { return; }
	if (yStart > yEnd) std::swap(yStart, yEnd);


	if (corner)
	{
		yStart -= m_hallWayPadding;
		yEnd += m_hallWayPadding;
	}

	for (int y = yStart; y <= yEnd; ++y)
	{
		m_dungeon->m_cells[y][col].setColor(sf::Color::Blue);	
		m_dungeon->m_cells[y][col].setProperty(TraversalProperty::Walkable);
		for (int padding = 1; padding <= m_hallWayPadding; padding++)
		{
			m_dungeon->m_cells[y][col - padding].setColor(sf::Color::Blue);
			m_dungeon->m_cells[y][col - padding].setProperty(TraversalProperty::Walkable);
			m_dungeon->m_cells[y][col + padding].setColor(sf::Color::Blue);
			m_dungeon->m_cells[y][col + padding].setProperty(TraversalProperty::Walkable);
		
		}
	}
}

Cell* DungeonGeneration::getHallywayEntry( int t_roomAId, int t_roomBId)
{
	Cell* startingCell = nullptr;

	sf::Vector2f roomsAPos = m_mainRooms[t_roomAId]->point.visual.getPosition();
	sf::Vector2f roomsBPos = m_mainRooms[t_roomBId]->point.visual.getPosition();

	sf::Vector2f direction = roomsBPos - roomsAPos;

	float angle = std::atan2(direction.y, direction.x) * 180 / RotationMath::PI;

	int gridCols = static_cast<int>(m_mainRooms[t_roomAId]->m_grid.m_cells[0].size() - 1);
	int gridRows = static_cast<int>(m_mainRooms[t_roomAId]->m_grid.m_cells.size() - 1);

	if (angle >= -45 && angle < 45) // right
		startingCell = m_mainRooms[t_roomAId]->cellsOccupied[static_cast<int>(gridRows / 2)][gridCols];
	else if (angle >= 45 && angle < 135) // velow
		startingCell = m_mainRooms[t_roomAId]->cellsOccupied[gridRows][static_cast<int>(gridCols / 2)];
	else if (angle >= -135 && angle < -45) // above

		startingCell = m_mainRooms[t_roomAId]->cellsOccupied[0][static_cast<int>(gridCols / 2)];
	else // left
		startingCell = m_mainRooms[t_roomAId]->cellsOccupied[static_cast<int>(gridRows / 2)][0];

	return startingCell;
}

void DungeonGeneration::cellCheckIsWalkable()
{
	
	m_dungeon->setUpNeighbours(true);
	std::vector<Node*> nextNeighbours;

	for (int row = 0; row < m_dungeon->m_cells.size(); row++)
	{
		for (int column = 0; column < m_dungeon->m_cells[row].size(); column++)
		{
			if (m_dungeon->m_cells[row][column].getNode()->getNeighbours().size() != 0) 
			{
				int size = m_dungeon->m_cells[row][column].getNode()->getNeighbours().size();
				nextNeighbours = m_dungeon->m_cells[row][column].getNode()->getNeighbours();
				break;
			}
		}

		if (!nextNeighbours.empty())
		{
			break;
		}
	}
	  

	while (!nextNeighbours.empty())
	{
		for (int  i = 0; i < nextNeighbours.size(); i++)
		{
			if (m_dungeon->m_cells[nextNeighbours[i]->m_row][nextNeighbours[i]->m_column].getProperty() == TraversalProperty::Walkable)
			{
				m_dungeon->m_cells[nextNeighbours[i]->m_row][nextNeighbours[i]->m_column].setColor(sf::Color::Yellow);
			}
			
		}
		nextNeighbours = Search::breadhFirstIncremental(nextNeighbours, m_dungeon->m_cells[m_dungeon->m_cells.size() - 1][m_dungeon->m_cells[0].size() - 1].m_body.getPosition());
	}
	
}









