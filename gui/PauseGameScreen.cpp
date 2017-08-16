//
// Created by Owen Exall on 2017/08/16.
//

#include "PauseGameScreen.h"

cge::GUI::PauseGameScreen::PauseGameScreen(cge::Window &win, cge::GameState *_currState, Player *player) :
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
	nanogui::FormHelper *gui = new nanogui::FormHelper(_screen);
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Main Menu");
	nanoguiWindow->setLayout(new nanogui::GroupLayout());

	nanogui::Button *btn_ResumeGame = new nanogui::Button(nanoguiWindow, "Resume Game");
	btn_ResumeGame->setTooltip("Resumes the current game.");
	btn_ResumeGame->setFixedWidth(200);
	btn_ResumeGame->setCallback([_currState] {
		*_currState = cge::RESUME;
	});

	nanogui::Button *btn_NewGame = new nanogui::Button(nanoguiWindow, "New Game");
	btn_NewGame->setTooltip("Starts a new game.");
	btn_NewGame->setFixedWidth(200);
	btn_NewGame->setCallback([_currState, player] {
		*_currState = cge::GameState::PLAY_GAME;
		player->setLives(3);
		player->setPauseMenue(false);
	});

	nanogui::Button *btn_SaveGame = new nanogui::Button(nanoguiWindow, "Save Game");
	btn_SaveGame->setTooltip("Options for saving game.");
	btn_SaveGame->setCallback([_currState] { *_currState = cge::GameState::PLAY_SAVE; });

	nanogui::Button *btn_LoadGame = new nanogui::Button(nanoguiWindow, "Load Game");
	btn_LoadGame->setTooltip("Options for loading game.");
	btn_LoadGame->setCallback([_currState] { *_currState = cge::GameState::PLAY_LOAD; });

	nanogui::Button *btn_Settings = new nanogui::Button(nanoguiWindow, "Settings");
	btn_Settings->setTooltip("Game Settings");
	btn_Settings->setCallback([_currState] { *_currState = cge::GameState::PLAY_OPTS; });

	gui->addGroup("");
	nanogui::Button *btn_Quit = new nanogui::Button(nanoguiWindow, "Main Menu");
	btn_Quit->setTooltip("Go back to the main menu.");
	btn_Quit->setCallback([_currState] {
		*_currState = cge::GameState::PLAY_MENU;
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

void cge::GUI::PauseGameScreen::setInputCallbacks() {glfwSetWindowUserPointer(_window.getGLFWWindow(), nullptr);
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
