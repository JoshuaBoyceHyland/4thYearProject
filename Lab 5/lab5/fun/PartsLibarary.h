#pragma once
#include "Loader.h"
#include "ShipPart.h"

class PartsLibarary
{
	public:
		PartsLibarary(const PartsLibarary& other) = delete;

		static PartsLibarary* getInstance();

		ShipPart getShipPart(int t_index);
	private:

		PartsLibarary();

		void initialiseVectors();

		static PartsLibarary* instance;

		const int NUM_OF_EACH_PART = 2;

		std::vector<ShipPart> m_thrusters;
		std::vector<ShipPart> m_cockpits;
		std::vector<ShipPart> m_hulls;
		std::vector<ShipPart> m_leftWings;
		std::vector<ShipPart> m_rightWings;
};

