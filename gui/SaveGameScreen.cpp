//
// Created by Owen Exall on 2017/08/16.
//

#include "SaveGameScreen.hpp"

cge::GUI::SaveGameScreen::SaveGameScreen(cge::Window &win, cge::GameState *_currState, Player *player, cge::Loader& loader, int* currMap)  :
		_window(win),
		_player(player),
		_audioMenuScroll("../resources/audio/click.wav", loader),
		_currMap(currMap)
{
	this->_audioMenuScroll.setLooping(false);
	this->_audioMenuScroll.setGain(0.09f);
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
	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Save Game");
	nanogui::AdvancedGridLayout layout(
			{100, 100, 100, 100, 100},
			{100, 100, 100, 100, 50},
			5);
	nanoguiWindow->setLayout(&layout);

	cge::GUI::Custom::CustomButton *btn_MainMenu = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Back");
	layout.setAnchor(btn_MainMenu, nanogui::AdvancedGridLayout::Anchor(0, 4,
		nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_MainMenu->setCallback([_currState] {
		*_currState = cge::GameState::PLAY_PAUSE;
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

	/**GAME SAVE CALLBACK**/

	/**Slot 1**/
	nanogui::Widget *p_slot1 = new nanogui::Widget(saves);
	p_slot1->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot1, "Slot 1)", "sans-bold");
	txtb_Slot1 = new nanogui::TextBox(p_slot1);
	txtb_Slot1->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot1->setValue(this->_availableSaves[0]->isAvailable() ? this->_availableSaves[0]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot1 = new cge::GUI::Custom::CustomButton(p_slot1, "Save");
	btn_SaveSlot1->setTooltip("Save Game on Slot 1");
	btn_SaveSlot1->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot1->setCallback([&] {
		this->saveGame(0);
	});

	/**Slot 2**/
	nanogui::Widget *p_slot2 = new nanogui::Widget(saves);
	p_slot2->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot2, "Slot 2)", "sans-bold");
	txtb_Slot2 = new nanogui::TextBox(p_slot2);
	txtb_Slot2->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot2->setValue(this->_availableSaves[1]->isAvailable() ? this->_availableSaves[1]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot2 = new cge::GUI::Custom::CustomButton(p_slot2, "Save");
	btn_SaveSlot2->setTooltip("Save Game on Slot 2");
	btn_SaveSlot2->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot2->setCallback([&] {
		this->saveGame(1);
	});

	/**Slot 3**/
	nanogui::Widget *p_slot3 = new nanogui::Widget(saves);
	p_slot3->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot3, "Slot 3)", "sans-bold");
	txtb_Slot3 = new nanogui::TextBox(p_slot3);
	txtb_Slot3->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot3->setValue(this->_availableSaves[2]->isAvailable() ? this->_availableSaves[2]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot3 = new cge::GUI::Custom::CustomButton(p_slot3, "Save");
	btn_SaveSlot3->setTooltip("Save Game on Slot 3");
	btn_SaveSlot3->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot3->setCallback([&] {
		this->saveGame(2);
	});

	/**Slot 4**/
	nanogui::Widget *p_slot4 = new nanogui::Widget(saves);
	p_slot4->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot4, "Slot 4)", "sans-bold");
	txtb_Slot4 = new nanogui::TextBox(p_slot4);
	txtb_Slot4->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot4->setValue(this->_availableSaves[3]->isAvailable() ? this->_availableSaves[3]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot4 = new cge::GUI::Custom::CustomButton(p_slot4, "Save");
	btn_SaveSlot4->setTooltip("Save Game on Slot 4");
	btn_SaveSlot4->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot4->setCallback([&] {
		this->saveGame(3);
	});

	/**Slot 5**/
	nanogui::Widget *p_slot5 = new nanogui::Widget(saves);
	p_slot5->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot5, "Slot 5)", "sans-bold");
	txtb_Slot5 = new nanogui::TextBox(p_slot5);
	txtb_Slot5->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot5->setValue(this->_availableSaves[4]->isAvailable() ? this->_availableSaves[4]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot5 = new cge::GUI::Custom::CustomButton(p_slot5, "Save");
	btn_SaveSlot5->setTooltip("Save Game on Slot 5");
	btn_SaveSlot5->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot5->setCallback([&] {
		this->saveGame(4);
	});

	/**Slot 6**/
	nanogui::Widget *p_slot6 = new nanogui::Widget(saves);
	p_slot6->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot6, "Slot 6)", "sans-bold");
	txtb_Slot6 = new nanogui::TextBox(p_slot6);
	txtb_Slot6->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot6->setValue(this->_availableSaves[5]->isAvailable() ? this->_availableSaves[5]->getCreationTime() : "[Empty]");
	cge::GUI::Custom::CustomButton *btn_SaveSlot6 = new cge::GUI::Custom::CustomButton(p_slot6, "Save");
	btn_SaveSlot6->setTooltip("Save Game on Slot 6");
	btn_SaveSlot6->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});
	btn_SaveSlot6->setCallback([&] {
		this->saveGame(5);
	});

	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::SaveGameScreen::~SaveGameScreen() {
	delete this->_screen;
	for (auto iter : this->_availableSaves) {
		delete iter.second;
	}
}

nanogui::Screen *cge::GUI::SaveGameScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::SaveGameScreen::drawScreen() {
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->_screen->drawContents();
	this->_screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::SaveGameScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
		 [](GLFWwindow *win, double x, double y) {
			 cge::GUI::SaveGameScreen *screen;
			 screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

			 screen->getScreen()->cursorPosCallbackEvent(x, y);
		 }
	);

	glfwSetMouseButtonCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int button, int action, int modifiers) {
		   cge::GUI::SaveGameScreen *screen;
		   screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
	   }
	);

	glfwSetKeyCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int key, int scancode, int action, int mods) {
		   cge::GUI::SaveGameScreen *screen;
		   screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
	   }
	);

	glfwSetCharCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, unsigned int codepoint) {
			cge::GUI::SaveGameScreen *screen;
			screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->charCallbackEvent(codepoint);
		}
	);

	glfwSetDropCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, int count, const char **filenames) {
			cge::GUI::SaveGameScreen *screen;
			screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->dropCallbackEvent(count, filenames);
		}
	);

	glfwSetScrollCallback(_window.getGLFWWindow(),
	  [](GLFWwindow *win, double x, double y) {
		  cge::GUI::SaveGameScreen *screen;
		  screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

		  screen->getScreen()->scrollCallbackEvent(x, y);
	  }
	);

	glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int width, int height) {
		   cge::GUI::SaveGameScreen *screen;
		   screen = (cge::GUI::SaveGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->resizeCallbackEvent(width, height);
	   }
	);
}

