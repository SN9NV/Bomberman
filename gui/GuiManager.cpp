//
// Created by Owen EXALL on 2017/08/10.
//

#include <SDL_opengl.h>
#include "GuiManager.hpp"

cge::GuiManager *cge::GuiManager::s_instance = nullptr;

bool cge::GuiManager::initialise(cge::Window& win) {
	if (s_instance == nullptr) {
		s_instance = new GuiManager(win);

		s_instance->setMainMenuScreen(new cge::GUI::MainMenuScreen(win));
	}
	return (true);
}

cge::GuiManager *cge::GuiManager::getSingleton() {
	if (s_instance == nullptr) {
		throw BombermanException("GuiManager not initialized.");
	}
	return (s_instance);
}

cge::GuiManager::GuiManager(cge::Window &win):
	_sdlWindow(win)
{
}

cge::GuiManager::~GuiManager() {
	delete this->_mainMenuScreen;
}

void cge::GuiManager::drawScreen(int screen) {
	glClearColor(0.9f, 0.9f, 0.9f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	switch (screen) {
		case (1):
		default:
			this->_mainMenuScreen->drawScreen();
			break;
	}
}

void cge::GuiManager::setMainMenuScreen(cge::GUI::MainMenuScreen *mainMenuScreen) {
	this->_mainMenuScreen = mainMenuScreen;
}

