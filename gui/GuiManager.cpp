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
		s_instance = new GuiManager(win, state, player);
	}
	return (true);
}

cge::GuiManager *cge::GuiManager::getSingleton() {
	if (s_instance == nullptr) {
		throw BombermanException("GuiManager not initialized.");
	}
	return (s_instance);
}

cge::GuiManager::GuiManager(cge::Window &win,
							cge::GameState *state,
							Player* player):
	_window(win),
	_state(state),
	_player(player)
{
	this->_mainMenuScreen = new cge::GUI::MainMenuScreen(win, state, player);
	this->_settingsScreen = new cge::GUI::SettingsScreen(win, state, player);
}

cge::GuiManager::~GuiManager() {
	delete this->_mainMenuScreen;
}

void cge::GuiManager::drawScreen(int screen) {
	glfwSetInputMode(this->_window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	switch (screen) {
		case (cge::GameState::PLAY_OPTS):
			this->_settingsScreen->setInputCallbacks();
			this->_settingsScreen->drawScreen();
			break;
		case (cge::GameState::PLAY_MENU):
		default:
			this->_mainMenuScreen->setInputCallbacks();
			this->_mainMenuScreen->drawScreen();
			break;
	}
}