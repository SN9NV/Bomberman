//
// Created by owen on 2017/08/10.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include <nanogui/nanogui.h>

#include "CustomButton.hpp"

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "../io/audio/AudioDevice.hpp"
#include "../io/settings/Settings.hpp"

namespace cge {
	namespace GUI {
		class MainMenuScreen {
		public:
			MainMenuScreen() = delete;
			MainMenuScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, int *currMap, cge::Loader &loader);
			MainMenuScreen(const MainMenuScreen &cpy);
			MainMenuScreen operator=(const MainMenuScreen &rhs);
			~MainMenuScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
			void ReinitializeScreen();

		private:
			cge::Window			&_window;

			nanogui::Screen		*_screen;
			Player				*_player;
			cge::Audio::Source	_audioMouseEnter;

			nanogui::ref<nanogui::Window> nanoguiWindow;
		};
	}
}

#endif //BOMBERMAN_MAINMENUSCREEN_HPP
