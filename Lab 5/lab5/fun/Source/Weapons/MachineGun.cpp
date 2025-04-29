#include "Weapons/MachineGun.h"

MachineGun::MachineGun(sf::Vector2f& t_holdPoint) :
	Weapon( t_holdPoint), 
	m_animator("ASSETS/IMAGES/Weapons", { "/MachineGun" }, m_body, { 18,19 })
{
	
}

void MachineGun::update()
{

	
	m_body.setPosition(m_holdingPoint);

	if (m_firing)
	{

		if (m_animator.animate())
		{
			m_firing = false;
		}
	}
	
}

void MachineGun::startShot()
{
	if (!m_firing)
	{
		m_firing = true;
	}
	
}

void MachineGun::draw(sf::RenderWindow& t_window)
{
	sf::CircleShape t(5);
	t.setPosition(m_animator.m_sprite.getPosition());
	t.setOrigin({ 5,5 });
	t.setFillColor(sf::Color::Cyan);


	t_window.draw(t);
	t_window.draw(m_animator.m_sprite);
}

