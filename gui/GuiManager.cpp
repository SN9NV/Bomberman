//
// Created by Owen EXALL on 2017/08/10.
//

#include "GuiManager.hpp"

cge::GuiManager *cge::GuiManager::s_instance = nullptr;

bool cge::GuiManager::initialise(cge::Window& win,
								cge::GameState *state,
								Player* player)
{
	if (s_instance == nullptr) {
		s_instance = new GuiManager(win, player);

		s_instance->setMainMenuScreen(new cge::GUI::MainMenuScreen(win, state, player));
	}
	return (true);
}

cge::GuiManager *cge::GuiManager::getSingleton() {
	if (s_instance == nullptr) {
		throw BombermanException("GuiManager not initialized.");
	}
	return (s_instance);
}

cge::GuiManager::GuiManager(cge::Window &win, Player* player):
	_window(win),
	_player(player)
{
}

cge::GuiManager::~GuiManager() {
	delete this->_mainMenuScreen;
}

void cge::GuiManager::drawScreen(int screen) {
	glfwSetInputMode(this->_window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	switch (screen) {
		case (cge::GameState::PLAY_MENU):
		default:
			this->_mainMenuScreen->setInputCallbacks();
			this->_mainMenuScreen->drawScreen();
			break;
	}
}

void cge::GuiManager::setMainMenuScreen(cge::GUI::MainMenuScreen *mainMenuScreen) {
	this->_mainMenuScreen = mainMenuScreen;
}

