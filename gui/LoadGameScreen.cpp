//
// Created by Owen EXALL on 2017/08/15.
//

#include "LoadGameScreen.hpp"

cge::GUI::LoadGameScreen::LoadGameScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, cge::Loader& loader, int* currMap) :
	_window(win),
	_player(player),
	_audioMenuScroll("../resources/audio/click.wav", loader),
	_currMap(currMap),
	_gameState(_currState),
	_prevState(prevState),
	_loader(loader)
{
	this->_audioMenuScroll.setLooping(false);
	this->_audioMenuScroll.setGain(0.09f);

	/**Load Available Saved Games**/
	for (int i = 0; i < 6; i++)
		this->_availableSaves.insert(std::make_pair(i, nullptr));
	this->searchAvailableSaves();

	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	this->_screen = new nanogui::Screen();
	this->_screen->initialize(this->_window.getGLFWWindow(), true);

	int width, height;
	glfwGetFramebufferSize(this->_window.getGLFWWindow(), &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(0);
	glfwSwapBuffers(this->_window.getGLFWWindow());

	// Create nanogui gui
	// bool enabled = true;
	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Load Game");
	nanogui::AdvancedGridLayout layout(
			{100, 100, 100, 100, 100},
			{100, 100, 100, 100, 50},
			5);
	nanoguiWindow->setLayout(&layout);

	cge::GUI::Custom::CustomButton *btn_MainMenu = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Back");
	layout.setAnchor(btn_MainMenu, nanogui::AdvancedGridLayout::Anchor(0, 4,
			nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_MainMenu->setCallback([_currState, prevState] {
		*_currState = *prevState;
	});
	btn_MainMenu->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	nanogui::TabWidget* tabs = nanoguiWindow->add<nanogui::TabWidget>();
	layout.setAnchor(tabs, nanogui::AdvancedGridLayout::Anchor(0, 0, 5, 4,
			nanogui::Alignment::Fill, nanogui::Alignment::Fill));

	nanogui::Widget* saves = tabs->createTab("Saved Games");
	saves->setLayout(new nanogui::GroupLayout());

	/**Slot 1**/
	nanogui::Widget *p_slot1 = new nanogui::Widget(saves);
	p_slot1->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot1, "Slot 1)", "sans-bold");
	txtb_Slot1 = new nanogui::TextBox(p_slot1);
	txtb_Slot1->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot1->setValue(this->_availableSaves[0]->isAvailable() ? this->_availableSaves[0]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot1 = new cge::GUI::Custom::CustomButton(p_slot1, "Load");
	btn_SaveSlot1->setTooltip("Load Game on Slot 1");
	btn_SaveSlot1->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot1->setCallback([&, _currState] {
		this->loadGame(0);
	});

	/**Slot 2**/
	nanogui::Widget *p_slot2 = new nanogui::Widget(saves);
	p_slot2->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot2, "Slot 2)", "sans-bold");
	txtb_Slot2 = new nanogui::TextBox(p_slot2);
	txtb_Slot2->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot2->setValue(this->_availableSaves[1]->isAvailable() ? this->_availableSaves[1]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot2 = new cge::GUI::Custom::CustomButton(p_slot2, "Load");
	btn_SaveSlot2->setTooltip("Load Game on Slot 2");
	btn_SaveSlot2->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot2->setCallback([&] {
		this->loadGame(1);
	});

	/**Slot 3**/
	nanogui::Widget *p_slot3 = new nanogui::Widget(saves);
	p_slot3->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot3, "Slot 3)", "sans-bold");
	txtb_Slot3 = new nanogui::TextBox(p_slot3);
	txtb_Slot3->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot3->setValue(this->_availableSaves[2]->isAvailable() ? this->_availableSaves[2]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot3 = new cge::GUI::Custom::CustomButton(p_slot3, "Load");
	btn_SaveSlot3->setTooltip("Load Game on Slot 3");
	btn_SaveSlot3->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot3->setCallback([&] {
		this->loadGame(2);
	});

	/**Slot 4**/
	nanogui::Widget *p_slot4 = new nanogui::Widget(saves);
	p_slot4->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot4, "Slot 4)", "sans-bold");
	txtb_Slot4 = new nanogui::TextBox(p_slot4);
	txtb_Slot4->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot4->setValue(this->_availableSaves[3]->isAvailable() ? this->_availableSaves[3]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot4 = new cge::GUI::Custom::CustomButton(p_slot4, "Load");
	btn_SaveSlot4->setTooltip("Load Game on Slot 4");
	btn_SaveSlot4->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot4->setCallback([&] {
		this->loadGame(3);
	});

	/**Slot 5**/
	nanogui::Widget *p_slot5 = new nanogui::Widget(saves);
	p_slot5->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot5, "Slot 5)", "sans-bold");
	txtb_Slot5 = new nanogui::TextBox(p_slot5);
	txtb_Slot5->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot5->setValue(this->_availableSaves[4]->isAvailable() ? this->_availableSaves[4]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot5 = new cge::GUI::Custom::CustomButton(p_slot5, "Load");
	btn_SaveSlot5->setTooltip("Load Game on Slot 5");
	btn_SaveSlot5->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot5->setCallback([&] {
		this->loadGame(4);
	});

	/**Slot 6**/
	nanogui::Widget *p_slot6 = new nanogui::Widget(saves);
	p_slot6->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot6, "Slot 6)", "sans-bold");
	txtb_Slot6 = new nanogui::TextBox(p_slot6);
	txtb_Slot6->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot6->setValue(this->_availableSaves[5]->isAvailable() ? this->_availableSaves[5]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot6 = new cge::GUI::Custom::CustomButton(p_slot6, "Load");
	btn_SaveSlot6->setTooltip("Load Game on Slot 6");
	btn_SaveSlot6->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot6->setCallback([&] {
		this->loadGame(5);
	});

	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::LoadGameScreen::~LoadGameScreen() {
	delete this->_screen;

	for (auto iter : this->_availableSaves) {
		delete iter.second;
	}
}

nanogui::Screen *cge::GUI::LoadGameScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::LoadGameScreen::drawScreen() {
	if (*_prevState == cge::GameState::PLAY_PAUSE)
		this->refreshSavedGames();

	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->_screen->drawContents();
	this->_screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::LoadGameScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
		 [](GLFWwindow *win, double x, double y) {
			 cge::GUI::LoadGameScreen *screen;
			 screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

			 screen->getScreen()->cursorPosCallbackEvent(x, y);
		 }
	);

	glfwSetMouseButtonCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int button, int action, int modifiers) {
		   cge::GUI::LoadGameScreen *screen;
		   screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
	   }
	);

	glfwSetKeyCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int key, int scancode, int action, int mods) {
		   cge::GUI::LoadGameScreen *screen;
		   screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
	   }
	);

	glfwSetCharCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, unsigned int codepoint) {
			cge::GUI::LoadGameScreen *screen;
			screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->charCallbackEvent(codepoint);
		}
	);

	glfwSetDropCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, int count, const char **filenames) {
			cge::GUI::LoadGameScreen *screen;
			screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->dropCallbackEvent(count, filenames);
		}
	);

	glfwSetScrollCallback(_window.getGLFWWindow(),
	  [](GLFWwindow *win, double x, double y) {
		  cge::GUI::LoadGameScreen *screen;
		  screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

		  screen->getScreen()->scrollCallbackEvent(x, y);
	  }
	);

	glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int width, int height) {
		   cge::GUI::LoadGameScreen *screen;
		   screen = (cge::GUI::LoadGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->resizeCallbackEvent(width, height);
	   }
	);
}

