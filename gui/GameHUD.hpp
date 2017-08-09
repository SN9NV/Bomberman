//
// Created by owen on 2017/08/09.
//

#ifndef BOMBERMAN_GAMEHUD_HPP
#define BOMBERMAN_GAMEHUD_HPP

#include "../io/Window.hpp"
#include "../sounds/Sounds.hpp"
#include "../shared.hpp"
#include "GUI.hpp"
#include "../io/InputManager.hpp"

namespace cge {
	class GameHUD {
	public:
		GameHUD(cge::Window& win, int *gameState, int* prevState, cge::Sounds* snds, cge::InputManager* manager);;

		~GameHUD();

		void DrawScreen();

	private:
		GameHUD();

		int*				_prevGameState;
		int*				_gameState;
		cge::InputManager*	_inputManager;
		cge::Sounds*		_sounds;
		cge::Window&		_sdlWindow;
		cge::GUI			_gui;

		void				_initUI(void);
		void				_registerHandlers(void);

		CEGUI::PushButton*	btn_SaveGame;
		CEGUI::PushButton*	btn_LoadGame;
		CEGUI::PushButton*	btn_Options;
		CEGUI::PushButton*	btn_MainMenu;

		bool 				btn_All_AreaEntered(const CEGUI::EventArgs& e);
		bool				btn_SaveGame_Clicked(const CEGUI::EventArgs& e);
		bool				btn_LoadGame_Clicked(const CEGUI::EventArgs& e);
		bool				btn_Options_Clicked(const CEGUI::EventArgs& e);
		bool 				btn_MainMenu_Clicked(const CEGUI::EventArgs& e);
	};
};


#endif //BOMBERMAN_GAMEHUD_HPP
