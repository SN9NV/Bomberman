//
// Created by Owen EXALL on 2017/08/15.
//

#ifndef BOMBERMAN_SETTINGSSCREEN_HPP
#define BOMBERMAN_SETTINGSSCREEN_HPP

#include <sstream>
#include <string>
#include "../io/Window.hpp"
#include "../shared.hpp"
#include "../BomberManGameLogic/Player.hpp"
#include <nanogui/nanogui.h>
#include "CustomButton.hpp"
#include "../io/audio/AudioSource.hpp"
#include "CustomTextbox.hpp"

namespace cge {
	namespace GUI {
		class SettingsScreen {
		public:
			SettingsScreen() = delete;
			SettingsScreen(cge::Window &win, cge::GameState *_currState, cge::GameState *prevState, Player *player, cge::Loader& loader);
			SettingsScreen(const SettingsScreen & cpy);
			SettingsScreen operator=(const SettingsScreen& rhs);
			~SettingsScreen();

			nanogui::Screen *getScreen();

			void drawScreen();

			void setInputCallbacks();
			void ReinitializeScreen();
		private:

			nanogui::ref<nanogui::Window> nanoguiWindow;
			nanogui::Screen *_screen;
			cge::Window &_window;
			Player *_player;
			cge::Audio::Source _audioMenuScroll;
			cge::GameState* _currState;
			cge::GameState* _prevState;
			bool			_changesMade;
			bool			_windowChangesMade;

			/**Sliders for Volume control**/
			nanogui::Slider *sl_master;
			nanogui::Slider *sl_music;
			nanogui::Slider *sl_sfx;

			/**Textboxes for Key Binding control**/
			std::string		charToString(int chr);
			Custom::CustomTextbox* txtb_MoveUp;
			Custom::CustomTextbox* txtb_MoveRight;
			Custom::CustomTextbox* txtb_MoveDown;
			Custom::CustomTextbox* txtb_MoveLeft;
			Custom::CustomTextbox* txtb_Detonate;

			std::map<std::string, Custom::CustomTextbox*> _txtbInputs;
			bool validateKeyBindings(const std::string& input, int key);

			/**Window Settings**/
			nanogui::CheckBox *chkbx_FullScreen;
			nanogui::ComboBox *cb_Resolution;

			void saveSettings();
		};
	};
};


#endif //BOMBERMAN_SETTINGSSCREEN_HPP