void cge::GUI::SaveGameScreen::searchAvailableSaves() {
	for (int i = 0; i < 6; i++) {
		cge::Saves::SavedGame *save = new cge::Saves::SavedGame(i);

		struct stat buffer;
		if (stat(save->getFileName().c_str(), &buffer) == 0) {
			save->setAvailable(true);
			struct tm * timeinfo = localtime(&buffer.st_ctime);
			save->setCreationTime(asctime(timeinfo));
		}
		this->_availableSaves.insert(std::make_pair(i, save));
	}
}

void cge::GUI::SaveGameScreen::saveGame(int slot) {
	if (this->_availableSaves[slot]->isAvailable()) {
		auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
				  "Overwrite Existing Save?", "Are you sure you want to overwrite the existing save?", "Yes",
				  "No", true);
		dlg->setCallback([&, slot] (int result) {
			if (result == 0)
				this->save(slot);
		});
	} else {
		this->save(slot);
	}
}

void cge::GUI::SaveGameScreen::save(int slot) {
	std::cout << "Saving" << std::endl;

	cge::Saves::SavedGame *save = this->_availableSaves[slot];

	if (save != nullptr) {
		std::ofstream saveFile;
		saveFile.open(save->getFileName());
		if (saveFile.is_open()) {
			saveFile << "level: " << *this->_currMap << std::endl
					 << "lives: " << this->_player->getLives() << std::endl
					 << "score: " << this->_player->getScore() << std::endl
					 << "dmg: " << this->_player->getDamage() << std::endl;
			saveFile.close();
		}

		struct stat buffer;
		stat(save->getFileName().c_str(), &buffer);
		save->setAvailable(true);
		struct tm * timeinfo = localtime(&buffer.st_ctime);
		save->setCreationTime(asctime(timeinfo));

		this->refreshGUI();
	} else {
		std::cout << "Failed to save. Save details not found." << std::endl;
	}
}

void cge::GUI::SaveGameScreen::refreshGUI() {
	txtb_Slot1->setValue(this->_availableSaves[0]->isAvailable() ? this->_availableSaves[0]->getCreationTime() : "[Empty]");
	txtb_Slot2->setValue(this->_availableSaves[1]->isAvailable() ? this->_availableSaves[1]->getCreationTime() : "[Empty]");
	txtb_Slot3->setValue(this->_availableSaves[2]->isAvailable() ? this->_availableSaves[2]->getCreationTime() : "[Empty]");
	txtb_Slot4->setValue(this->_availableSaves[3]->isAvailable() ? this->_availableSaves[3]->getCreationTime() : "[Empty]");
	txtb_Slot5->setValue(this->_availableSaves[4]->isAvailable() ? this->_availableSaves[4]->getCreationTime() : "[Empty]");
	txtb_Slot6->setValue(this->_availableSaves[5]->isAvailable() ? this->_availableSaves[5]->getCreationTime() : "[Empty]");
}

void cge::GUI::SaveGameScreen::ReinitializeScreen() {
	this->_screen->initialize(this->_window.getGLFWWindow(), false);
	this->nanoguiWindow->center();
}

cge::GUI::SaveGameScreen::SaveGameScreen(const cge::GUI::SaveGameScreen &cpy) :
		_window(cpy._window),
		_player(cpy._player),
		_audioMenuScroll(cpy._audioMenuScroll),
		_currMap(cpy._currMap)
{
	this->_screen = cpy._screen;
	this->nanoguiWindow = cpy.nanoguiWindow;
}

cge::GUI::SaveGameScreen cge::GUI::SaveGameScreen::operator=(const cge::GUI::SaveGameScreen &rhs) {
	*this = rhs;
	return (*this);
}
