//
// Created by owen on 2017/08/08.
//

#ifndef BOMBERMAN_LOADGAMESCREEN_HPP
#define BOMBERMAN_LOADGAMESCREEN_HPP

#include "../io/Window.hpp"
#include "../sounds/Sounds.hpp"
#include "../shared.hpp"
#include "GUI.hpp"

#define SAVE_GAMES_PATH "./resources/saves"

namespace cge {
	class LoadGameScreen {
	public:
		LoadGameScreen(cge::Window& win, int *gameState, cge::Sounds* snds);;

		~LoadGameScreen();

		void DrawScreen();

	private:
		LoadGameScreen();

		int*				_gameState;
		cge::Sounds*		_sounds;
		cge::Window&		_sdlWindow;
		cge::GUI			_gui;

		void				_processInput(void);
		void				_initUI(void);
		void				_registerHandlers(void);

		void				_getSavedGames(void);

		CEGUI::PushButton* 	btn_MainMenu;
		CEGUI::PushButton* 	btn_LoadGame;
		CEGUI::Listbox*		lb_SavedGames;

		bool				btn_All_EnterArea(const CEGUI::EventArgs& e);
		bool				btn_MainMenu_Clicked(const CEGUI::EventArgs& e);
		bool				btn_LoadGame_Clicked(const CEGUI::EventArgs& e);
	};
}


#endif //BOMBERMAN_LOADGAMESCREEN_HPP
