#pragma once
#include "Scene.h"
#include "GameData.h"
#include "World/Grid.h"
#include "MovableCamera.h"
#include "NPC/BaseNPC.h"
#include "BasePlayer.h"
#include "Utility/MapSaver.h"
/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>
class BaseGameplayScene : public Scene
{

	public :
		BaseGameplayScene(sf::RenderWindow& t_window);

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;

	private:
		Grid* m_grid;
		BasePlayer* m_player;
		MovableCamera m_camera;
		std::vector<NPC*> m_npc;
		MapSaver saver;
		std::vector<WorldItem*> jobs;
};

