#include "NPC/Actors/Animator.h"

Animator::Animator(std::string t_texturesPathBase, std::vector<std::string> t_animationFolderNames, sf::Sprite& t_sprite,  sf::Vector2f t_spriteOrigin ) : 
	m_sprite(t_sprite)
{
	Loader* loader = Loader::getInstance();
	

	for (int i = 0; i < t_animationFolderNames.size(); i++)
	{
		m_animations.push_back(loader->loadAllTexturesInFile(t_texturesPathBase + t_animationFolderNames[i]));
	}


	// default to first first frame to start
	m_sprite.setTexture(m_animations[0].m_sprites[0]->texture);

	m_sprite.setOrigin(t_spriteOrigin);
}

bool Animator::animate()
{

	m_elapsedTime++;

	if (m_elapsedTime > m_elapseReset)
	{
		m_elapsedTime = 0;

		m_animations[m_currentState].m_currentFrame++;

	
		if (m_animations[m_currentState].m_currentFrame >= m_animations[m_currentState].m_maxFrames)
		{
			
			if (m_assignLasFrame)
			{
				m_animations[m_currentState].m_currentFrame = 0;
				m_sprite.setTexture(m_animations[m_currentState].m_sprites[m_animations[m_currentState].m_currentFrame]->texture);
			}
			
			
			return true; // animation finished a loop

		}
	}

	m_sprite.setTexture(m_animations[m_currentState].m_sprites[m_animations[m_currentState].m_currentFrame]->texture);

	return false; // animation not finished a loop
}

bool Animator::onLastFrame()
{
	return m_animations[m_currentState].m_currentFrame ==m_animations[m_currentState].m_maxFrames - 1;
}


