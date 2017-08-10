//
// Created by Owen EXALL on 2017/08/10.
//

#ifndef BOMBERMAN_GUIMANAGER_HPP
#define BOMBERMAN_GUIMANAGER_HPP

#include "../io/Window.hpp"

namespace cge {
	class GuiManager {
	public:
		static cge::GuiManager* getSingleton(cge::Window& win);

		GuiManager(cge::Window& win);
		~GuiManager();

	private:
		static cge::GuiManager*	s_instance;

		cge::Window&			_sdlWindow;
	};
}


#endif //BOMBERMAN_GUIMANAGER_HPP
