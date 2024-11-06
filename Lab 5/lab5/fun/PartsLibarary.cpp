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

ShipPart* PartsLibarary::getCockpit(int t_index)
{
	return &m_cockpits[t_index];
}

ShipPart* PartsLibarary::getHullPart(int t_index)
{
	return &m_hulls[t_index];
}

ShipPart* PartsLibarary::getGetThruster(int t_index)
{
	return &m_thrusters[t_index];
}

ShipPart* PartsLibarary::getLeftWing(int t_index)
{
	return &m_leftWings[t_index];
}

ShipPart* PartsLibarary::getRightWing(int t_index)
{
	return &m_rightWings[t_index];
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

	sf::Vector2f pos = {100, 100 };
	sf::Texture* texture;

	for (int i = 0; i < NUM_OF_EACH_PART; i++)
	{
		

		texture = loader->loadTexture(basePath + cockpitPath + std::to_string(i + 1) + ".png");
		m_cockpits.emplace_back(ShipPart(texture, PartType::CockPit, pos));

		pos.y += 100;
		texture = loader->loadTexture(basePath + hullPath + std::to_string(i + 1) + ".png");
		m_hulls.emplace_back(ShipPart( texture, PartType::Hull, pos));
		pos.y += 100;
		texture = loader->loadTexture(basePath + thrusterPath + std::to_string(i + 1) + ".png");
		m_thrusters.emplace_back(ShipPart(texture, PartType::Thruster, pos));
		pos.y += 100;
		texture = loader->loadTexture(basePath + leftWingPath + std::to_string(i + 1) + ".png");
		m_leftWings.emplace_back(ShipPart(texture, PartType::Left_Wing, pos));
		pos.y += 100;
		texture = loader->loadTexture(basePath + rightWingPath + std::to_string(i + 1) + ".png");
		m_rightWings.emplace_back(ShipPart(texture, PartType::Right_Wing, pos));
		pos.y += 100;


		//pos.x += 300;
		//pos.y = 100;
	}

}
