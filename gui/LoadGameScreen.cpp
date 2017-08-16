//
// Created by Owen EXALL on 2017/08/15.
//

#include "LoadGameScreen.hpp"

cge::GUI::LoadGameScreen::LoadGameScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player) :
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
	nanogui::ref<nanogui::Window> nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Load Game");
	nanogui::AdvancedGridLayout layout(
			{100, 100, 100, 100, 100},
			{100, 100, 100, 100, 50},
			5);
	nanoguiWindow->setLayout(&layout);

	nanogui::Button *btn_MainMenu = new nanogui::Button(nanoguiWindow, "Back");
	layout.setAnchor(btn_MainMenu, nanogui::AdvancedGridLayout::Anchor(0, 4,
			nanogui::Alignment::Middle, nanogui::Alignment::Middle));
	btn_MainMenu->setCallback([_currState, prevState] {
		*_currState = *prevState;
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
	nanogui::TextBox *txtb_Slot1 = new nanogui::TextBox(p_slot1);
	txtb_Slot1->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot1->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot1 = new nanogui::Button(p_slot1, "Load");
	btn_SaveSlot1->setTooltip("Load Game on Slot 1");

	/**Slot 2**/
	nanogui::Widget *p_slot2 = new nanogui::Widget(saves);
	p_slot2->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot2, "Slot 2)", "sans-bold");
	nanogui::TextBox *txtb_Slot2 = new nanogui::TextBox(p_slot2);
	txtb_Slot2->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot2->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot2 = new nanogui::Button(p_slot2, "Load");
	btn_SaveSlot2->setTooltip("Load Game on Slot 2");

	/**Slot 3**/
	nanogui::Widget *p_slot3 = new nanogui::Widget(saves);
	p_slot3->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot3, "Slot 3)", "sans-bold");
	nanogui::TextBox *txtb_Slot3 = new nanogui::TextBox(p_slot3);
	txtb_Slot3->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot3->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot3 = new nanogui::Button(p_slot3, "Load");
	btn_SaveSlot3->setTooltip("Load Game on Slot 3");

	/**Slot 4**/
	nanogui::Widget *p_slot4 = new nanogui::Widget(saves);
	p_slot4->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot4, "Slot 4)", "sans-bold");
	nanogui::TextBox *txtb_Slot4 = new nanogui::TextBox(p_slot4);
	txtb_Slot4->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot4->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot4 = new nanogui::Button(p_slot4, "Load");
	btn_SaveSlot4->setTooltip("Load Game on Slot 4");

	/**Slot 5**/
	nanogui::Widget *p_slot5 = new nanogui::Widget(saves);
	p_slot5->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot5, "Slot 5)", "sans-bold");
	nanogui::TextBox *txtb_Slot5 = new nanogui::TextBox(p_slot5);
	txtb_Slot5->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot5->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot5 = new nanogui::Button(p_slot5, "Load");
	btn_SaveSlot5->setTooltip("Load Game on Slot 5");

	/**Slot 6**/
	nanogui::Widget *p_slot6 = new nanogui::Widget(saves);
	p_slot6->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 20));

	new nanogui::Label(p_slot6, "Slot 6)", "sans-bold");
	nanogui::TextBox *txtb_Slot6 = new nanogui::TextBox(p_slot6);
	txtb_Slot6->setFixedSize(nanogui::Vector2i(250, 25));
	txtb_Slot6->setValue("[Empty]");
	nanogui::Button *btn_SaveSlot6 = new nanogui::Button(p_slot6, "Load");
	btn_SaveSlot6->setTooltip("Load Game on Slot 6");

	_screen->setVisible(true);
	_screen->performLayout();
	nanoguiWindow->center();
}

cge::GUI::LoadGameScreen::~LoadGameScreen() {
	delete this->_screen;
}

nanogui::Screen *cge::GUI::LoadGameScreen::getScreen() {
	return (this->_screen);
}

void cge::GUI::LoadGameScreen::drawScreen() {
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
