//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUIMANAGER_HPP
#define BOMBERMAN_GUIMANAGER_HPP

#include "../io/Window.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "MainMenuScreen.hpp"
#include "SettingsScreen.hpp"
#include "LoadGameScreen.hpp"
#include "SaveGameScreen.h"
#include "PauseGameScreen.h"

namespace cge {
	class GuiManager {
	public:
		static bool			initialise(cge::Window& ,
										cge::GameState* state,
										cge::GameState *prevState,
										Player* player);
		explicit GuiManager(cge::Window& win,
							cge::GameState* state,
							cge::GameState *prevState,
							Player* player);

		static GuiManager*	getSingleton();

		~GuiManager();

		void drawScreen(int screen);

	private:
		static cge::GuiManager*		s_instance;

		cge::GameState*				_prevState;
		cge::GameState*				_state;
		cge::Window&				_window;
		Player*						_player;

		cge::GUI::MainMenuScreen*	_mainMenuScreen;
		cge::GUI::SettingsScreen*	_settingsScreen;
		cge::GUI::LoadGameScreen*	_loadGameScreen;
		cge::GUI::SaveGameScreen*	_saveGameScreen;
		cge::GUI::PauseGameScreen*	_pauseGameScreen;
	};
}


#endif //BOMBERMAN_GUIMANAGER_HPP
