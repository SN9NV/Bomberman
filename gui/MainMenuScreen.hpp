//
// Created by owen on 2017/08/10.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include "../io/Window.hpp"
#include <nanogui/nanogui.h>

namespace cge {
	namespace GUI {
		class MainMenuScreen {
		public:
			MainMenuScreen(cge::Window& win);
			~MainMenuScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
		private:
			nanogui::Screen* 	screen;
			cge::Window&		_window;
		};
	}
}


#endif //BOMBERMAN_MAINMENUSCREEN_HPP
