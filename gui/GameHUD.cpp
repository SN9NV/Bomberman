//
// Created by owen on 2017/08/09.
//

#include "GameHUD.hpp"

cge::GameHUD::GameHUD(cge::Window &win, int *gameState, int* prevState, cge::Sounds *snds, cge::InputManager* manager) :
	_sdlWindow(win)
{
	this->_gameState = gameState;
	this->_prevGameState = prevState;
	this->_sounds = snds;
	this->_inputManager = manager;

	this->_initUI();

	this->btn_SaveGame = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_SaveGame");
	this->btn_LoadGame = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_LoadGame");
	this->btn_Options = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_Options");
	this->btn_MainMenu = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_MainMenu");

	this->_registerHandlers();
}

cge::GameHUD::~GameHUD() {
	this->_gui.destroy();
}

void cge::GameHUD::DrawScreen() {
	this->_gui.onSDLEvent(this->_inputManager->event);

	this->_gui.draw();
}

void cge::GameHUD::_initUI(void) {
	this->_gui.init("resources/gui/datafiles");
	this->_gui.loadScheme("TaharezLook.scheme");
	this->_gui.loadScheme("AlfiskoSkin.scheme");
	this->_gui.setFont("DejaVuSans-10");

	this->_gui.loadLayout("GamePaused.layout");

	this->_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	SDL_ShowCursor(0);
}

void cge::GameHUD::_registerHandlers(void) {
	//btn_SaveGame
	this->btn_SaveGame->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_All_AreaEntered, this));
	this->btn_SaveGame->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_SaveGame_Clicked, this));

	//btn_LoadGame
	this->btn_LoadGame->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_All_AreaEntered, this));
	this->btn_LoadGame->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_LoadGame_Clicked, this));

	//btn_Options
	this->btn_Options->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_All_AreaEntered, this));
	this->btn_Options->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_Options_Clicked, this));

	//btn_MainMenu
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_All_AreaEntered, this));
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::GameHUD::btn_MainMenu_Clicked, this));
}

bool cge::GameHUD::btn_SaveGame_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = cge::GameState::PLAY_SAVE_GAME;
	return (true);
}

bool cge::GameHUD::btn_LoadGame_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_prevGameState = *this->_gameState;
	*this->_gameState = cge::GameState::PLAY_LOAD_GAME;
	return (true);
}

bool cge::GameHUD::btn_Options_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_prevGameState = *this->_gameState;
	*this->_gameState = cge::GameState::PLAY_OPTIONS;
	return (true);
}

bool cge::GameHUD::btn_MainMenu_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = cge::GameState::PLAY_MAINMENU;
	return (true);
}

bool cge::GameHUD::btn_All_AreaEntered(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Scroll);
	return (true);
}