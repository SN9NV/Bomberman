//
// Created by owen on 2017/08/10.
//

#ifndef BOMBERMAN_MAINMENUSCREEN_HPP
#define BOMBERMAN_MAINMENUSCREEN_HPP

#include "../io/Window.hpp"
#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/entypo.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/graph.h>
#include <nanogui/formhelper.h>

namespace cge {
	namespace GUI {
		class MainMenuScreen {
		public:
			MainMenuScreen(cge::Window& win);
			~MainMenuScreen();

			void drawScreen();
		private:
			nanogui::Screen* screen;
		};
	}
}


#endif //BOMBERMAN_MAINMENUSCREEN_HPP
