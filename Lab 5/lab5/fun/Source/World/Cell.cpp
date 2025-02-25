#include "World/Cell.h"

Cell::Cell( float t_width, float t_height, int t_row, int t_column, sf::Vector2f t_position ) :
	m_row(t_row),
	m_column(t_column),
	m_node(t_row, t_column, t_position)
{
	m_body.setPosition(t_position);
	m_body.setSize({t_width, t_height});
	m_body.setFillColor(sf::Color::Transparent);
	m_body.setOutlineColor(sf::Color::Blue);
	m_body.setOutlineThickness(2.5);
	m_body.setOrigin({ t_width / 2, t_height / 2 });
	m_property = TraversalProperty::Unwalkable;

	setUpText();
}

Cell::Cell(const Cell& t_other, bool t_copyPosition = true) : m_node(t_other.m_node)
{
		m_body = t_other.m_body;
		m_row = t_other.m_row;
		m_column = t_other.m_column;
		m_textActive = t_other.m_textActive;
		m_occupied = t_other.m_occupied;
		m_property = t_other.m_property;
		m_texture = t_other.m_texture;
		m_font = t_other.m_font;
		m_text = t_other.m_text;

		if (m_texture != nullptr)
		{
			m_body.setTexture(&(*m_texture).texture);
		}

		m_text.setFont((*m_font));

		if (t_copyPosition)
		{
			m_position = t_other.m_body.getPosition();
			m_body.setPosition(t_other.m_position);
		}
		else {
			m_position = m_position;
			m_body.setPosition(m_position);
		}
}

void Cell::reset()
{
	m_property = TraversalProperty::Unwalkable;
	m_texture = nullptr;
	m_occupied = false;
	m_body.setFillColor(sf::Color::Black);
	m_body.setOutlineThickness(2.5f);
	m_body.setTexture(nullptr);
	m_text.setString(m_cellPropertyString[m_property]);

}

//Cell::Cell(const Cell& t_other)
//{
//	m_body = t_other.m_body;
//	m_position = t_other.m_position;
//	m_property = t_other.m_property;
//	m_text = t_other.m_text;
//	m_texture = t_other.m_texture;
//	m_font = t_other.m_font;
//
//	if (m_texture != nullptr)
//	{
//		m_body.setTexture(&(*m_texture).texture);
//	}
//
//	m_text.setFont((*m_font));
//	
//}


void Cell::draw(sf::RenderWindow& t_window)
{


	t_window.draw(m_body);

	if (m_cellJob != nullptr)
	{
		m_cellJob->draw(t_window);
	}

	if (m_textActive)
	{
		t_window.draw(m_text);
	}

	
	
}

void Cell::outlineEnabled(bool t_enable)
{
	if (t_enable)
	{
		m_body.setOutlineThickness(1.0f);
	}
	else
	{
		m_body.setOutlineThickness(0.0f);
	}
}

void Cell::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_body.setPosition(m_position);

	if (m_cellJob != nullptr)
	{
		m_cellJob->setPosition(m_position);
	}
	
}

void Cell::setTexture(Texture* t_texture)
{
	
	m_texture = t_texture;
	
	if (t_texture != nullptr)
	{
		m_body.setTexture(&(*m_texture).texture);
	}
	else
	{
		m_body.setTexture(nullptr);
	}

	m_body.setOutlineThickness(0.0f);
}

void Cell::setProperty(TraversalProperty t_property)
{
	m_occupied = true;
	m_property = t_property;
	m_text.setString(m_cellPropertyString[m_property]);
}

void Cell::project(Texture* t_texture)
{
	m_body.setTexture(&t_texture->texture);
	m_body.setFillColor(sf::Color::White);
	m_body.setOutlineThickness(0.0f);
}

void Cell::project(WorldItem* t_job)
{
	//m_cellJob->m_sprite.setTexture( t_job->getTexture()->texture);
}

void Cell::resetTexture()
{
	if (m_texture != nullptr)
	{
		m_body.setTexture(&m_texture->texture);
		m_body.setFillColor(sf::Color::White);
		m_body.setOutlineThickness(0.0f);
		
	}
	else
	{
		m_body.setTexture(nullptr);
		m_body.setFillColor(sf::Color::Black);
		m_body.setOutlineThickness(2.50f);
	}
}

void Cell::debug(bool t_debug)
{
	if (t_debug)
	{
		m_text.setString(	"M: " + std::to_string(m_node.getManhattan()) + "\n" +
							"E: " + std::to_string(m_node.getEudclidian()) + "\n" +
							"H: " + std::to_string(m_node.getHeurisitic())
						);

		/*m_text.setString("Row: " + std::to_string(m_row) + "\n" +
			" Column: " + std::to_string(m_column)
		);*/
		m_body.setOutlineThickness(1.0f);
	}
	else
	{
		m_text.setString("");
		m_body.setOutlineThickness(0.0f);
	}
	
}

void Cell::setUpText()
{
	Loader* loader = Loader::getInstance();

	m_font = loader->loadFont("ASSETS/FONTS/ariblk.ttf");

	m_text.setFont((*m_font));
	m_text.setPosition({ m_body.getPosition().x  - m_body.getSize().x /2,  m_body.getPosition().y - m_body.getSize().x / 2 });
	m_text.setFillColor(sf::Color::Black);
	m_text.setOutlineColor(sf::Color::Yellow);
	m_text.setOutlineThickness(1.0f);
	m_text.setCharacterSize(m_body.getSize().x * 0.15f);

	m_text.setString(m_cellPropertyString[m_property]);
}
