//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_LEVELRUNNNER_HPP
#define BOMBERMAN_LEVELRUNNNER_HPP


#include "../entites/Model.hpp"
#include "Bomb.hpp"
#include "Being.h"
#include "Player.hpp"
#include "../entites/Camera.hpp"
#include "Gate.hpp"


enum levelState
{
	PLAY,
	PLAY_MENU,
	WANTS_QUIT,
	FAIL,
	COMPLEAT
};

class LevelRunner
{
private:
	std::vector<std::vector<cge::Entity *>> _level;
	std::vector<Being *> _beings;
	std::vector<Bomb *> _bombs;
	std::map<std::string, cge::Model> _models;
	std::vector<std::string> _map;
	cge::Loader &_loader;
	Player *_player;
	Gate	*_gate;
	cge::Window _window;
	cge::GLSLProgram _shader;
	cge::InputManager _inputManager;
	cge::Renderer _renderer;
	cge::Camera _camera;
	int _state = levelState::PLAY;
	int _dwalls;

	void beingWorldInteraction();
	void bombWorldInteraction();
	void loadMapEntitys();
	cge::Model *getModel(std::string name);
	void checkBeingBlast(int x, int y);
	void checkWallBlast(int x, int y);
	void bumpBeing(Being *);
	void endlevel();

public:
	LevelRunner(cge::Loader &_loader, Player *_player, const cge::Window &_window);
	int runLevel(std::vector<std::string> map);
};


#endif //BOMBERMAN_LEVELRUNNNER_HPP
