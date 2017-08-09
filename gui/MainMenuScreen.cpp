//
// Created by owen on 2017/08/08.
//

#include "MainMenuScreen.hpp"

cge::MainMenuScreen::MainMenuScreen(cge::Window &win, int* gameState, int* prevState, cge::Sounds* snds) :
	_sdlWindow(win)
{
	this->_initUI();
	this->_gameState = gameState;
	this->_prevGameState = prevState;
	this->_sounds = snds;

	this->btn_NewGame = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_NewGame");
	this->btn_LoadGame = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_LoadGame");
	this->btn_Options = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_Options");
	this->btn_Quit = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_Quit");

	this->_registerHandlers();

	//rendering stuff to draw the bomberman model on the menu screen.
	this->shader = new cge::GLSLProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	this->renderer = new cge::Renderer(*this->shader);
	this->loader = new cge::Loader();
	this->camera = new cge::Camera(glm::vec3(2.0f, 4.75f, 4.5f), glm::vec3(0.5f, -0.4f, 0.0f), this->_sdlWindow);
}

cge::MainMenuScreen::~MainMenuScreen() {
	this->_gui.destroy();
	delete this->camera;
	delete this->loader;
	delete this->renderer;
	delete this->shader;
}

void cge::MainMenuScreen::DrawScreen(cge::Entity& bomberman) {
	//Process any input
	this->_processInput();

	this->shader->start();
	this->renderer->prepare();
	this->camera->update(*this->shader);
	this->renderer->render(bomberman);
	glDisable(GL_DEPTH_TEST);
	this->_gui.draw();

	this->shader->end();

	this->_sdlWindow.swapBuffers();
}

void cge::MainMenuScreen::_processInput(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		this->_gui.onSDLEvent(event);
	}
}

void cge::MainMenuScreen::_initUI(void) {
	this->_gui.init("resources/gui/datafiles");
	this->_gui.loadScheme("TaharezLook.scheme");
	this->_gui.loadScheme("AlfiskoSkin.scheme");
	this->_gui.setFont("DejaVuSans-10");

	this->_gui.loadLayout("MainMenu.layout");

	this->_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	SDL_ShowCursor(0);
}

void cge::MainMenuScreen::_registerHandlers(void) {
	//btn_NewGame
	this->btn_NewGame->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_All_EnterArea, this));
	this->btn_NewGame->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_NewGame_Clicked, this));

	//btn_LoadGame
	this->btn_LoadGame->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_All_EnterArea, this));
	this->btn_LoadGame->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_LoadGame_Clicked, this));

	//btn_Options
	this->btn_Options->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_All_EnterArea, this));
	this->btn_Options->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_Options_Clicked, this));

	//btn_Quit
	this->btn_Quit->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_Quit_Clicked, this));
	this->btn_Quit->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::MainMenuScreen::btn_All_EnterArea, this));
}

bool cge::MainMenuScreen::btn_Quit_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = cge::GameState::WANTS_QUIT;
	return (true);
}

bool cge::MainMenuScreen::btn_All_EnterArea(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Scroll);
	return (true);
}

bool cge::MainMenuScreen::btn_NewGame_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = cge::GameState::PLAY_GAME_PLAY;
	return (true);
}

bool cge::MainMenuScreen::btn_LoadGame_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_prevGameState = *this->_gameState;
	*this->_gameState = cge::GameState::PLAY_LOAD_GAME;
	return (true);
}

bool cge::MainMenuScreen::btn_Options_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_prevGameState = *this->_gameState;
	*this->_gameState = cge::GameState::PLAY_OPTIONS;
	return (true);
}
