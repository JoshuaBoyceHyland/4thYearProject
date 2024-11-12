#pragma once
#include "Loader.h"
#include "ShipPart.h"

class PartsLibarary
{
	public:
		PartsLibarary(const PartsLibarary& other) = delete;

		static PartsLibarary* getInstance();
		

		ShipPart* getCockpit(int t_index);
		ShipPart* getHullPart(int t_index);
		ShipPart* getGetThruster(int t_index);
		ShipPart* getLeftWing(int t_index);
		ShipPart* getRightWing(int t_index);
		ShipPart* getPart(PartType t_type, int t_index);


		static const int NUM_OF_EACH_PART = 2;
	private:

		PartsLibarary();

		void initialiseVectors();

		static PartsLibarary* instance;

		
		std::vector<std::vector<ShipPart>> m_parts = { std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>(), std::vector<ShipPart>() };
		
		std::vector<ShipPart> m_cockpits;
		std::vector<ShipPart> m_hulls;
		std::vector<ShipPart> m_thrusters;
		std::vector<ShipPart> m_leftWings;
		std::vector<ShipPart> m_rightWings;
};

