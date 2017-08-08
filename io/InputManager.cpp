#include "InputManager.hpp"

void cge::InputManager::pressKey(int keysym) {
	this->_keyMap[keysym] = true;
}

void cge::InputManager::releaseKey(int keysym) {
	this->_keyMap[keysym] = false;
}

void cge::InputManager::setMouseCoordinates(const glm::vec2 &mouseCoordinates) {
	this->_mouseCoordinates = mouseCoordinates;
}

glm::vec2 cge::InputManager::getMouseCoordinates() const {
	return this->_mouseCoordinates;
}

bool cge::InputManager::isKeyPressed(int keysym) const {
	auto it = this->_keyMap.find(keysym);

	return (it != this->_keyMap.end()) ? it->second : false;
}