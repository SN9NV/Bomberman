//
// Created by Owen EXALL on 2017/08/15.
//

#include "SettingsScreen.hpp"

cge::GUI::SettingsScreen::SettingsScreen(cge::Window &win, cge::GameState *_currState, Player *player) :
	_window(win),
	_player(player)
{
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
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Settings");
	nanogui::AdvancedGridLayout layout(
			{100, 100, 100, 100, 100},
			{100, 100, 100, 100, 50},
			5);
	nanoguiWindow->setLayout(&layout);

	nanogui::Button *btn_MainMenu = new nanogui::Button(nanoguiWindow, "Back");
	layout.setAnchor(btn_MainMenu, nanogui::AdvancedGridLayout::Anchor(0, 4,
		nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_MainMenu->setCallback([_currState] {
		*_currState = cge::GameState::PLAY_MENU;
	});

	nanogui::Button *btn_Save = new nanogui::Button(nanoguiWindow, "Save");
	layout.setAnchor(btn_Save, nanogui::AdvancedGridLayout::Anchor(4, 4,
		nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_Save->setCallback([&] {
		std::cout << "Save Game Here." << std::endl;
	});

	nanogui::TabWidget* tabs = nanoguiWindow->add<nanogui::TabWidget>();
	layout.setAnchor(tabs, nanogui::AdvancedGridLayout::Anchor(0, 0, 5, 4,
		nanogui::Alignment::Fill, nanogui::Alignment::Fill));

	nanogui::Widget* sounds = tabs->createTab("Sound Settings");
	sounds->setLayout(new nanogui::GroupLayout());

	/**SOUNDS: Master Volume**/
	new nanogui::Label(sounds, "Master Volume:", "sans-bold");
	nanogui::Widget *p_master = new nanogui::Widget(sounds);
	p_master->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	nanogui::Slider *sl_master = new nanogui::Slider(p_master);
	sl_master->setValue(0.5f); // set master volume here;
	sl_master->setFixedWidth(250);

	nanogui::TextBox *txtb_master = new nanogui::TextBox(p_master);
	txtb_master->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_master->setValue("50"); // set master volume here;
	txtb_master->setUnits("%");
	sl_master->setCallback([txtb_master](float value) {
		txtb_master->setValue(std::to_string((int) (value * 100)));
	});
	txtb_master->setFixedSize(nanogui::Vector2i(60,25));
	txtb_master->setFontSize(20);
	txtb_master->setAlignment(nanogui::TextBox::Alignment::Right);


	/**SOUNDS: Music Volume**/
	new nanogui::Label(sounds, "Music Volume:", "sans-bold");
	nanogui::Widget *p_music = new nanogui::Widget(sounds);
	p_music->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	nanogui::Slider *sl_music = new nanogui::Slider(p_music);
	sl_music->setValue(0.5f); // set music volume here;
	sl_music->setFixedWidth(250);

	nanogui::TextBox *txtb_music = new nanogui::TextBox(p_music);
	txtb_music->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_music->setValue("50"); // set music volume here;
	txtb_music->setUnits("%");
	sl_music->setCallback([txtb_music](float value) {
		txtb_music->setValue(std::to_string((int) (value * 100)));
	});
	txtb_music->setFixedSize(nanogui::Vector2i(60,25));
	txtb_music->setFontSize(20);
	txtb_music->setAlignment(nanogui::TextBox::Alignment::Right);

	/**SOUNDS: Music Volume**/
	new nanogui::Label(sounds, "Sound Effects Volume:", "sans-bold");
	nanogui::Widget *p_sfx = new nanogui::Widget(sounds);
	p_sfx->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	nanogui::Slider *sl_sfx = new nanogui::Slider(p_sfx);
	sl_sfx->setValue(0.5f); // set sfx volume here;
	sl_sfx->setFixedWidth(250);

	nanogui::TextBox *txtb_sfx = new nanogui::TextBox(p_sfx);
	txtb_sfx->setFixedSize(nanogui::Vector2i(60, 25));
	txtb_sfx->setValue("50"); // set sfx volume here;
	txtb_sfx->setUnits("%");
	sl_sfx->setCallback([txtb_sfx](float value) {
		txtb_sfx->setValue(std::to_string((int) (value * 100)));
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
	auto txtb_MoveUp = p_MoveUp->add<nanogui::TextBox>();
	txtb_MoveUp->setValue("W");//Change here to settings
	txtb_MoveUp->setEditable(true);
	txtb_MoveUp->setFixedWidth(35);
	/*txtb_MoveUp->setCallback([](const std::string &val) -> bool {
		std::cout << "Test: " << val << std::endl;
		return (true);
	});*/
	txtb_MoveUp->setFormat("[A-Z]");

	/**KEY-BINDINGS: Move Right**/
	nanogui::Widget* p_MoveRight = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveRight = p_MoveRight->add<nanogui::Label>("Move Right:");
	lbl_MoveRight->setFixedWidth(80);
	p_MoveRight->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	auto txtb_MoveRight = p_MoveRight->add<nanogui::TextBox>();
	txtb_MoveRight->setValue("D");//Change here to settings
	txtb_MoveRight->setEditable(true);
	txtb_MoveRight->setFixedWidth(35);
	txtb_MoveRight->setFormat("[A-Z]");

	/**KEY-BINDINGS: Move Down**/
	nanogui::Widget* p_MoveDown = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveDown = p_MoveDown->add<nanogui::Label>("Move Down:");
	lbl_MoveDown->setFixedWidth(80);
	p_MoveDown->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	auto txtb_MoveDown = p_MoveDown->add<nanogui::TextBox>();
	txtb_MoveDown->setValue("S");//Change here to settings
	txtb_MoveDown->setEditable(true);
	txtb_MoveDown->setFixedWidth(35);
	txtb_MoveDown->setFormat("[A-Z]");

	/**KEY-BINDINGS: Move Left**/
	nanogui::Widget* p_MoveLeft = keyBindings->add<nanogui::Widget>();
	auto lbl_MoveLeft = p_MoveLeft->add<nanogui::Label>("Move Left:");
	lbl_MoveLeft->setFixedWidth(80);
	p_MoveLeft->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6));
	auto txtb_MoveLeft = p_MoveLeft->add<nanogui::TextBox>();
	txtb_MoveLeft->setValue("A"); //Change here to settings
	txtb_MoveLeft->setEditable(true);
	txtb_MoveLeft->setFixedWidth(35);
	txtb_MoveLeft->setFormat("[A-Z]");

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