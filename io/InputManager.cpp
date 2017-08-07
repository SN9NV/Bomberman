#include "InputManager.hpp"

namespace cge {
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
}