#include "Job.h"

Job::Job(Texture* t_texture)
{
	setTexture(t_texture);

	m_sprite.setOrigin(t_texture->texture.getSize().x / 2, t_texture->texture.getSize().y );
	m_sprite.setPosition(0,0);
}

Job::Job(std::string t_name, sf::Vector2f t_position) : m_name(t_name)
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/nulshock.otf");

	m_text.setString(t_name);
	m_text.setFont((*m_font));
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);

}

void Job::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_sprite);
}

void Job::setTexture(Texture* t_texture)
{
	m_texture = t_texture;
	m_sprite.setTexture(t_texture->texture);
}
