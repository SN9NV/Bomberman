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
	PLAY = 1,
	WANTS_QUIT,
	FAIL,
	COMPLEAT,
	FAIL_MAP_LOAD,
};

class LevelRunner
{
private:
	std::vector<std::vector<cge::Entity *>> _level;
	std::vector<Being *> _beings;
	std::vector<Being *> _dead;
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
	int _balloons;
	int _onil;

	void beingWorldInteraction();
	void bombWorldInteraction();
	void loadMapEntitys();
	cge::Model *getModel(std::string name);
	void checkBeingBlast(int x, int y);
	bool checkWallBlast(int x, int y);
	void bumpBeing(Being *);
	void endlevel();
	bool checkMapWall();

public:
	int getState() const;
	LevelRunner(cge::Loader &_loader, Player *_player, const cge::Window &_window);
	int runLevel(std::string path);
//todo: move loadMapfrom file to private
	void loadMapFromFile(std::string path);
};


#endif //BOMBERMAN_LEVELRUNNNER_HPP
