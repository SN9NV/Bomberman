//
// Created by Owen EXALL on 2017/08/10.
//

#include "GUI.hpp"

cge::GUI::GUI(cge::Window &win) :
	_sdlWindow(win),
	nanogui::Screen(win.getSDLWindow(), Eigen::Vector2i(win.getWidth(), win.getHeight()), "SDL_gui Test")
{
	(void)_sdlWindow;
}

cge::GUI::~GUI() {

}
