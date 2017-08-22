//
// Created by Owen Exall on 2017/08/16.
//

#include "PauseGameScreen.hpp"

cge::GUI::PauseGameScreen::PauseGameScreen(cge::Window &win, cge::GameState *_currState, cge::GameState* prevState, Player *player, int* currMap, cge::Loader& loader) :
		_window(win),
		_player(player),
		_audioMenuScroll("../resources/audio/click.wav", loader)
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
	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Main Menu");
	nanoguiWindow->setLayout(new nanogui::GroupLayout());

	cge::GUI::Custom::CustomButton *btn_ResumeGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Resume Game");
	btn_ResumeGame->setTooltip("Resumes the current game.");
	btn_ResumeGame->setFixedWidth(200);
	btn_ResumeGame->setCallback([_currState] {
		*_currState = cge::RESUME;
	});
	btn_ResumeGame->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_NewGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "New Game");
	btn_NewGame->setTooltip("Starts a new game.");
	btn_NewGame->setFixedWidth(200);
	btn_NewGame->setCallback([&, _currState, player, currMap] {
		auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
											  "New Game", "Any unsaved progress will be lost. Continue?", "Yes", "No",
											  true);
		dlg->setCallback([_currState, player, currMap](int result) {
			if (result == 0) {
				*_currState = cge::GameState::PLAY_GAME;
				player->setLives(3);
				player->setPauseMenue(false);
				player->setDamage(2);
				*currMap = 0;
			}
		});
	});
	btn_NewGame->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_SaveGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Save Game");
	btn_SaveGame->setTooltip("Options for saving game.");
	btn_SaveGame->setCallback([_currState] {
		*_currState = cge::GameState::PLAY_SAVE;
	});
	btn_SaveGame->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_LoadGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Load Game");
	btn_LoadGame->setTooltip("Options for loading game.");
	btn_LoadGame->setCallback([_currState, prevState] {
		*prevState = *_currState;
		*_currState = cge::GameState::PLAY_LOAD;
	});
	btn_LoadGame->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_Settings = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Settings");
	btn_Settings->setTooltip("Game Settings");
	btn_Settings->setCallback([_currState, prevState] {
		*prevState = *_currState;
		*_currState = cge::GameState::PLAY_OPTS;
	});
	btn_Settings->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	gui->addGroup("");
	cge::GUI::Custom::CustomButton *btn_Quit = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Main Menu");
	btn_Quit->setTooltip("Go back to the main menu.");
	btn_Quit->setCallback([&, _currState]{
		auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
											  "Back to Main", "Any unsaved progress will be lost. Continue?", "Yes",
											  "No", true);
		dlg->setCallback([_currState](int result) {
			if (result == 0) {
				*_currState = cge::GameState::PLAY_MENU;
			}
		});
	});
	btn_Quit->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_QuitToDesktop = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Quit to Desktop");
	btn_QuitToDesktop->setTooltip("Game Settings");
	btn_QuitToDesktop->setCallback([&, _currState] {
		auto dlg = new nanogui::MessageDialog(this->_screen, nanogui::MessageDialog::Type::Warning,
											  "Quit to Desktop?", "Any unsaved progress will be lost. Continue?", "Yes",
											  "No", true);
		dlg->setCallback([_currState](int result) {
			if (result == 0) {
				*_currState = cge::GameState::WANTS_QUIT;
			}
		});
	});
	btn_QuitToDesktop->setMouseEnterCallback([&] {
		this->_audioMenuScroll.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMenuScroll.setPlaying();
	});

	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::PauseGameScreen::~PauseGameScreen() {
	delete this->_screen;
}

nanogui::Screen *cge::GUI::PauseGameScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::PauseGameScreen::drawScreen() {
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->_screen->drawContents();
	this->_screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::PauseGameScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
		 [](GLFWwindow *win, double x, double y) {
			 cge::GUI::PauseGameScreen *screen;
			 screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

			 screen->getScreen()->cursorPosCallbackEvent(x, y);
		 }
	);

	glfwSetMouseButtonCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int button, int action, int modifiers) {
		   cge::GUI::PauseGameScreen *screen;
		   screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
	   }
	);

	glfwSetKeyCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int key, int scancode, int action, int mods) {
		   cge::GUI::PauseGameScreen *screen;
		   screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
	   }
	);

	glfwSetCharCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, unsigned int codepoint) {
			cge::GUI::PauseGameScreen *screen;
			screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->charCallbackEvent(codepoint);
		}
	);

	glfwSetDropCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, int count, const char **filenames) {
			cge::GUI::PauseGameScreen *screen;
			screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->dropCallbackEvent(count, filenames);
		}
	);

	glfwSetScrollCallback(_window.getGLFWWindow(),
	  [](GLFWwindow *win, double x, double y) {
		  cge::GUI::PauseGameScreen *screen;
		  screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

		  screen->getScreen()->scrollCallbackEvent(x, y);
	  }
	);

	glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int width, int height) {
		   cge::GUI::PauseGameScreen *screen;
		   screen = (cge::GUI::PauseGameScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->resizeCallbackEvent(width, height);
	   }
	);
}

void cge::GUI::PauseGameScreen::ReinitializeScreen() {
	this->_screen->initialize(this->_window.getGLFWWindow(), false);
	this->nanoguiWindow->center();
}
