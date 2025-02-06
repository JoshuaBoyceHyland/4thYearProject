#pragma once
#include "Cell.h"
//#include"Search.h"
class Grid
{
	public:

		Grid();

		Grid(int t_rows, int t_columns, float t_width, float t_height, sf::Vector2f t_startPosition);
		
		void draw(sf::RenderWindow& t_window);

		void changeToWalkable(sf::Vector2f t_mouseCLick);

		void setForGamePlay();

		void deletePiece(sf::Vector2f t_mouseCLick);

		void placePiece(sf::Vector2f t_mouseCLick, std::vector<Texture*> t_textures, TraversalProperty t_property);

		void highlightNeighbours(sf::Vector2f t_mouseCLick);

		Cell* cellSelection(sf::Vector2f t_mouseCLick);

		void resetGridCellForPathFinding( bool t_resetCosts, bool t_resetMarkings);

		void pathFind(sf::Vector2f t_mouseCLick);

		void setStartPoint(sf::Vector2f t_startPoint) { m_startPoint = t_startPoint; }
		
		void inactiveCellsDeletion();
		
		void setPosition(sf::Vector2f t_position);

		void scale(float xScale, float yScale);

		std::vector<Cell*> m_traversableCells;
		std::vector<std::vector<Cell>> m_cells;

	private:

		void setUpNeighbours();

		sf::Vector2f m_startPoint = { -100, -100 };

		float m_cellHeight;
		float m_cellWidth;

		int MAX_ROWS;
		int MAX_COLUMS;

		
};

