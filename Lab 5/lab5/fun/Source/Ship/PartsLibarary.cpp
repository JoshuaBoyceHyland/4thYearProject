#include "Ship/PartsLibarary.h"

PartsLibarary* PartsLibarary::instance = nullptr;

PartsLibarary::PartsLibarary()
{
	fillLibrary();
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
	return &m_parts[static_cast<int>(PartType::CockPit)][t_index];
}

ShipPart* PartsLibarary::getHullPart(int t_index)
{
	return &m_parts[static_cast<int>(PartType::Hull)][t_index];
}

ShipPart* PartsLibarary::getGetThruster(int t_index)
{
	return &m_parts[static_cast<int>(PartType::Thruster)][t_index];
}

ShipPart* PartsLibarary::getLeftWing(int t_index)
{
	return &m_parts[static_cast<int>(PartType::Left_Wing)][t_index];
}

ShipPart* PartsLibarary::getRightWing(int t_index)
{
	return &m_parts[static_cast<int>(PartType::Right_Wing)][t_index];
}

ShipPart* PartsLibarary::getPart(PartType t_type, int t_index)
{
	return &m_parts[static_cast<int>(t_type)][t_index];
}

void PartsLibarary::fillLibrary()
{


	Loader* loader = Loader::getInstance();

	std::string basePath = "ASSETS/IMAGES/";
	std::string hullPath = "hulls/hull_";
	std::string cockpitPath = "cockpits/cockpit_";
	std::string thrusterPath = "thrusters/thruster_";
	std::string leftWingPath = "left_wings/left_wing_";
	std::string rightWingPath = "right_wings/right_wing_";

	sf::Vector2f pos = {100, 100 };
	Texture* texture;

	for (int i = 0; i < NUM_OF_EACH_PART; i++)
	{
		

		texture = loader->loadTexture(basePath + cockpitPath + std::to_string(i + 1) + ".png");
		texture->id = i;
		m_parts[static_cast<int>(PartType::CockPit)].emplace_back(ShipPart(texture, PartType::CockPit, pos));
		pos.y += 100;

		texture = loader->loadTexture(basePath + hullPath + std::to_string(i + 1) + ".png");
		texture->id = i;
		m_parts[static_cast<int>(PartType::Hull)].emplace_back(ShipPart( texture, PartType::Hull, pos));
		pos.y += 100;

		texture = loader->loadTexture(basePath + thrusterPath + std::to_string(i + 1) + ".png");
		texture->id = i;
		m_parts[static_cast<int>(PartType::Thruster)].emplace_back(ShipPart(texture, PartType::Thruster, pos));
		pos.y += 100;

		texture = loader->loadTexture(basePath + leftWingPath + std::to_string(i + 1) + ".png");
		texture->id = i;
		m_parts[static_cast<int>(PartType::Left_Wing)].emplace_back(ShipPart(texture, PartType::Left_Wing, pos));
		pos.y += 100;

		texture = loader->loadTexture(basePath + rightWingPath + std::to_string(i + 1) + ".png");
		texture->id = i;
		m_parts[static_cast<int>(PartType::Right_Wing)].emplace_back(ShipPart(texture, PartType::Right_Wing, pos));
		pos.y += 100;

	}

}
