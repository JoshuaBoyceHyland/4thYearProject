#pragma once
#include "GameData.h"
#include "NPC/NPC.h"
#include "Scenes/Scene.h"
#include "MovableCamera.h"
#include "BasePlayer.h"
#include "DungeonGeneration/DungeonGeneration.h"
#include "MiniMap.h"
class EnemyBaseScene : public Scene
{

public:
	EnemyBaseScene(sf::RenderWindow& t_window, std::function<void(SceneType)> t_sceneChangeFunction);

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
	Dungeon* m_dungeon;
	MovableCamera m_camera;
	Ship* m_ship;


	/*std::unique_ptr<*/MiniMap*/*>*/ m_minimap;
	std::function<void(SceneType)> m_sceneChangeFunction;
};

