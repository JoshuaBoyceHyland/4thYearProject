#pragma once
#include <SFML/Graphics.hpp>
#include "ShipPart.h"
#include "VectorMath.h"
#include "Atttibutes.h"

class EditorMouse
{

	public:
		EditorMouse();

		void selectPiece(int t_index);
		/// <summary>
		/// Check if we are picking up an already existing piece in the scene
		/// </summary>
		void checkForPartSelection();
		void releaseSelectedPart();

		void update();

		sf::Vector2f m_position;

		std::vector<ShipPart*> m_partsInScene;

	private:
		ShipPart* getClosestPart();
		sf::Vector2f getClosestConnectionPos(Connectors* t_connector, sf::Vector2f t_point);
		int getClosestConnectionIndex(Connectors* t_connector, sf::Vector2f t_point);
		
		ShipPart* m_selectedPart = nullptr;
};

