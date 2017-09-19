//
// Created by Owen EXALL on 2017/08/10.
//

#include "GuiManager.hpp"

cge::GuiManager *cge::GuiManager::s_instance = nullptr;

bool cge::GuiManager::initialise(cge::Window& win, cge::GameState *state, cge::GameState *prevState, Player* player, int *currMap, cge::Loader& loader){
	if (s_instance == nullptr) {
		s_instance = new GuiManager(win, state, prevState, player, currMap, loader);
	}

	return (true);
}

cge::GuiManager *cge::GuiManager::getSingleton() {
	if (s_instance == nullptr) {
		throw BombermanException("GuiManager not initialized.");
	}
	return (s_instance);
}

cge::GuiManager::GuiManager(cge::Window &win, cge::GameState *state, cge::GameState *prevState, Player* player, int *currMap, cge::Loader& loader) :
		_window(win),
		_prevState(prevState),
		_state(state),
		_player(player),
		_currMap(currMap)
{
	this->_mainMenuScreen = new cge::GUI::MainMenuScreen(win, state, prevState, player, currMap, loader);
	this->_settingsScreen = new cge::GUI::SettingsScreen(win, state, prevState, player, loader);
	this->_loadGameScreen = new cge::GUI::LoadGameScreen(win, state, prevState, player, loader, currMap);
	this->_saveGameScreen = new cge::GUI::SaveGameScreen(win, state, player, loader, currMap);
	this->_pauseGameScreen = new cge::GUI::PauseGameScreen(win, state, prevState, player, currMap, loader);
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

cge::GuiManager::GuiManager(const cge::GuiManager &cpy) :
		_window(cpy._window),
		_prevState(cpy._prevState),
		_state(cpy._state),
		_player(cpy._player),
		_currMap(cpy._currMap)
{
	this->_mainMenuScreen = cpy._mainMenuScreen;
	this->_settingsScreen = cpy._settingsScreen;
	this->_loadGameScreen = cpy._loadGameScreen;
	this->_saveGameScreen = cpy._saveGameScreen;
	this->_pauseGameScreen = cpy._pauseGameScreen;
}

cge::GuiManager cge::GuiManager::operator=(const cge::GuiManager &rhs) {
	this->_window = rhs._window;
	this->_prevState = rhs._prevState;
	this->_state = rhs._state;
	this->_player = rhs._player;
	this->_currMap = rhs._currMap;

	this->_mainMenuScreen = rhs._mainMenuScreen;
	this->_settingsScreen = rhs._settingsScreen;
	this->_loadGameScreen = rhs._loadGameScreen;
	this->_saveGameScreen = rhs._saveGameScreen;
	this->_pauseGameScreen = rhs._pauseGameScreen;

	return *this;
}
