#include "Wings.h"

Wings::Wings(std::string t_texturePath, sf::ConvexShape t_body)
{
	setUpBody(t_texturePath);
	setUpConnectionPoints();
}

Wings::Wings(Attributes t_attributes, std::string t_texturePath)
{
}

void Wings::update()
{
}

void Wings::draw(sf::RenderWindow& t_window)
{
}

void Wings::setRotation(float t_rotation)
{
}

void Wings::setPostion(sf::Vector2f t_position)
{
}

sf::Vector2f Wings::getConnectionPount(int t_index)
{
	return sf::Vector2f();
}

void Wings::setUpBody(std::string t_texturePath)
{
}

void Wings::setUpConnectionPoints()
{
}
