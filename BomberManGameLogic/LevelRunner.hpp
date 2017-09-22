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
#include "../io/audio/AudioDevice.hpp"
#include "Onil.hpp"
#include "PowerUPAbstract.hpp"
#include "../rendering/SpriteRenderer.hpp"
#include "LevelFactory.hpp"
#include <chrono>
#include <thread>

enum levelState {
	PLAY = 1,
	WANTS_QUIT,
	FAIL,
	COMPLETE,
	FAIL_MAP_LOAD,
	PAUSE
};

/// Shield masks
enum Shield {
	UP		= (1u << 0),
	DOWN	= (1u << 1),
	LEFT	= (1u << 2),
	RIGHT	= (1u << 3)
};

class LevelRunner {
private:
	std::vector<std::vector<cge::Entity *> >	_level;
	std::vector<cge::Entity *>					_floors;
	std::vector<cge::Audio::Source *>			_sources;
	std::vector<Being *>						_beings;
	std::vector<Bomb *>							_bombs;
	std::vector<std::string>					_map;
	std::vector<cge::Entity *>					_batch;

	cge::Loader				&_loader;
	cge::Window				&_window;
	cge::InputManager		*_inputManager;
	cge::GLSLProgram		_entShader;
	cge::GLSLProgram		_partShader;
	cge::Renderer			_renderer;
	cge::Camera				_camera;
	cge::ParticalRenderer	_particalRenderer;
	cge::TextRenderer		_textRenderer;
	cge::SpriteRenderer		_spriteRenderer;
	cge::Sprite				_life;
	cge::Sprite				_timer;
	cge::Audio::Device		_audioDevice;

	Player			*_player;
	Gate			*_gate;
	LevelFactory	_objtLoader;

	PowerUPAbstract	*_powerUpInstance;
	unsigned		_levelTime;
	int				_state = levelState::PLAY;
	int				_dwalls;
	int				_balloons;
	int				_onil;
	int				_ovapi;
	bool			_powerup;

	void	beingWorldInteraction();
	void	bombWorldInteraction();
	void	loadMapEntitys();
	void	checkBeingBlast(float x, float y);
	bool	checkWallBlast(float x, float y);
	void	checkBombBlast(float x, float y);
	void	bumpBeing(Being *begin);
	void	endLevel();
	bool	checkMapWall();
	void	runLevelLoop();
	void	fireEffect(const glm::vec3 &position, size_t numParticals);
	void	portalActiveEffect(const glm::vec3 &position, size_t numParticals);
	void	portalUseEffect(const glm::vec3 &position, size_t numParticals);
	void	wallBrakeEffect(const glm::vec3 &position, size_t numParticals);
	void	checkGateDamage(const glm::vec3 &position, Being *being);
	void	placeBeing(Being *being);
	void	cleanLevel();
	void	update();
	void	render();
	void	loadMapFromFile(const std::string &path);
	void	rotatePowerUp();

public:
	LevelRunner(cge::Loader &_loader, Player *_player, cge::Window &_window, cge::InputManager *inputManager, cge::Audio::Device &audioDevice);

	int		getState() const;
	int		runLevel(const std::string &path);
	int		resumeLevel();
	void	DrawEOGCredits();
};

#endif //BOMBERMAN_LEVELRUNNNER_HPP
