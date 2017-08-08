#ifndef NEW_INPUTMANAGER_HPP
#define NEW_INPUTMANAGER_HPP


#include <glm/vec2.hpp>
#include <unordered_map>

namespace cge {
	class InputManager {
	public:
		InputManager() = default;
		~InputManager() = default;

		void	pressKey(int keysym);
		void	releaseKey(int keysym);
		void	setMouseCoordinates(const glm::vec2 &mouseCoordinates);

		glm::vec2	getMouseCoordinates() const;
		bool 		isKeyPressed(int keysym) const;

	private:
		std::unordered_map<int, bool>	_keyMap;
		glm::vec2						_mouseCoordinates;
	};
}

#endif //NEW_INPUTMANAGER_HPP
