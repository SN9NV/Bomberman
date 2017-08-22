//
// Created by Owen EXALL on 2017/08/15.
//

#include "SettingsScreen.hpp"
#include "../io/settings/Settings.hpp"
#include "GuiManager.hpp"

cge::GUI::SettingsScreen::SettingsScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, cge::Loader& loader) :
	_window(win),
	_player(player),
	_audioMenuScroll("../resources/audio/menu_click.wav", loader),
	_currState(_currState),
	_prevState(prevState),
	_changesMade(false),
	_windowChangesMade(false)
{
	this->_audioMenuScroll.setLooping(false);
	this->_audioMenuScroll.setGain(0.09f);

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
	bool enabled = true;
	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Settings");
	nanogui::AdvancedGridLayout layout(
			{100, 100, 100, 100, 100},
			{100, 100, 100, 100, 50},
			5);
	nanoguiWindow->setLayout(&layout);

	cge::GUI::Custom::CustomButton *btn_MainMenu = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Back");
	layout.setAnchor(btn_MainMenu, nanogui::AdvancedGridLayout::Anchor(0, 4,
		nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_MainMenu->setCallback([&] {
		if (this->_changesMade || this->_windowChangesMade) {
			auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
				"Unsaved Changes", "All unsaved changes will be lost. Continue?", "Yes", "No", true);
			dlg->setCallback([&] (int result) {
				if (result == 0)
					*this->_currState = *this->_prevState;
			});
		} else {
			*this->_currState = *this->_prevState;
		}
	});
	btn_MainMenu->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_Save = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Save");
	layout.setAnchor(btn_Save, nanogui::AdvancedGridLayout::Anchor(4, 4,
		nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_Save->setCallback([&] {
		this->saveSettings();
	});
	btn_Save->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	nanogui::TabWidget* tabs = nanoguiWindow->add<nanogui::TabWidget>();
	layout.setAnchor(tabs, nanogui::AdvancedGridLayout::Anchor(0, 0, 5, 4,
		nanogui::Alignment::Fill, nanogui::Alignment::Fill));

	/**SOUNDS**/
	nanogui::Widget* sounds = tabs->createTab("Sound Settings");
	sounds->setLayout(new nanogui::GroupLayout());

	/**SOUNDS: Master Volume**/
	new nanogui::Label(sounds, "Master Volume:", "sans-bold");
	nanogui::Widget *p_master = new nanogui::Widget(sounds);
	p_master->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	sl_master = new nanogui::Slider(p_master);
	sl_master->setValue(cge::Settings::Settings::getSingleton()->getSettings().MasterVolume);
	sl_master->setFixedWidth(250);

	nanogui::TextBox *txtb_master = new nanogui::TextBox(p_master);
	txtb_master->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_master->setValue(std::to_string((int)(sl_master->value() * 100)));
	txtb_master->setUnits("%");
	sl_master->setCallback([&, txtb_master](float value) {
		cge::Settings::Settings::getSingleton()->setMasterVolume(value);
		txtb_master->setValue(std::to_string((int) (value * 100)));
		this->_changesMade = true;
	});
	txtb_master->setFixedSize(nanogui::Vector2i(60,25));
	txtb_master->setFontSize(20);
	txtb_master->setAlignment(nanogui::TextBox::Alignment::Right);


	/**SOUNDS: Music Volume**/
	new nanogui::Label(sounds, "Music Volume:", "sans-bold");
	nanogui::Widget *p_music = new nanogui::Widget(sounds);
	p_music->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	sl_music = new nanogui::Slider(p_music);
	sl_music->setValue(cge::Settings::Settings::getSingleton()->getSettings().MusicVolume);
	sl_music->setFixedWidth(250);

	nanogui::TextBox *txtb_music = new nanogui::TextBox(p_music);
	txtb_music->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_music->setValue(std::to_string((int)(sl_music->value() * 100)));
	txtb_music->setUnits("%");
	sl_music->setCallback([&, txtb_music](float value) {
		cge::Settings::Settings::getSingleton()->setMusicVolume(value);
		txtb_music->setValue(std::to_string((int) (value * 100)));
		this->_changesMade = true;
	});
	txtb_music->setFixedSize(nanogui::Vector2i(60,25));
	txtb_music->setFontSize(20);
	txtb_music->setAlignment(nanogui::TextBox::Alignment::Right);

	/**SOUNDS: Sfx Volume**/
	new nanogui::Label(sounds, "Sound Effects Volume:", "sans-bold");
	nanogui::Widget *p_sfx = new nanogui::Widget(sounds);
	p_sfx->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	sl_sfx = new nanogui::Slider(p_sfx);
	sl_sfx->setValue(cge::Settings::Settings::getSingleton()->getSettings().SfxVolume); // set sfx volume here;
	sl_sfx->setFixedWidth(250);

	nanogui::TextBox *txtb_sfx = new nanogui::TextBox(p_sfx);
	txtb_sfx->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_sfx->setValue(std::to_string((int)(sl_sfx->value() * 100)));
	txtb_sfx->setUnits("%");
	sl_sfx->setCallback([&, txtb_sfx](float value) {
		cge::Settings::Settings::getSingleton()->setSfxVolume(value);
		txtb_sfx->setValue(std::to_string((int) (value * 100)));
		this->_changesMade = true;
	});
	txtb_sfx->setFixedSize(nanogui::Vector2i(60,25));
	txtb_sfx->setFontSize(20);
	txtb_sfx->setAlignment(nanogui::TextBox::Alignment::Right);

	/**KEY-BINDINGS: **/
	nanogui::Widget* keyBindings = tabs->createTab("Key Bindings");
	keyBindings->setLayout(new nanogui::GroupLayout());

	/**KEY-BINDINGS: Move Upwards**/
	nanogui::Widget* p_MoveUp = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveUp = p_MoveUp->add<nanogui::Label>("Move Up:");
	lbl_MoveUp->setFixedWidth(80);
	p_MoveUp->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	txtb_MoveUp = p_MoveUp->add<nanogui::TextBox>();
	txtb_MoveUp->setValue(charToString(cge::Settings::Settings::getSingleton()->getSettings().KeyUpwards));
	txtb_MoveUp->setEditable(true);
	txtb_MoveUp->setFixedWidth(50);
	txtb_MoveUp->setFormat("[A-Z]");
	txtb_MoveUp->setCallback([&] (const std::string& str)-> bool {
		this->_changesMade = true;
		return (true);
	});

	/**KEY-BINDINGS: Move Down**/
	nanogui::Widget* p_MoveDown = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveDown = p_MoveDown->add<nanogui::Label>("Move Down:");
	lbl_MoveDown->setFixedWidth(80);
	p_MoveDown->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	txtb_MoveDown = p_MoveDown->add<nanogui::TextBox>();
	txtb_MoveDown->setValue(charToString(cge::Settings::Settings::getSingleton()->getSettings().KeyDown));
	txtb_MoveDown->setEditable(true);
	txtb_MoveDown->setFixedWidth(50);
	txtb_MoveDown->setFormat("[A-Z]");
	txtb_MoveDown->setCallback([&] (const std::string& str)-> bool {
		this->_changesMade = true;
		return (true);
	});

	/**KEY-BINDINGS: Move Right**/
	nanogui::Widget* p_MoveRight = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveRight = p_MoveRight->add<nanogui::Label>("Move Right:");
	lbl_MoveRight->setFixedWidth(80);
	p_MoveRight->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	txtb_MoveRight = p_MoveRight->add<nanogui::TextBox>();
	txtb_MoveRight->setValue(charToString(cge::Settings::Settings::getSingleton()->getSettings().KeyRight));
	txtb_MoveRight->setEditable(true);
	txtb_MoveRight->setFixedWidth(50);
	txtb_MoveRight->setFormat("[A-Z]");
	txtb_MoveRight->setCallback([&] (const std::string& str)-> bool {
		this->_changesMade = true;
		return (true);
	});

	/**KEY-BINDINGS: Move Left**/
	nanogui::Widget* p_MoveLeft = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveLeft = p_MoveLeft->add<nanogui::Label>("Move Left:");
	lbl_MoveLeft->setFixedWidth(80);
	p_MoveLeft->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	txtb_MoveLeft = p_MoveLeft->add<nanogui::TextBox>();
	txtb_MoveLeft->setValue(charToString(cge::Settings::Settings::getSingleton()->getSettings().KeyLeft)); //Change here to settings
	txtb_MoveLeft->setEditable(true);
	txtb_MoveLeft->setFixedWidth(50);
	txtb_MoveLeft->setFormat("[A-Z]");
	txtb_MoveLeft->setCallback([&] (const std::string& str)-> bool {
		this->_changesMade = true;
		return (true);
	});

	/**WINDOW**/
	nanogui::Widget* windowSettings = tabs->createTab("Window");
	windowSettings->setLayout(new nanogui::GroupLayout());

	new nanogui::Label(windowSettings, "Resolution:", "sans-bold");
	cb_Resolution = new nanogui::ComboBox(windowSettings,
		{
			"1920 x 1080",
			"1280 x 720",
			"640 × 480"
		});
	cb_Resolution->setFontSize(16);
	if (cge::Settings::Settings::getSingleton()->getSettings().Height == 1080)
		cb_Resolution->setSelectedIndex(0);
	else if (cge::Settings::Settings::getSingleton()->getSettings().Height == 720)
		cb_Resolution->setSelectedIndex(1);
	else
		cb_Resolution->setSelectedIndex(2);
	cb_Resolution->setCallback([&] (int index) {
		_windowChangesMade = true;
	});

	chkbx_FullScreen = new nanogui::CheckBox(windowSettings, "Fullscreen");
	chkbx_FullScreen->setChecked(cge::Settings::Settings::getSingleton()->getSettings().Fullscreen);
	chkbx_FullScreen->setCallback([&] (bool state) {
		_windowChangesMade = true;
	});

	tabs->setActiveTab(0);
	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::SettingsScreen::~SettingsScreen() {
	delete this->_screen;
}

nanogui::Screen *cge::GUI::SettingsScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::SettingsScreen::drawScreen() {
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->_screen->drawContents();
	this->_screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::SettingsScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
		 [](GLFWwindow *win, double x, double y) {
			 cge::GUI::SettingsScreen *screen;
			 screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

			 screen->getScreen()->cursorPosCallbackEvent(x, y);
		 }
	);

	glfwSetMouseButtonCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int button, int action, int modifiers) {
		   cge::GUI::SettingsScreen *screen;
		   screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
	   }
	);

	glfwSetKeyCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int key, int scancode, int action, int mods) {
		   cge::GUI::SettingsScreen *screen;
		   screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
	   }
	);

	glfwSetCharCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, unsigned int codepoint) {
			cge::GUI::SettingsScreen *screen;
			screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->charCallbackEvent(codepoint);
		}
	);

	glfwSetDropCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, int count, const char **filenames) {
			cge::GUI::SettingsScreen *screen;
			screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->dropCallbackEvent(count, filenames);
		}
	);

	glfwSetScrollCallback(_window.getGLFWWindow(),
	  [](GLFWwindow *win, double x, double y) {
		  cge::GUI::SettingsScreen *screen;
		  screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

		  screen->getScreen()->scrollCallbackEvent(x, y);
	  }
	);

	glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int width, int height) {
		   cge::GUI::SettingsScreen *screen;
		   screen = (cge::GUI::SettingsScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->resizeCallbackEvent(width, height);
	   }
	);
}

