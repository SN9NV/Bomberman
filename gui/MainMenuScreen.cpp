//
// Created by owen on 2017/08/10.
//

#include "MainMenuScreen.hpp"


cge::GUI::MainMenuScreen::MainMenuScreen(cge::Window &win, cge::GameState *currState, Player* player) :
		_window(win),
		_player(player)
{

	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Create a nanogui screen and pass the glfw pointer to initialize
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
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Main Menu");
	nanoguiWindow->setLayout(new nanogui::GroupLayout());

	nanogui::Button *btn_NewGame = new nanogui::Button(nanoguiWindow, "New Game");
	btn_NewGame->setTooltip("Starts a new game.");
	btn_NewGame->setWidth(200);
	btn_NewGame->setCallback([currState, player] {
		*currState = cge::GameState::PLAY_GAME;
		player->setLives(3);
	});

	nanogui::Button *btn_LoadGame = new nanogui::Button(nanoguiWindow, "Load Game");
	btn_LoadGame->setTooltip("Options for loading game.");

	nanogui::Button *btn_Settings = new nanogui::Button(nanoguiWindow, "Settings");
	btn_Settings->setTooltip("Game Settings");

	gui->addGroup("");
	nanogui::Button *btn_Quit = new nanogui::Button(nanoguiWindow, "Quit");
	btn_Quit->setTooltip("Quit the game.");
	btn_Quit->setCallback([currState] { *currState = cge::GameState::WANTS_QUIT; });

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
