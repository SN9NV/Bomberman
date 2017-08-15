//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUIMANAGER_HPP
#define BOMBERMAN_GUIMANAGER_HPP

#include "../io/Window.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "MainMenuScreen.hpp"
#include "SettingsScreen.hpp"

namespace cge {
	class GuiManager {
	public:
		static bool			initialise(cge::Window& ,
										cge::GameState* state,
										Player* player);
		explicit GuiManager(cge::Window& win,
							cge::GameState* state,
							Player* player);

		static GuiManager*	getSingleton();

		~GuiManager();

		void drawScreen(int screen);

	private:
		static cge::GuiManager*		s_instance;

		cge::GameState*				_state;
		cge::Window&				_window;
		Player*						_player;

		cge::GUI::MainMenuScreen*	_mainMenuScreen;
		cge::GUI::SettingsScreen*	_settingsScreen;
	};
}


#endif //BOMBERMAN_GUIMANAGER_HPP
