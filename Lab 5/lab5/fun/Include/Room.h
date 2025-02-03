#pragma once
#include "Cell.h"
#include <fstream>
#include <sstream>
#include <string>
#include "Grid.h"
#include "TileLibrary.h"
#include "VectorMath.h"
#include "RotationMath.h"

enum class ResourceType{  Electricty, Happinness, Water, Oxygen, None};

class Room
{
	public:

		Room();

		Room(Grid t_grid);

		bool emplaceOnGrid(Grid* t_backgroundGrid, sf::Vector2f t_mosuePosition);

		void setPosition(sf::Vector2f t_mosuePosition);

		void draw(sf::RenderWindow& t_window);
	private:

		Grid m_grid;

};

