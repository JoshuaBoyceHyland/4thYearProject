#pragma once
#include <SFML/Graphics.hpp>
#include "ShipPart.h"
#include "VectorMath.h"
#include "Atttibutes.h"

class EditorMouse
{

	public:
		EditorMouse();



		void checkForPartSelection();
		void releaseSelectedPart();

		void update();

		sf::Vector2f m_position;

		std::vector<ShipPart*> m_partsInScene;

	private:
		ShipPart* getClosestPart();
		sf::Vector2f getClosestConnection(Connectors* t_connector, sf::Vector2f t_point);
		
		ShipPart* m_selectedPart = nullptr;
};

