//
// Created by owen on 2017/08/10.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include "../io/Window.hpp"
#include "../shared.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class MainMenuScreen {
		public:
			MainMenuScreen();
			MainMenuScreen(cge::Window& win, cge::GameState* _currState);
			~MainMenuScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
		private:
			nanogui::Screen* 	_screen;
			cge::Window&		_window;
		};
	}
}


#endif //BOMBERMAN_MAINMENUSCREEN_HPP
