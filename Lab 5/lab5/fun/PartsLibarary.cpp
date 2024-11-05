#include "PartsLibarary.h"

PartsLibarary* PartsLibarary::instance = nullptr;

PartsLibarary::PartsLibarary()
{
	initialiseVectors();
}

PartsLibarary* PartsLibarary::getInstance()
{
	if (instance == nullptr)
	{
		instance = new PartsLibarary();
	}
	return instance;
}

ShipPart PartsLibarary::getShipPart(int t_index)
{
	return m_hulls[t_index];
}

void PartsLibarary::initialiseVectors()
{
	Loader* loader = Loader::getInstance();

	std::string basePath = "ASSETS/IMAGES/";
	std::string hullPath = "hulls/hull_";
	std::string cockpitPath = "cockpits/cockpit_";
	std::string thrusterPath = "thrusters/thruster_";
	std::string leftWingPath = "left_wings/left_wing_";
	std::string rightWingPath = "right_wings/right_wing_";

	sf::Vector2f pos = { 500, 500 };
	sf::Texture* texture;

	for (int i = 0; i < NUM_OF_EACH_PART; i++)
	{
		texture = loader->loadTexture(basePath + cockpitPath + std::to_string(i) + "png");
		m_cockpits.emplace_back(ShipPart(texture, PartType::CockPit, pos));

		texture = loader->loadTexture(basePath + hullPath + std::to_string(i) + "png");
		m_hulls.emplace_back(ShipPart( texture, PartType::Hull, pos));

		texture = loader->loadTexture(basePath + thrusterPath + std::to_string(i) + "png");
		m_thrusters.emplace_back(ShipPart(texture, PartType::Thruster, pos));

		texture = loader->loadTexture(basePath + leftWingPath + std::to_string(i) + "png");
		m_leftWings.emplace_back(ShipPart(texture, PartType::Left_Wing, pos));

		texture = loader->loadTexture(basePath + rightWingPath + std::to_string(i) + "png");
		m_rightWings.emplace_back(ShipPart(texture, PartType::Left_Wing, pos));


	}

}
