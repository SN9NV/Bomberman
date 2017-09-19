//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_PAUSEGAMESCREEN_H
#define BOMBERMAN_PAUSEGAMESCREEN_H

#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "../io/audio/AudioSource.hpp"
#include <nanogui/nanogui.h>
#include "CustomButton.hpp"
#include "../io/settings/Settings.hpp"

namespace cge {
	namespace GUI {
		class PauseGameScreen {
		public:
			PauseGameScreen() = delete;
			PauseGameScreen(cge::Window& win, cge::GameState* _currState, cge::GameState* prevState, Player *player, int* currMap, cge::Loader& loader);
			PauseGameScreen(const PauseGameScreen & cpy);
			PauseGameScreen &operator=(const PauseGameScreen & rhs) = default;
			~PauseGameScreen();

			nanogui::Screen* getScreen();

			void drawScreen();
			void setInputCallbacks();
			void ReinitializeScreen();
		private:

			nanogui::ref<nanogui::Window> nanoguiWindow;
			nanogui::Screen* 	_screen;
			cge::Window&		_window;
			Player*				_player;
			cge::Audio::Source	_audioMenuScroll;
		};
	}
};


#endif //BOMBERMAN_PAUSEGAMESCREEN_H
