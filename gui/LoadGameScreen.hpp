//
// Created by Owen EXALL on 2017/08/15.
//

#ifndef BOMBERMAN_LOADGAME_HPP
#define BOMBERMAN_LOADGAME_HPP

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class LoadGameScreen {
		public:
			LoadGameScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player);

			~LoadGameScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			LoadGameScreen();

			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
		};
	}
}


#endif //BOMBERMAN_LOADGAME_HPP
