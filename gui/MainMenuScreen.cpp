//
// Created by owen on 2017/08/10.
//

#include <iostream>
#include "MainMenuScreen.hpp"

cge::GUI::MainMenuScreen::MainMenuScreen(cge::Window &win) :
	_window(win)
{
	this->screen = new nanogui::Screen();
	this->screen->initialize(win.getGLFWWindow(), true);

	enum test_enum {
		Item1 = 0,
		Item2,
		Item3
	};

	bool bvar = true;
	int ivar = 12345678;
	double dvar = 3.1415926;
	float fvar = (float)dvar;
	std::string strval = "A string";
	test_enum enumval = Item2;
	nanogui::Color colval(0.5f, 0.5f, 0.7f, 1.f);

    int width, height;
	glfwGetFramebufferSize(win.getGLFWWindow(), &width, &height);
    glViewport(0, 0, width, height);

	//create NanoGUI
	bool enabled = true;
	nanogui::FormHelper *gui = new nanogui::FormHelper(this->screen);
	nanogui::ref<nanogui::Window> nanoguiWindow =
			gui->addWindow(Eigen::Vector2i(this->_window.getWidth(),
					this->_window.getHeight()),
					"Main Menu");



	gui->addGroup("Basic types");
    gui->addVariable("bool", bvar)->setTooltip("Test tooltip.");
    gui->addVariable("string", strval);

    gui->addGroup("Validating fields");
    gui->addVariable("int", ivar)->setSpinnable(true);
    gui->addVariable("float", fvar)->setTooltip("Test.");
    gui->addVariable("double", dvar)->setSpinnable(true);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)->setItems({ "Item 1", "Item 2", "Item 3" });
    gui->addVariable("Color", colval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", []() { std::cout << "Button pressed." << std::endl; })->setTooltip("Testing a much longer tooltip, that will wrap around to new lines multiple times.");;

    screen->setVisible(true);
    screen->performLayout();
    nanoguiWindow->center();

	this->setInputCallbacks();
}

cge::GUI::MainMenuScreen::~MainMenuScreen() {
	delete screen;
}

void cge::GUI::MainMenuScreen::drawScreen() {
	glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();

	this->screen->drawContents();
	this->screen->drawWidgets();

	_window.swapBuffers();
}

void cge::GUI::MainMenuScreen::setInputCallbacks() {
	glfwSetWindowUserPointer(_window.getGLFWWindow(), this);

	glfwSetCursorPosCallback(_window.getGLFWWindow(),
            [](GLFWwindow *win, double x, double y) {
			cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->cursorPosCallbackEvent(x, y);
        }
    );

     glfwSetMouseButtonCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, int button, int action, int modifiers) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->mouseButtonCallbackEvent(button, action, modifiers);
        }
    );

    glfwSetKeyCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, int key, int scancode, int action, int mods) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->keyCallbackEvent(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, unsigned int codepoint) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, int count, const char **filenames) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->dropCallbackEvent(count, filenames);
        }
    );

    glfwSetScrollCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, double x, double y) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->scrollCallbackEvent(x, y);
       }
    );

    glfwSetFramebufferSizeCallback(_window.getGLFWWindow(),
        [](GLFWwindow *win, int width, int height) {
            cge::GUI::MainMenuScreen* screen;
			screen = (cge::GUI::MainMenuScreen*)glfwGetWindowUserPointer(win);

            screen->getScreen()->resizeCallbackEvent(width, height);
        }
    );
}

nanogui::Screen *cge::GUI::MainMenuScreen::getScreen() {
	return (this->screen);
}
