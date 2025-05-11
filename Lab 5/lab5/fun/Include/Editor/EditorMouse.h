#pragma once
#include <SFML/Graphics.hpp>
#include "Ship/ShipPart.h"
#include "Utility/VectorMath.h"
#include "Ship/Connector.h"
#include "Particles/ParticleExplosion.h"

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>

/// <summary>
/// Will track mouse position and is in charge of selecting any ShipPart and connecting it to another.
/// </summary>
class ShipEditorMouse
{

	public:
		ShipEditorMouse();

		/// <summary>
		/// makes the piece the origin for rotation
		/// </summary>
		void checkForOriginSelection();

		/// <summary>
		/// Assigns a ShipPart as being the current one being held by user.
		/// </summary>
		/// <param name="t_index">Index used to identify which ShipPart in the scene we are assigning</param>
		void selectPiece(int t_index);

		/// <summary>
		/// Checks if we are picking up a ShipPart in the sciene
		/// </summary>
		void checkForPartSelection();

		/// <summary>
		/// Releases a ShipPart from being the selected part ( m_selectedPart ) and also checks if it should be connected to another ShipPart.
		/// </summary>
		void releaseSelectedPart();

		/// <summary>
		/// Sets the position of the selected part ( m_selectedPart ) if its not nullptr.
		/// </summary>
		void update();



		/// <summary>
		/// Position of the mouse
		/// </summary>
		sf::Vector2f m_position;

		/// <summary>
		/// A vector of all the ShipParts in the scene.
		/// </summary>
		std::vector<ShipPart*> m_partsInScene;

		/// <summary>
		/// Where the ship will rotate around
		/// </summary>
		ShipPart* m_shipOrigin = nullptr;

		ParticleExplosion* test = nullptr;
	private:

		/// <summary>
		/// Using the ShipPart Connector, checks which ShipPart is closest to the selected part.
		/// </summary>
		/// <returns>The Closest ShipPart.</returns>
		ShipPart* getClosestPart();

		/// <summary>
		/// Gets the given Connector points closest point to the given t_point.
		/// </summary>
		/// <param name="t_connector">Connector points being checked.</param>
		/// <param name="t_point">Position being checked which point is closest to</param>
		/// <returns> Closest connection point position</returns>
		sf::Vector2f getClosestConnectionPos(Connector* t_connector, sf::Vector2f t_point);

		/// <summary>
		/// Gets the given Connector points closest point Index to the given t_point.
		/// </summary>
		/// <param name="t_connector">Connector points being checked.</param>
		/// <param name="t_point">Position being checked which point is closest to</param>
		/// <returns> Closest connection point Index</returns>
		int getClosestConnectionIndex(Connector* t_connector, sf::Vector2f t_point);
		
		/// <summary>
		/// The ShipPart in the scene which is currently being held by the EditorMouse.
		/// </summary>
		ShipPart* m_selectedPart = nullptr;
		
		
};

