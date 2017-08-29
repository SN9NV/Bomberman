//
// Created by owen on 2017/08/10.
//

#include "MainMenuScreen.hpp"


cge::GUI::MainMenuScreen::MainMenuScreen(cge::Window &win,
										 cge::GameState *currState,
										 cge::GameState *prevState,
										 Player* player,
										 int* currMap,
										 cge::Loader& _loader) :
		_window(win),
		_player(player),
		_audioMouseEnter("../resources/audio/click.wav", _loader)
{
	this->_audioMouseEnter.setLooping(false);
	this->_audioMouseEnter.setGain(0.09f);

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

	cge::GUI::Custom::CustomButton *btn_NewGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "New Game");
	btn_NewGame->setTooltip("Starts a new game.");
	btn_NewGame->setFixedWidth(200);
	btn_NewGame->setCallback([currState, player, currMap] {
		*currState = cge::GameState::PLAY_GAME;
		player->setLives(3);
		player->setPauseMenue(false);
		player->setDamage(2);
		player->setScore(0);
		*currMap = 0;
	});
	btn_NewGame->setMouseEnterCallback([&] {
		this->_audioMouseEnter.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMouseEnter.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_LoadGame = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Load Game");
	btn_LoadGame->setTooltip("Options for loading game.");
	btn_LoadGame->setCallback([currState, prevState] {
		*prevState = *currState;
		*currState = cge::GameState::PLAY_LOAD;
	});
	btn_LoadGame->setMouseEnterCallback([&] {
		this->_audioMouseEnter.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMouseEnter.setPlaying();
	});

	cge::GUI::Custom::CustomButton *btn_Settings = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Settings");
	btn_Settings->setTooltip("Game Settings");
	btn_Settings->setCallback([currState, prevState] {
		*prevState = *currState;
		*currState = cge::GameState::PLAY_OPTS;
	});
	btn_Settings->setMouseEnterCallback([&] {
		this->_audioMouseEnter.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMouseEnter.setPlaying();
	});

	gui->addGroup("");
	cge::GUI::Custom::CustomButton *btn_Quit = new cge::GUI::Custom::CustomButton(nanoguiWindow, "Quit");
	btn_Quit->setTooltip("Quit the game.");
	btn_Quit->setCallback([currState] {
		*currState = cge::GameState::WANTS_QUIT;
	});
	btn_Quit->setMouseEnterCallback([&] {
		this->_audioMouseEnter.setGain(cge::Settings::Settings::getSingleton()->getSfxVolume());
		this->_audioMouseEnter.setPlaying();
	});

	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::MainMenuScreen::~MainMenuScreen() {
	delete this->_screen;
}

void cge::GUI::MainMenuScreen::drawScreen() {
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->_screen->drawContents();
	this->_screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::MainMenuScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, double x, double y) {
			 cge::GUI::MainMenuScreen *screen;
			 screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

			 screen->getScreen()->cursorPosCallbackEvent(x, y);
		 }
	);

	glfwSetMouseButtonCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int button, int action, int modifiers) {
		   cge::GUI::MainMenuScreen *screen;
		   screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
	   }
	);

	glfwSetKeyCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int key, int scancode, int action, int mods) {
		   cge::GUI::MainMenuScreen *screen;
		   screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
	   }
	);

	glfwSetCharCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, unsigned int codepoint) {
			cge::GUI::MainMenuScreen *screen;
			screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->charCallbackEvent(codepoint);
		}
	);

	glfwSetDropCallback(_window.getGLFWWindow(),
		[](GLFWwindow *win, int count, const char **filenames) {
			cge::GUI::MainMenuScreen *screen;
			screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

			screen->getScreen()->dropCallbackEvent(count, filenames);
		}
	);

	glfwSetScrollCallback(_window.getGLFWWindow(),
	  [](GLFWwindow *win, double x, double y) {
		  cge::GUI::MainMenuScreen *screen;
		  screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

		  screen->getScreen()->scrollCallbackEvent(x, y);
	  }
	);

	glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
	   [](GLFWwindow *win, int width, int height) {
		   cge::GUI::MainMenuScreen *screen;
		   screen = (cge::GUI::MainMenuScreen *) glfwGetWindowUserPointer(win);

		   screen->getScreen()->resizeCallbackEvent(width, height);
	   }
	);
}

nanogui::Screen *cge::GUI::MainMenuScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::MainMenuScreen::ReinitializeScreen() {
	this->_screen->initialize(this->_window.getGLFWWindow(), false);
	this->nanoguiWindow->center();
}

cge::GUI::MainMenuScreen::MainMenuScreen(const cge::GUI::MainMenuScreen &cpy) :
	_window(cpy._window),
	_player(cpy._player),
	_audioMouseEnter(cpy._audioMouseEnter)
{
	this->_screen = cpy._screen;
	this->nanoguiWindow = cpy.nanoguiWindow;
}

cge::GUI::MainMenuScreen cge::GUI::MainMenuScreen::operator=(const cge::GUI::MainMenuScreen &rhs) {
	*this = rhs;
	return (*this);
}
