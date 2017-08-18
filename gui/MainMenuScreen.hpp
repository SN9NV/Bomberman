//
// Created by owen on 2017/08/10.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "../io/audio/AudioDevice.hpp"
#include "CustomButton.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class MainMenuScreen {
		public:
			MainMenuScreen(cge::Window& win,
						   cge::GameState* _currState,
						   cge::GameState* prevState,
						   Player *player,
						   int* currMap,
						   cge::Loader& _loader);
			~MainMenuScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
		private:
			MainMenuScreen();

			nanogui::Screen* 	_screen;
			cge::Window&		_window;
			Player*				_player;
			cge::Audio::Source	_audioMouseEnter;
		};
	}
}


#endif //BOMBERMAN_MAINMENUSCREEN_HPP
