//
// Created by Owen EXALL on 2017/08/10.
//

#include "GuiManager.hpp"

cge::GuiManager *cge::GuiManager::s_instance = nullptr;

cge::GuiManager *cge::GuiManager::getSingleton(cge::Window& win) {
	if (s_instance == nullptr) {
		s_instance = new cge::GuiManager(win);
	}
	return (s_instance);
}

cge::GuiManager::GuiManager(cge::Window &win):
	_sdlWindow(win)
{
	(void)_sdlWindow;
}

cge::GuiManager::~GuiManager() {

}