void cge::GUI::LoadGameScreen::searchAvailableSaves() {
	for (int i = 0; i < 6; i++) {
		if (this->_availableSaves[i] == nullptr)
			this->_availableSaves[i] = new cge::Saves::SavedGame(i);
		cge::Saves::SavedGame *save = this->_availableSaves[i];

		struct stat buffer;
		if (stat(save->getFileName().c_str(), &buffer) == 0) {
			save->setAvailable(true);
			struct tm * timeinfo = localtime(&buffer.st_ctime);
			save->setCreationTime(asctime(timeinfo));
		}
	}
}

void cge::GUI::LoadGameScreen::refreshSavedGames() {
	this->searchAvailableSaves();
	txtb_Slot1->setValue(this->_availableSaves[0]->isAvailable() ? this->_availableSaves[0]->getCreationTime() : "[Empty]");
	txtb_Slot2->setValue(this->_availableSaves[1]->isAvailable() ? this->_availableSaves[1]->getCreationTime() : "[Empty]");
	txtb_Slot3->setValue(this->_availableSaves[2]->isAvailable() ? this->_availableSaves[2]->getCreationTime() : "[Empty]");
	txtb_Slot4->setValue(this->_availableSaves[3]->isAvailable() ? this->_availableSaves[3]->getCreationTime() : "[Empty]");
	txtb_Slot5->setValue(this->_availableSaves[4]->isAvailable() ? this->_availableSaves[4]->getCreationTime() : "[Empty]");
	txtb_Slot6->setValue(this->_availableSaves[5]->isAvailable() ? this->_availableSaves[5]->getCreationTime() : "[Empty]");
}

