//
// Created by Owen EXALL on 2017/08/10.
//

#include "GuiManager.hpp"

cge::GuiManager *cge::GuiManager::s_instance = nullptr;

bool cge::GuiManager::initialise(cge::Window& win,
								cge::GameState *state,
								cge::GameState *prevState,
								Player* player,
								int* currMap,
								cge::Loader& _loader)
{
	if (s_instance == nullptr) {
		s_instance = new GuiManager(win, state, prevState, player, currMap, _loader);
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
							cge::GameState *prevState,
							Player* player,
							int* currMap,
							cge::Loader& _loader) :
	_window(win),
	_prevState(prevState),
	_state(state),
	_player(player),
	_currMap(currMap)
{
	this->_mainMenuScreen = new cge::GUI::MainMenuScreen(win, state, prevState, player, currMap, _loader);
	this->_settingsScreen = new cge::GUI::SettingsScreen(win, state, prevState, player, _loader);
	this->_loadGameScreen = new cge::GUI::LoadGameScreen(win, state, prevState, player, _loader, currMap);
	this->_saveGameScreen = new cge::GUI::SaveGameScreen(win, state, player, _loader, currMap);
	this->_pauseGameScreen = new cge::GUI::PauseGameScreen(win, state, prevState, player, currMap, _loader);
}

cge::GuiManager::~GuiManager() {
	delete this->_mainMenuScreen;
	delete this->_settingsScreen;
	delete this->_loadGameScreen;
	delete this->_saveGameScreen;
	delete this->_pauseGameScreen;
}

void cge::GuiManager::drawScreen(int screen) {
	glfwSetInputMode(this->_window.getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	switch (screen) {
		case (cge::GameState::PLAY_OPTS):
			this->_settingsScreen->setInputCallbacks();
			this->_settingsScreen->drawScreen();
			break;
		case (cge::GameState::PLAY_LOAD):
			this->_loadGameScreen->setInputCallbacks();
			this->_loadGameScreen->drawScreen();
			break;
		case (cge::GameState::PLAY_SAVE):
			this->_saveGameScreen->setInputCallbacks();
			this->_saveGameScreen->drawScreen();
			break;
		case (cge::GameState::PLAY_PAUSE):
			this->_pauseGameScreen->setInputCallbacks();
			this->_pauseGameScreen->drawScreen();
			break;
		case (cge::GameState::PLAY_MENU):
		default:
			this->_mainMenuScreen->setInputCallbacks();
			this->_mainMenuScreen->drawScreen();
			break;
	}
}

void cge::GuiManager::ReinitializeScreens() {
	this->_mainMenuScreen->ReinitializeScreen();
	this->_settingsScreen->ReinitializeScreen();
	this->_loadGameScreen->ReinitializeScreen();
	this->_saveGameScreen->ReinitializeScreen();
	this->_pauseGameScreen->ReinitializeScreen();
}
