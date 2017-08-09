//
// Created by owen on 2017/08/09.
//

#ifndef BOMBERMAN_OPTIONSSCREEN_HPP
#define BOMBERMAN_OPTIONSSCREEN_HPP

#include "../sounds/Sounds.hpp"
#include "../io/Window.hpp"
#include "GUI.hpp"

namespace cge {
	class OptionsScreen {
	public:
		OptionsScreen(cge::Window& win, int *gameState, int *prevState, cge::Sounds* snds);;

		~OptionsScreen();

		void DrawScreen();

	private:
		OptionsScreen();

		int*				_prevGameState;
		int*				_gameState;
		cge::Sounds*		_sounds;
		cge::Window&		_sdlWindow;
		cge::GUI			_gui;

		void				_processInput(void);
		void				_initUI(void);
		void				_registerHandlers(void);

		CEGUI::PushButton*	btn_MainMenu;
		CEGUI::PushButton*	btn_Save;
		CEGUI::Slider*		sl_MusicVolume;
		CEGUI::Slider*		sl_SfxVolume;
		CEGUI::Window*		lbl_CurrMusicVolume;
		CEGUI::Window*		lbl_CurrSfxVolume;

		bool				btn_All_EnterArea(const CEGUI::EventArgs& e);
		bool				btn_MainMenu_Clicked(const CEGUI::EventArgs& e);
		bool				btn_Save_Clicked(const CEGUI::EventArgs& e);
		bool 				sl_MusicVolume_ValueChanged(const CEGUI::EventArgs& e);
		bool				sl_SfxVolume_ValueChanged(const CEGUI::EventArgs& e);

		void				_updateValue();
	};
};


#endif //BOMBERMAN_OPTIONSSCREEN_HPP
