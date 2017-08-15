//
// Created by Owen EXALL on 2017/08/15.
//

#ifndef BOMBERMAN_SETTINGSSCREEN_HPP
#define BOMBERMAN_SETTINGSSCREEN_HPP

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class SettingsScreen {
		public:
			SettingsScreen(cge::Window &win, cge::GameState *_currState, Player *player);

			~SettingsScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			SettingsScreen();

			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
		};
	};
};


#endif //BOMBERMAN_SETTINGSSCREEN_HPP
