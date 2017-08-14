//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUIMANAGER_HPP
#define BOMBERMAN_GUIMANAGER_HPP

#include "../io/Window.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "MainMenuScreen.hpp"

namespace cge {
	class GuiManager {
	public:
		static bool			initialise(cge::Window& ,
										cge::GameState* state,
										Player* player);
		static GuiManager*	getSingleton();

		explicit GuiManager(cge::Window& win,
							Player* player);
		~GuiManager();

		void drawScreen(int screen);

	private:
		static cge::GuiManager*		s_instance;

		cge::Window&				_window;
		Player*						_player;

		cge::GUI::MainMenuScreen*	_mainMenuScreen;
		void 						setMainMenuScreen(cge::GUI::MainMenuScreen*	mainMenuScreen);
	};
}


#endif //BOMBERMAN_GUIMANAGER_HPP
