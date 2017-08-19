//
// Created by Owen EXALL on 2017/08/15.
//

#ifndef BOMBERMAN_LOADGAME_HPP
#define BOMBERMAN_LOADGAME_HPP


#include <sys/stat.h>
#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "../io/audio/AudioSource.hpp"
#include <nanogui/nanogui.h>
#include "CustomButton.hpp"
#include "../extras/SavedGame.hpp"
#include "../io/settings/Settings.hpp"

namespace cge {
	namespace GUI {
		class LoadGameScreen {
		public:
			LoadGameScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, cge::Loader& loader, int* currMap);

			~LoadGameScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();

		private:
			LoadGameScreen();

			nanogui::Screen*	_screen;
			cge::Window&		_window;
			Player				*_player;
			cge::Audio::Source	_audioMenuScroll;
			int*				_currMap;
			cge::GameState*		_gameState;
			cge::GameState*		_prevState;
			std::map<int, cge::Saves::SavedGame*> _availableSaves;

			void				searchAvailableSaves();
			void				refreshSavedGames();
			void				loadGame(int slot);
			void				load(int slot);

			nanogui::TextBox *txtb_Slot1;
			nanogui::TextBox *txtb_Slot2;
			nanogui::TextBox *txtb_Slot3;
			nanogui::TextBox *txtb_Slot4;
			nanogui::TextBox *txtb_Slot5;
			nanogui::TextBox *txtb_Slot6;
		};
	}
}


#endif //BOMBERMAN_LOADGAME_HPP
