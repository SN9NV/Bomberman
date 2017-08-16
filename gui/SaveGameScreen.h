//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_SAVEGAMESCREEN_H
#define BOMBERMAN_SAVEGAMESCREEN_H

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class SaveGameScreen {
		public:
			SaveGameScreen(cge::Window
			&win,
			cge::GameState *_currState, Player
			*player);

			~SaveGameScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			SaveGameScreen();

			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
		};
	};
};


#endif //BOMBERMAN_SAVEGAMESCREEN_H
