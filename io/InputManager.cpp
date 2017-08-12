
#include "InputManager.hpp"

namespace cge {
	InputManager::InputManager(const cge::Window& win) :
		_window(win)
	{
		glfwSetWindowUserPointer(win.getGLFWWindow(), this);

		glfwSetKeyCallback(win.getGLFWWindow(),
        [](GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
			(void)scancode;
			(void)mods;
			cge::InputManager* iManager = (cge::InputManager*)glfwGetWindowUserPointer(glfwWindow);

			std::cout << "Key:      " << key << std::endl
					  << "ScanCode: " << scancode << std::endl
					  << "Action:   " << action << std::endl
					  << "Mods:     " << mods << std::endl;

			if (key == GLFW_KEY_ESCAPE)
				iManager->_exitCase = true;

			if (action == GLFW_PRESS || action == GLFW_REPEAT)
				iManager->pressKey(key);
			else if (action == GLFW_RELEASE)
				iManager->releaseKey(key);
        });
	}

	void InputManager::pressKey(int keysym) {
		this->_keyMap[keysym] = true;
	}

	void InputManager::releaseKey(int keysym) {
		this->_keyMap[keysym] = false;
	}

	void InputManager::setMouseCoordinates(const glm::vec2 &mouseCoordinates) {
		this->_mouseCoordinates = mouseCoordinates;
	}

	glm::vec2 InputManager::getMouseCoordinates() const {
		return this->_mouseCoordinates;
	}

	bool InputManager::isKeyPressed(int keysym) const {
		auto it = this->_keyMap.find(keysym);

		return (it != this->_keyMap.end()) ? it->second : false;
	}

	void InputManager::poolKeyEvnt() {
		/*SDL_Event	event = {};

		while (SDL_PollEvent(&event) > 0) {
			switch (event.type) {
				case SDL_QUIT:
					_exitCase = true;
				case SDL_KEYDOWN:
					if (event.key.repeat == 0) {
						this->pressKey(event.key.keysym.sym);
					}
					break;
				case SDL_KEYUP:
					this->releaseKey(event.key.keysym.sym);
					break;
				default:
					break;
			}
		}*/
		glfwPollEvents();
	}

	bool InputManager::isExitCase() const
	{
		return _exitCase;
	}
}