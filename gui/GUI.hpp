//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUI_HPP
#define BOMBERMAN_GUI_HPP

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
#include <nanogui/tabwidget.h>
#include <nanogui/formhelper.h>

namespace cge {
	class GUI {
	public:
		GUI(cge::Window& win);
		~GUI();

		void DrawScreen();
	private:
		cge::Window& _sdlWindow;
	};
}

#endif //BOMBERMAN_GUI_HPP
