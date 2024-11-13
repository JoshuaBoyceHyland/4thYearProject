#pragma once
#include "Loader.h"
#include "ShipPart.h"

/// <summary>
/// Holds every ship part that can be made.
/// </summary>
class PartsLibarary
{
	public:
		PartsLibarary(const PartsLibarary& other) = delete;

		/// <summary>
		/// Gets the single instance of this class, if class instance doesn't exist it instaniates it.
		/// </summary>
		/// <returns> Pointer to instance of PartsLibrary</returns>
		static PartsLibarary* getInstance();
		
		/// <summary>
		/// Gets a specific cockpit part using an index.
		/// </summary>
		/// <param name="t_index">Index of cockpit part.</param>
		/// <returns>Desired cockpit</returns>
		ShipPart* getCockpit(int t_index);

		/// <summary>
		/// Gets a specific hull part using an index.
		/// </summary>
		/// <param name="t_index">Index of hull part.</param>
		/// <returns>Desired hull.</returns>
		ShipPart* getHullPart(int t_index);

		/// <summary>
		/// Gets a specific thruster part using an index.
		/// </summary>
		/// <param name="t_index">Index of thruster part.</param>
		/// <returns>Desired thruster</returns>
		ShipPart* getGetThruster(int t_index);

		/// <summary>
		/// Gets a specific left wing part using an index.
		/// </summary>
		/// <param name="t_index">Index of left wing part.</param>
		/// <returns>Desired left wing</returns>
		ShipPart* getLeftWing(int t_index);

		/// <summary>
		/// Gets a specific right wing part using an index.
		/// </summary>
		/// <param name="t_index">Index of right wing part.</param>
		/// <returns>Desired right wing</returns>
		ShipPart* getRightWing(int t_index);

		/// <summary>
		/// Gets a specific part from the the ShipParts vector using the type and index.
		/// </summary>
		/// <param name="t_type">Type of ship part desired.</param>
		/// <param name="t_index">Index of ship part.</param>
		/// <returns>Desired shipPart</returns>
		ShipPart* getPart(PartType t_type, int t_index);

		/// <summary>
		/// Amount of each type of ship part.
		/// </summary>
		static const int NUM_OF_EACH_PART = 2;
	private:

		/// <summary>
		/// Private constructor so it can only be created internally by the getInstance function if needed to. Calls fillLibrary().
		/// </summary>
		PartsLibarary();

		/// <summary>
		/// Fills each Vector with every type of ship part using the loader.
		/// </summary>
		void fillLibrary();

		/// <summary>
		/// Single instance of the PartsLibrary.
		/// </summary>
		static PartsLibarary* instance;

		/// <summary>
		/// A vector of ShipPart vectors, each specific ShipPart type Vector being accessable using the PartType enum.
		/// </summary>
		std::vector<std::vector<ShipPart>> m_parts = { std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>() };
		
};

