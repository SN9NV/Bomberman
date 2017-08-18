//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_SAVEGAMESCREEN_H
#define BOMBERMAN_SAVEGAMESCREEN_H

#include <sys/stat.h>
#include <time.h>
#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "../io/audio/AudioSource.hpp"
#include <nanogui/nanogui.h>
#include "CustomButton.hpp"
#include "../extras/SavedGame.hpp"

namespace cge {
	namespace GUI {
		class SaveGameScreen {
		public:
			SaveGameScreen(cge::Window
			&win,
			cge::GameState *_currState, Player
			*player,
			cge::Loader& loader);

			~SaveGameScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			SaveGameScreen();

			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
			cge::Audio::Source _audioMenuScroll;
			std::map<int, cge::Saves::SavedGame*> _availableSaves;

			void searchAvailableSaves();
			void saveGame(int slot);
		};
	};
};


#endif //BOMBERMAN_SAVEGAMESCREEN_H
