#pragma once
#include "Scene.h"
#include "EditorMouse.h"
#include "PartsLibarary.h"
#include "UIEditorBox.h"
#include "UIScreenBorder.h"

/// <summary>
/// Class for
/// </summary>
class EditorScene : public Scene
{
	public:

		/// <summary>
		/// constructor for Editor scene
		/// Updates the mouses vector of scene parts
		/// </summary>
		/// <param name="t_window">Assigns to our reference so we can draw to the main window</param>
		EditorScene(sf::RenderWindow& t_window );

		/// <summary>
		/// Updates our objects in the scene
		/// </summary>
		/// <param name="t_deltaTime"></param>
		virtual void update(sf::Time t_deltaTime) override;

		/// <summary>
		/// Renders all objects
		/// </summary>
		virtual void render() override;

		/// <summary>
		/// Handles Key presses
		/// </summary>
		/// <param name="t_event">Key Press Event</param>
		virtual void processKeys(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do with on mouse press
		/// </summary>
		/// <param name="t_event">Mouse Press Event</param>
		virtual void processMousePress(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do with mouse release event
		/// </summary>
		/// <param name="t_event">Mouse release event</param>
		virtual void processMouseRelease(sf::Event t_event) override;

		/// <summary>
		/// Handles what to do withe a mouse move event
		/// </summary>
		/// <param name="t_event">Mouse move event</param>
		virtual void processMouseMove(sf::Event t_event) override;


	private: 
		/// <summary>
		/// Vector of all parts in the scene
		/// </summary>
		std::vector<ShipPart*> m_parts; 
		/// <summary>
		/// Editor mouse for the scene
		/// </summary>
		EditorMouse m_mouse;
		/// <summary>
		///  Ui for this scene
		/// </summary>
		UIEditorBox m_ui;

		UIScreenBorder m_uiBorder;
};

