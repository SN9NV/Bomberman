//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_PAUSEGAMESCREEN_H
#define BOMBERMAN_PAUSEGAMESCREEN_H

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class PauseGameScreen {
		public:
			PauseGameScreen(cge::Window& win, cge::GameState* _currState, cge::GameState* prevState, Player *player, int* currMap);
			~PauseGameScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
		private:
			PauseGameScreen();

			nanogui::Screen* 	_screen;
			cge::Window&		_window;
			Player*				_player;
		};
	}
};


#endif //BOMBERMAN_PAUSEGAMESCREEN_H
