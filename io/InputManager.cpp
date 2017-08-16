
#include "InputManager.hpp"

namespace cge {
	InputManager::InputManager(const cge::Window& win) :
		_window(win)
	{

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

	void InputManager::pollKeyEvnt() {
		this->setInputCallBacks();
		glfwPollEvents();
	}

	bool InputManager::isExitCase() const
	{
		return _exitCase;
	}

	void InputManager::setInputCallBacks() {
		/*These are all the menu's callbacks. Set them to null
		 * so that they aren't called during game play.*/
		glfwSetCursorPosCallback(_window.getGLFWWindow(),nullptr);
		glfwSetMouseButtonCallback(_window.getGLFWWindow(), nullptr);
		//glfwSetKeyCallback(_window.getGLFWWindow(), nullptr); // Changing this one.
		glfwSetCharCallback(_window.getGLFWWindow(), nullptr);
		glfwSetDropCallback(_window.getGLFWWindow(), nullptr);
		glfwSetScrollCallback(_window.getGLFWWindow(), nullptr);
		glfwSetFramebufferSizeCallback(_window.getGLFWWindow(), nullptr);

		glfwSetWindowUserPointer(this->_window.getGLFWWindow(), nullptr);
		glfwSetWindowUserPointer(this->_window.getGLFWWindow(), this);

		glfwSetKeyCallback(this->_window.getGLFWWindow(),
        [](GLFWwindow *glfwWindow, int key, int scancode, int action, int mods) {
			(void)scancode;
			(void)mods;
			cge::InputManager* iManager = (cge::InputManager*)glfwGetWindowUserPointer(glfwWindow);

			/*std::cout << "Key:      " << key << std::endl
					  << "ScanCode: " << scancode << std::endl
					  << "Action:   " << action << std::endl
					  << "Mods:     " << mods << std::endl;*/

			if (action == GLFW_PRESS || action == GLFW_REPEAT)
				iManager->pressKey(key);
			else if (action == GLFW_RELEASE)
				iManager->releaseKey(key);
        });
	}
}