//
// Created by owen on 2017/08/09.
//

#include "OptionsScreen.hpp"
#include "../shared.hpp"

cge::OptionsScreen::OptionsScreen(cge::Window &win, int *gameState, int* prevState, cge::Sounds *snds) :
	_sdlWindow(win)
{
	this->_prevGameState = prevState;
	this->_gameState = gameState;
	this->_sounds = snds;

	this->_initUI();

	this->btn_MainMenu = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_MainMenu");
	this->btn_Save = this->_gui.getChildFromRoot<CEGUI::PushButton>("btn_Save");
	this->sl_MusicVolume = this->_gui.getChildFromRoot<CEGUI::Slider>("sl_MusicVolume");
	this->sl_SfxVolume = this->_gui.getChildFromRoot<CEGUI::Slider>("sl_SfxVolume");
	this->lbl_CurrMusicVolume = this->_gui.getChildFromRoot<CEGUI::Window>("lbl_CurrMusicVolume");
	this->lbl_CurrSfxVolume = this->_gui.getChildFromRoot<CEGUI::Window>("lbl_CurrSfxVolume");

	this->sl_MusicVolume->setCurrentValue(this->_sounds->GetMusicVolume());
	this->sl_SfxVolume->setCurrentValue(this->_sounds->GetSfxVolume());
	this->_updateValue();

	this->_registerHandlers();
}

cge::OptionsScreen::~OptionsScreen() {
	this->_gui.destroy();
}

void cge::OptionsScreen::DrawScreen() {
	//Process any input
	this->_processInput();

	// Clear the screen
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->_gui.draw();

	this->_sdlWindow.swapBuffers();
}

void cge::OptionsScreen::_processInput(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		this->_gui.onSDLEvent(event);
	}
}

void cge::OptionsScreen::_initUI(void) {
	this->_gui.init("resources/gui/datafiles");
	this->_gui.loadScheme("TaharezLook.scheme");
	this->_gui.loadScheme("AlfiskoSkin.scheme");
	this->_gui.setFont("DejaVuSans-10");

	this->_gui.loadLayout("Options.layout");

	this->_gui.setMouseCursor("AlfiskoSkin/MouseArrow");
	SDL_ShowCursor(0);
}

void cge::OptionsScreen::_registerHandlers(void) {
	//btn_MainMenu
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::btn_All_EnterArea, this));
	this->btn_MainMenu->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::btn_MainMenu_Clicked, this));

	//btn_Save
	this->btn_Save->subscribeEvent(CEGUI::PushButton::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::btn_All_EnterArea, this));
	this->btn_Save->subscribeEvent(CEGUI::PushButton::EventClicked,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::btn_Save_Clicked, this));

	//sl_MusicVolume
	this->sl_MusicVolume->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::sl_MusicVolume_ValueChanged, this));

	//sl_SfxVolume
	this->sl_SfxVolume->subscribeEvent(CEGUI::Slider::EventValueChanged,
		CEGUI::Event::Subscriber(&cge::OptionsScreen::sl_SfxVolume_ValueChanged, this));
}

bool cge::OptionsScreen::btn_MainMenu_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	*this->_gameState = *this->_prevGameState;
	return (true);
}

bool cge::OptionsScreen::btn_Save_Clicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->SetMusicVolume(static_cast<int>(this->sl_MusicVolume->getCurrentValue()));
	this->_sounds->SetSfxVolume(static_cast<int>(this->sl_SfxVolume->getCurrentValue()));
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Validate);
	return (true);
}

bool
cge::OptionsScreen::sl_MusicVolume_ValueChanged(const CEGUI::EventArgs &e) {
	(void)e;
	this->_updateValue();
	this->_sounds->SetMusicVolume(static_cast<int>(this->sl_MusicVolume->getCurrentValue()));
	return (true);
}

bool cge::OptionsScreen::sl_SfxVolume_ValueChanged(const CEGUI::EventArgs &e) {
	(void)e;
	this->_updateValue();
	this->_sounds->SetSfxVolume(static_cast<int>(this->sl_SfxVolume->getCurrentValue()));
	return (true);
}

bool cge::OptionsScreen::btn_All_EnterArea(const CEGUI::EventArgs &e) {
	(void)e;
	this->_sounds->PlaySfx(cge::Sounds::Sfx::Menu_Scroll);
	return (true);
}

void cge::OptionsScreen::_updateValue() {
	std::string mVolume = std::to_string(static_cast<int>(this->sl_MusicVolume->getCurrentValue()));
	std::string sVolume = std::to_string(static_cast<int>(this->sl_SfxVolume->getCurrentValue()));

	mVolume = "(" + mVolume + ")";
	sVolume = "(" + sVolume + ")";

	this->lbl_CurrMusicVolume->setText(mVolume);
	this->lbl_CurrSfxVolume->setText(sVolume);
}
