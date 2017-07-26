#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <vector>
#include <unordered_map>
#include <SDL2/SDL_keycode.h>

template<class T>
class InputManager {
	public:
		struct KeyCB {
			bool	enabled;
			int		keysym;
			void	(*callback)(T *);
		};

		InputManager();
		InputManager(T *mainGame) {
			this->_MainGame = mainGame;
		}

		void	registerInput(int keysym, void (*callback)(T*), bool isEnabled = true) {
			this->_callbacks.push_back({ isEnabled, keysym, callback });
		}

		void	unregisterAll(void) {
			this->_callbacks.clear();
		}

		void	enableKey(int keysym, bool isEnabled = true) {
			for (auto &cb : this->_callbacks) {
				if (cb.keysym == keysym) {
					cb.enabled = isEnabled;
				}
			}
		}

		void	enableAllKeys(bool isEnabled = true) {
			for (auto &cb : this->_callbacks) {
				cb.enabled = isEnabled;
			}
		}

		void	processInput() {
			for (auto &cb : this->_callbacks) {
				if (this->isKeyPressed(cb.keysym)) {
					cb.callback(this->_MainGame);
				}
			}
		}

		void	pressKey(int keysym) {
			this->_keyMap[keysym] = true;
		}

		void	releaseKey(int keysym) {
			this->_keyMap[keysym] = false;
		}

		bool	isKeyPressed(int keysym) {
			auto it = this->_keyMap.find(keysym);

			if (it != this->_keyMap.end()) {
				return it->second;
			} else {
				return false;
			}
		}

	private:
		T								*_MainGame;
		std::unordered_map<int, bool>	_keyMap;
		std::vector<KeyCB>				_callbacks;
};

#endif // INPUTMANAGER_HPP
