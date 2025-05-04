#pragma once
#include "NPC/NPC.h"
#include "Scene.h"
#include "MovableCamera.h"
#include "BasePlayer.h"
#include "DungeonGeneration/DungeonGeneration.h"
#include "MiniMap.h"
class GeneratedDungionNPCTestScene : public Scene
{
	
	public:
		GeneratedDungionNPCTestScene(sf::RenderWindow& t_window);

		void update(sf::Time t_deltaTime) override;
		void render() override;
		void processKeys(sf::Event t_event) override;
		void processMousePress(sf::Event t_event) override;
		void processMouseRelease(sf::Event t_event) override;
		void processMouseMove(sf::Event t_event) override;
		void processMouseWheel(sf::Event t_event) override;


	private:

		Cell* prev;
		BasePlayer* m_player;
		std::vector<NPC*> m_npc;
		Grid* m_dungeon;
		MovableCamera m_camera;


		DungeonGeneration m_dungeonGenerator;
		/*std::unique_ptr<*/MiniMap*/*>*/ m_minimap;
		
};

