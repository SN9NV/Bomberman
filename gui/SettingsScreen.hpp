//
// Created by Owen EXALL on 2017/08/15.
//

#ifndef BOMBERMAN_SETTINGSSCREEN_HPP
#define BOMBERMAN_SETTINGSSCREEN_HPP

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>
#include "CustomButton.hpp"
#include "../io/audio/AudioSource.hpp"

namespace cge {
	namespace GUI {
		class SettingsScreen {
		public:
			SettingsScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, cge::Loader& loader);

			~SettingsScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			SettingsScreen();

			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
			cge::Audio::Source _audioMenuScroll;
		};
	};
};


#endif //BOMBERMAN_SETTINGSSCREEN_HPP
