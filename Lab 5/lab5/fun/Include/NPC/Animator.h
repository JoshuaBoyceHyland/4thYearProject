#pragma once
#include <SFML/Graphics.hpp>

#include "Librarys/Loader.h"

enum class SpriteState { Idle, Run, Dead };


struct Animation
{
	public:
	
		Animation(std::vector<Texture*> t_sprites) : m_sprites(t_sprites), m_maxFrames(t_sprites.size()) {}

		
		int m_currentFrame = 0;
		int m_maxFrames = 1;
		std::vector<Texture*> m_sprites;

};

class Animator
{

	public:
		Animator(std::string t_texturesPath);

		sf::Sprite m_sprite;

		void animate();
		int m_currentState = 0;


	private:

		int m_elapsedTime = 0;
		int m_elapseReset = 8;
		std::vector<Animation> m_animations;


	
};

