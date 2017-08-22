//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_LEVELRUNNNER_HPP
#define BOMBERMAN_LEVELRUNNNER_HPP


#include "../entites/Model.hpp"
#include "../rendering/TextRenderer.hpp"
#include "Bomb.hpp"
#include "Being.hpp"
#include "Player.hpp"
#include "../entites/Camera.hpp"
#include "Gate.hpp"
#include "../rendering/ParticalRenderer.hpp"
#include "PowerUPInterface.hpp"


enum levelState
{
	PLAY = 1,
	WANTS_QUIT,
	FAIL,
	COMPLEAT,
	FAIL_MAP_LOAD,
	PAUSE
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
	cge::Window &_window;
	cge::GLSLProgram _entShader;
	cge::GLSLProgram _partShader;
	cge::InputManager *_inputManager;
	cge::Renderer _renderer;
	cge::Camera _camera;
	cge::ParticalRenderer _particalRenderer;
	unsigned _levelTime;
	int _state = levelState::PLAY;
	int _dwalls;
	int _balloons;
	int _onil;
	bool _powerup;
	PowerUPInterface *_powerUpInstance;

	void beingWorldInteraction();
	void bombWorldInteraction();
	void loadMapEntitys();
	cge::Model *getModel(std::string name);
	void checkBeingBlast(int x, int y);
	bool checkWallBlast(int x, int y);
	void bumpBeing(Being *);
	void endLevel();
	bool checkMapWall();
	void runLevelLoop();
	void fireEffect(glm::vec3 position, size_t numParticals);
	void portalActiveEffect(glm::vec3 position, size_t numParticals);
	void portalUseEffect(glm::vec3 position, size_t numParticals);
	void wallBrakeEffect(glm::vec3 position, size_t numParticals);
	void checkGateDamage(glm::vec3 position, Being *being);
	void cleanLevel();
	void update();
	void render();

public:
	int getState() const;
	LevelRunner(cge::Loader &_loader, Player *_player, cge::Window &_window, cge::InputManager *inputManager);
	int runLevel(const std::string &path);
    int resumeLevel();
//todo: move loadMapfrom file to private
	void loadMapFromFile(const std::string &path);
};


#endif //BOMBERMAN_LEVELRUNNNER_HPP
