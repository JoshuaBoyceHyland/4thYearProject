#include "Player.h"

Player::Player(sf::Vector2f t_position) :
m_position( t_position ), 
bod("ASSETS/IMAGES/texture.jpg"), 
pit("ASSETS/IMAGES/texture.jpg")
{
	if (!m_spriteTexture.loadFromFile("ASSETS/IMAGES/ship.png"));
	{
		std::cout << "Cannot load file" << std::endl;
	}
	
	m_body.setTexture(m_spriteTexture); 
	m_body.setScale({ 0.25f, 0.25f });
	m_body.setOrigin({ static_cast<float>(m_spriteTexture.getSize().x/2) ,static_cast<float>(m_spriteTexture.getSize().y / 2 )});
}

void Player::update( float deltaTime )
{
	input();


	float radian = (m_rotation + 270.0f) * (3.14159265359f / 180.0f);
	m_velocity.x = std::cos(radian ) * m_speed * (deltaTime / 1000);
	m_velocity.y = std::sin(radian) * m_speed * (deltaTime / 1000);

	m_position += m_velocity;

	bod.setPostion(m_position);
	bod.setRotation(m_rotation);


	pit.setPostion( m_position + pit.getConnectionPount(2) +  bod.getConnectionPount(2));
	pit.setRotation(m_rotation);

	m_body.setPosition(m_position);
	m_body.setRotation(m_rotation);
	
	m_speed *= 0.99f;

	bod.update();
	pit.update();

}

void Player::draw(sf::RenderWindow& t_window)
{
	bod.draw(t_window);
	pit.draw(t_window);
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

void Player::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 4;
	}
	boundCheck();
}

void Player::boundCheck()
{

	if (m_position.x > 1280)
	{
		m_position.x = 0;
	}
	else if (m_position.x < 0)
	{
		m_position.x = 1280;
	}

	if (m_position.y > 720)
	{
		m_position.y = 0; 
	}
	else if (m_position.y < 0)
	{
		
		m_position.y = 720;
	}
}
