#include <SDL_events.h>
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
	void InputManager::poolKeyEvnt() {
		SDL_Event	event = {};

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
		}
	}

	bool InputManager::isExitCase() const
	{
		return _exitCase;
	}
}