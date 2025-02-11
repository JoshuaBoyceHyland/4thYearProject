#include "Job.h"

Job::Job(std::string t_name, sf::Vector2f t_position) : m_name(t_name), m_position( t_position)
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/nulshock.otf");

	m_text.setString(t_name);
	m_text.setFont((*m_font));
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50);
	m_text.setPosition(m_position);

}

void Job::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_text);
}
