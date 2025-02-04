#include "World/Tile.h"

Tile::Tile(Texture* t_texture, float t_width, float t_height)
{
	m_cells.push_back({ t_width,t_height });
	m_textures.push_back(t_texture);
	m_cells[0].setColor(sf::Color::White);
	m_cells[0].setTexture(t_texture);
}

Tile::Tile(std::vector<Texture*> t_texture, float t_width, float t_height, int t_rows, int t_colums) :m_textures(t_texture)
{


}

void Tile::draw(sf::RenderWindow& t_window)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].draw(t_window);
	}
}

void Tile::setPosition(sf::Vector2f t_position)
{
	for (int i = 0; i < m_cells.size(); i++)
	{
		m_cells[i].setPosition(t_position);
	}
}
