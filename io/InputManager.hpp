#ifndef NEW_INPUTMANAGER_HPP
#define NEW_INPUTMANAGER_HPP

#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <unordered_map>

namespace cge {
	class InputManager {
	public:
		InputManager(const cge::Window& win);
		~InputManager() = default;

		void 	poolKeyEvnt();
		void	pressKey(int keysym);
		void	releaseKey(int keysym);
		void	setMouseCoordinates(const glm::vec2 &mouseCoordinates);
		void	setInputCallBacks();

		glm::vec2	getMouseCoordinates() const;
		bool 		isKeyPressed(int keysym) const;
		bool 		isExitCase() const;

	private:
		const cge::Window&				_window;

		bool 							_exitCase = false;
		std::unordered_map<int, bool>	_keyMap;
		glm::vec2						_mouseCoordinates;
	};
}

#endif //NEW_INPUTMANAGER_HPP
