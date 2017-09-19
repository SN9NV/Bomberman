//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUIMANAGER_HPP
#define BOMBERMAN_GUIMANAGER_HPP

#include "../io/Window.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include "MainMenuScreen.hpp"
#include "SettingsScreen.hpp"
#include "LoadGameScreen.hpp"
#include "SaveGameScreen.hpp"
#include "PauseGameScreen.hpp"
#include "../BomberManGameLogic/LevelRunner.hpp"

namespace cge {
	class GuiManager {
	public:
		static bool	initialise(cge::Window& win, cge::GameState *state, cge::GameState *prevState, Player *player, int *currMap, cge::Loader &loader);

		GuiManager() = delete;
		explicit GuiManager(cge::Window &win, cge::GameState *state, cge::GameState *prevState, Player *player, int *currMap, cge::Loader &loader);

		static GuiManager	*getSingleton();

		GuiManager(const GuiManager &cpy);
		GuiManager operator=(const GuiManager &rhs);
		~GuiManager();

		void drawScreen(int screen);

		void ReinitializeScreens();

	private:
		static cge::GuiManager	*s_instance;

		cge::Window				&_window;
		cge::GameState			*_prevState;
		cge::GameState			*_state;
		Player					*_player;
		int						*_currMap;

		cge::GUI::MainMenuScreen	*_mainMenuScreen;
		cge::GUI::SettingsScreen	*_settingsScreen;
		cge::GUI::LoadGameScreen	*_loadGameScreen;
		cge::GUI::SaveGameScreen	*_saveGameScreen;
		cge::GUI::PauseGameScreen	*_pauseGameScreen;
	};
}

#endif //BOMBERMAN_GUIMANAGER_HPP
