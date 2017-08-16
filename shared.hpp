//
// Created by owen on 2017/08/12.
//

#ifndef BOMBERMAN_SHARED_HPP
#define BOMBERMAN_SHARED_HPP

namespace cge {
	enum GameState {
		PLAY_GAME,
		PLAY_PAUSE,
		PLAY_MENU,
		PLAY_LOAD,
		PLAY_SAVE,
		PLAY_OPTS,
		WANTS_QUIT,
		RESUME
	};
}

#endif //BOMBERMAN_SHARED_HPP
