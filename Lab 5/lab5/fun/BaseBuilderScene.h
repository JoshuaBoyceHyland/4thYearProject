#pragma once
#include "Scene.h"
#include "Globals.h"
#include "VectorMath.h"
#include "MovableCamera.h"
#include "Job.h"
#include "Room.h"
//#include "Cell.h"
#include "Grid.h"
#include "BaseBuilderEditiorBox.h"

class BaseBuilderScene : public Scene
{
	public:
		BaseBuilderScene(sf::RenderWindow& t_window);

		// Inherited via Scene
		void update(sf::Time t_deltaTime) override;

		void render() override;

		void processKeys(sf::Event t_event) override;

		void processMousePress(sf::Event t_event) override;

		void processMouseRelease(sf::Event t_event) override;

		void processMouseMove(sf::Event t_event) override;

		void processMouseWheel(sf::Event t_event) override;

	private:


		sf::RectangleShape m_rect;

		MovableCamera m_camera;
		Job m_job;
		Room m_room;
		Grid m_grid;
		BaseBuilderEditiorBox m_editorBox;
};