void cge::GUI::LoadGameScreen::loadGame(int slot) {
	if (this->_availableSaves[slot]->isAvailable()) {
		if (*this->_prevState == cge::GameState::PLAY_PAUSE) {
			auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
												"Loose progress.",
												"You are about to load a game and will loose all unsaved progess. Continue?",
												"Yes", "No", true);

			(void)dlg;
			dlg->setCallback([this, slot](int result) {
				if (result == 0)
					this->load(slot);
			});
		} else
			this->load(slot);
	} else {
		auto noSaveDlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
			"No Saved Game!", "No Saved Game available on this slot.", "OK", "Cancel", false);

		(void)noSaveDlg;
	}
}

void cge::GUI::LoadGameScreen::load(int slot) {
	cge::Saves::SavedGame* save = this->_availableSaves[slot];

	std::string line;
	std::ifstream ifs(save->getFileName());
	std::smatch match;

	int level = 0,
		lives = 3,
		score = 0,
		dmg = 2;

	if (ifs.good()) {
		while (std::getline(ifs, line)) {
			if (std::regex_match(line, match, std::regex("level: ([0-5]{1})\\s*"))) {
				level = std::atoi(match[1].str().c_str());
			} else if (std::regex_match(line, match, std::regex("lives: ([0-9]{1,2})\\s*"))) {
				lives = std::atoi(match[1].str().c_str());
			} else if (std::regex_match(line, match, std::regex("score: ([0-9])\\s*"))) {
				score = std::atoi(match[1].str().c_str());
			} else if (std::regex_match(line, match, std::regex("dmg: ([0-9])\\s*"))) {
				dmg = std::atoi(match[1].str().c_str());
			} else {
				auto noSaveDlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
					"Error", "Failed to load save game. Corrupted save file.", "OK", "Cancel", false);

				(void)noSaveDlg;
				ifs.close();
				return ;
			}
		}
		*_currMap = level;
		_player->setLives(lives);
		_player->setScore(score);
		_player->setPauseMenue(false);
		_player->setDamage(dmg);
		*_gameState = cge::GameState::PLAY_GAME;
	} else {
		std::cerr << "Failed to load game. Corrupt" << std::endl;
	}
}

void cge::GUI::LoadGameScreen::ReinitializeScreen() {
	this->_screen->initialize(this->_window.getGLFWWindow(), false);
	this->nanoguiWindow->center();
}

cge::GUI::LoadGameScreen::LoadGameScreen(const cge::GUI::LoadGameScreen &cpy) :
	_window(cpy._window),
	_player(cpy._player),
	_audioMenuScroll("../resources/audio/click.wav", cpy._loader),
	_currMap(cpy._currMap),
	_gameState(cpy._gameState),
	_prevState(cpy._prevState),
	_loader(cpy._loader)
{
	this->_screen = cpy._screen;
	this->nanoguiWindow = cpy.nanoguiWindow;
}
