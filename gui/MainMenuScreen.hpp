//
// Created by owen on 2017/08/08.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include "../io/Window.hpp"
#include "../sounds/Sounds.hpp"
#include "GUI.hpp"
#include "../shared.hpp"
#include "../rendering/GLSLProgram.hpp"
#include "../io/InputManager.hpp"
#include "../loaders/Loader.hpp"
#include "../rendering/Renderer.hpp"
#include "../entites/Camera.hpp"

namespace cge {
	class MainMenuScreen {
	public:
		MainMenuScreen(cge::Window& win, int *gameState, int* prevState, cge::Sounds* snds);
		~MainMenuScreen();

		void				DrawScreen(cge::Entity& bomberman);
	private:
		MainMenuScreen();

		int*				_prevGameState;
		int*				_gameState;
		cge::Sounds*		_sounds;
		cge::Window&		_sdlWindow;
		cge::GUI			_gui;

		void				_processInput(void);
		void				_initUI(void);
		void				_registerHandlers(void);

		cge::GLSLProgram*	shader;
		cge::Renderer*		renderer;
		cge::Loader*		loader;
		cge::Camera*		camera;
		cge::Model*			bomberModel;

		CEGUI::PushButton*	btn_NewGame;
		CEGUI::PushButton*	btn_LoadGame;
		CEGUI::PushButton*	btn_Options;
		CEGUI::PushButton*	btn_Quit;

		bool				btn_All_EnterArea(const CEGUI::EventArgs& e);
		bool 				btn_Quit_Clicked(const CEGUI::EventArgs& e);
		bool				btn_NewGame_Clicked(const CEGUI::EventArgs& e);
		bool 				btn_LoadGame_Clicked(const CEGUI::EventArgs& e);
		bool				btn_Options_Clicked(const CEGUI::EventArgs& e);
	};
}


#endif //BOMBERMAN_MAINMENUSCREEN_HPP
