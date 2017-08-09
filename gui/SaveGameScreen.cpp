//
// Created by owen on 2017/08/09.
//

#include "SaveGameScreen.hpp"

cge::SaveGameScreen::SaveGameScreen(cge::Window &win, int *gameState, cge::Sounds *snds) :
	_sdlWindow(win)
{
	this->_gameState = gameState;
	this->_sounds = snds;

	this->_initUI();

	this->txtb_SaveGame = this->_gui.getChildFromRoot<CEGUI::Editbox>("txtb_SaveName");
	this->btn_MainMenu = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_MainMenu");
	this->btn_SaveGame = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_Save");
	this->lb_SavedGames = this->_gui.getChildFromRoot<CEGUI::Listbox>("lb_SaveGames");

	this->_registerHandlers();
	this->_getSavedGames();
}

cge::SaveGameScreen::~SaveGameScreen() {
	this->_gui.destroy();
}

void cge::SaveGameScreen::DrawScreen() {
	//Process any input
	this->_processInput();

	// Clear the screen
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->_gui.draw();

	this->_sdlWindow.swapBuffers();
}

void cge::SaveGameScreen::_processInput(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		this->_gui.onSDLEvent(event);
	}
}

void cge::SaveGameScreen::_initUI(void) {
	this->_gui.init("resources/gui/datafiles");
	this->_gui.loadScheme("TaharezLook.scheme");
	this->_gui.loadScheme("AlfiskoSkin.scheme");
	this->_gui.setFont("DejaVuSans-10");

	this->_gui.loadLayout("SaveGame.layout");

	this->_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	SDL_ShowCursor(0);
}

void cge::SaveGameScreen::_registerHandlers(void) {
	//btn_MainMenu
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::SaveGameScreen::btn_All_EnterArea, this));
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::SaveGameScreen::btn_MainMenu_Clicked, this));

	//btn_LoadGame
	this->btn_SaveGame->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::SaveGameScreen::btn_All_EnterArea, this));
	this->btn_SaveGame->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::SaveGameScreen::btn_SaveGame_Clicked, this));
}

bool file_has_suffix(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		   str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

void cge::SaveGameScreen::_getSavedGames(void) {
	DIR				*dir;
	struct dirent	*ent;
	int				id;

	if ((dir = opendir(SAVE_GAMES_PATH)) != nullptr) {
		id = 0;
		while ((ent = readdir(dir)) != nullptr) {
			std::string fileName = ent->d_name;

			if (!file_has_suffix(fileName, ".save"))
				continue;
			CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(fileName, id, nullptr, false, true);
			item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
			item->setSelected(this->lb_SavedGames->getItemCount() == 0);
			this->lb_SavedGames->addItem(item);
			id++;
		}
		closedir(dir);
	} else {
		this->_gui.showMessageBox("Failed to open directory where saves are located.", "Error");
	}
}

bool cge::SaveGameScreen::btn_All_EnterArea(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Scroll);
	return (true);
}

bool cge::SaveGameScreen::btn_MainMenu_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = cge::GameState::PLAY_GAME_PAUSED;
	return (true);
}

bool cge::SaveGameScreen::btn_SaveGame_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	this->_gui.showMessageBox(this->txtb_SaveGame->getText().c_str());
	//*this->_gameState = cge::GameState::PLAY_GAME_PAUSED;
	return (true);
}
