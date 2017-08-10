//
// Created by owen on 2017/08/10.
//

#include <iostream>
#include "MainMenuScreen.hpp"

cge::GUI::MainMenuScreen::MainMenuScreen(cge::Window &win) {
	this->screen = new nanogui::Screen(win.getSDLWindow(),
		nanogui::Vector2i(win.getWidth(), win.getHeight()),
		"NanoGUI test");

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

	bool enabled = true;
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen);
    nanogui::Window* rwindow = gui->addWindow(Eigen::Vector2i(10, 10), "Form helper example");
    gui->addGroup("Basic types");
    gui->addVariable("bool", bvar);
	gui->addVariable("string", strval);

	gui->addGroup("Validating fields");
    gui->addVariable("int", ivar);
    gui->addVariable("float", fvar);
    gui->addVariable("double", dvar);

    gui->addGroup("Complex types");
    gui->addVariable("Enumeration", enumval, enabled)
       ->setItems({"Item 1", "Item 2", "Item 3"});
    gui->addVariable("Color", colval);

    gui->addGroup("Other widgets");
    gui->addButton("A button", [](){ std::cout << "Button pressed." << std::endl; });

    screen->setVisible(true);
    screen->performLayout();
	rwindow->center();
}

cge::GUI::MainMenuScreen::~MainMenuScreen() {
	delete screen;
}

void cge::GUI::MainMenuScreen::drawScreen() {
	this->screen->drawAll();
}
