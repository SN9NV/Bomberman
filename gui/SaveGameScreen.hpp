//
// Created by owen on 2017/08/09.
//

#ifndef BOMBERMAN_SAVEGAMESCREEN_HPP
#define BOMBERMAN_SAVEGAMESCREEN_HPP

#include "../io/Window.hpp"
#include "../sounds/Sounds.hpp"
#include "GUI.hpp"
#include "../shared.hpp"
#include "LoadGameScreen.hpp"
#include <dirent.h>

namespace cge {
	class SaveGameScreen {
	public:
		SaveGameScreen(cge::Window& win, int *gameState, cge::Sounds* snds);;

		~SaveGameScreen();

		void DrawScreen();

	private:
		SaveGameScreen();

		int*				_gameState;
		cge::Sounds*		_sounds;
		cge::Window&		_sdlWindow;
		cge::GUI			_gui;

		void				_processInput(void);
		void				_initUI(void);
		void				_registerHandlers(void);

		void				_getSavedGames(void);

		CEGUI::Editbox*		txtb_SaveGame;
		CEGUI::PushButton* 	btn_MainMenu;
		CEGUI::PushButton* 	btn_SaveGame;
		CEGUI::Listbox*		lb_SavedGames;

		bool				btn_All_EnterArea(const CEGUI::EventArgs& e);
		bool				btn_MainMenu_Clicked(const CEGUI::EventArgs& e);
		bool				btn_SaveGame_Clicked(const CEGUI::EventArgs& e);
	};
}


#endif //BOMBERMAN_SAVEGAMESCREEN_HPP