void cge::GUI::SettingsScreen::saveSettings() {
	cge::Settings::Settings* setts = cge::Settings::Settings::getSingleton();

	setts->setMasterVolume(this->sl_master->value());
	setts->setMusicVolume(this->sl_music->value());
	setts->setSfxVolume(this->sl_sfx->value());

	setts->setKeyUpwards(static_cast<unsigned int>(this->txtb_MoveUp->value()[0]));
	setts->setKeyRight(static_cast<unsigned int>(this->txtb_MoveRight->value()[0]));
	setts->setKeyDown(static_cast<unsigned int>(this->txtb_MoveDown->value()[0]));
	setts->setKeyLeft(static_cast<unsigned int>(this->txtb_MoveLeft->value()[0]));

	_player->set_up(this->txtb_MoveUp->value()[0]);
	_player->set_right(this->txtb_MoveRight->value()[0]);
	_player->set_down(this->txtb_MoveDown->value()[0]);
	_player->set_left(this->txtb_MoveLeft->value()[0]);

	if (cb_Resolution->selectedIndex() == 0) {
		setts->setHeight(1080);
		setts->setWidth(1920);
	} else if (cb_Resolution->selectedIndex() == 1) {
		setts->setHeight(720);
		setts->setWidth(1280);
	} else if (cb_Resolution->selectedIndex() == 2) {
		setts->setHeight(480);
		setts->setWidth(640);
	}
	setts->setFullscreen(chkbx_FullScreen->checked());

	if (this->_windowChangesMade) {
		this->_window.recreate(setts->getSettings().Width, setts->getSettings().Height);
		cge::GuiManager::getSingleton()->ReinitializeScreens();
	}

	setts->writeToBinaryFile();
	auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Information,
		"Saved.", "Settings saved. Back to Menu?", "Yes", "No", true);
	this->_changesMade = false;
	this->_windowChangesMade = false;
	dlg->setCallback([&] (int result) {
		if (result == 0)
			*this->_currState = *this->_prevState;
	});
}

std::string cge::GUI::SettingsScreen::charToString(int chr) {
	std::stringstream ss;
	std::string s;
	ss << (char)chr;
	ss >> s;
	return (s);
}

void cge::GUI::SettingsScreen::ReinitializeScreen() {
	this->_screen->initialize(this->_window.getGLFWWindow(), false);
	this->nanoguiWindow->center();
}
