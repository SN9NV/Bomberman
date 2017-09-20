//
// Created by rojones on 2017/08/09.
//

#include "LevelRunner.hpp"
#include "DestructWall.hpp"
#include "Gate.hpp"
#include "Balloon.hpp"
#include "../extras/Maths.hpp"
#include "Wall.hpp"
#include "../io/audio/AudioSource.hpp"
#include "FireUp.hpp"
#include "FireDown.hpp"
#include "FullFire.hpp"
#include "WingBoot.hpp"
#include "AddBomb.hpp"

LevelRunner::LevelRunner(cge::Loader &loader, Player *player, cge::Window &window, cge::InputManager *inputManager, cge::Audio::Device &audioDevice) :
		_loader(loader),
		_window(window),
		_inputManager(inputManager),
		_entShader("shaders/vertex.glsl", "shaders/fragment.glsl"),
		_partShader("shaders/particalVertex.glsl", "shaders/particalFragment.glsl"),
		_renderer(_entShader),
		_camera({0.0f, 5.0f, 0.0f}, {1.5f, 0.0f, 0.0f}, _window),
		_particalRenderer(_partShader),
		_life({20, window.getHeight() - 100}, {48, 48}, 1, _loader.loadTexture("resources/Textures/Heart.png")),
		_timer({window.getWidth() - (5 * 48), window.getHeight() - 100}, {48, 48}, 1, _loader.loadTexture("resources/Textures/StopWatch.png")),
		_audioDevice(audioDevice),
		_player(player),
		_gate(nullptr),
		_objtLoader(loader, _level, *player),
		_powerUpInstance(nullptr),
		_balloons(0),
		_onil(0),
		_ovapi(0),
		_powerup(false)
{
	_particalRenderer.addParticalTexture(_loader.loadTextureAtlas("resources/TextureAtlas/FireBallAtlas.png", 4), GL_SRC_ALPHA, GL_ONE);
	_particalRenderer.addParticalTexture(_loader.loadTextureAtlas("resources/Textures/ConcreatFragment.png", 1), GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_particalRenderer.addParticalTexture(_loader.loadTextureAtlas("resources/TextureAtlas/PortalEffect.png", 2), GL_SRC_ALPHA, GL_ONE);

	this->_player->setAnimationSpeed(2.6f);
}

void LevelRunner::bumpBeing(Being *being) {
	glm::vec3 pos = being->getPosition();
	int x = roundf(pos.x);
	int y = roundf(pos.z);

	//collision box up
	if ((y - 1) > -1 && _level[y - 1][x] != nullptr) {
		if (!being->isWallPass() || (dynamic_cast<DestructWall *>(_level[y - 1][x])) == nullptr) {
			float minBoxDist = being->getHitBoxRadius() + _level[y - 1][x]->getHitBoxRadius();
			float dist = fabsf(_level[y - 1][x]->getPosition().z - pos.z);

			if (dist < minBoxDist) {
				being->setPosition({being->getPosition().x, 0, being->getPosition().z + (minBoxDist - dist)});
				being->setMoveDir({0, 0, 0});
			}
		}
	}

	//collision box down
	if (y + 1 < static_cast<int>(_level.size()) && _level[y + 1][x] != nullptr) {
		if (!being->isWallPass() || (dynamic_cast<DestructWall *>(_level[y + 1][x])) == nullptr) {
			float minBoxDist = being->getHitBoxRadius() + _level[y + 1][x]->getHitBoxRadius();
			float dist = fabsf(_level[y + 1][x]->getPosition().z - pos.z);

			if (dist < minBoxDist) {
				being->setPosition({being->getPosition().x, 0, being->getPosition().z - (minBoxDist - dist)});
				being->setMoveDir({0, 0, 0});
			}
		}
	}

	//collision box left
	if (x - 1 > -1 && _level[y][x - 1] != nullptr) {
		if (!being->isWallPass() || (dynamic_cast<DestructWall *>(_level[y][x - 1])) == nullptr) {
			float minBoxDist = being->getHitBoxRadius() + _level[y][x - 1]->getHitBoxRadius();
			float dist = fabsf(_level[y][x - 1]->getPosition().x - pos.x);

			if (dist < minBoxDist) {
				being->setPosition({being->getPosition().x + (minBoxDist - dist), 0, being->getPosition().z});
				being->setMoveDir({0, 0, 0});
			}
		}
	}

	//collision box right
	if (x + 1 < static_cast<int>(_level[y].size()) && _level[y][x + 1] != nullptr) {
		if (!being->isWallPass() || (dynamic_cast<DestructWall *>(_level[y][x + 1])) == nullptr) {
			float minBoxDist = being->getHitBoxRadius() + _level[y][x + 1]->getHitBoxRadius();
			float dist = fabsf(_level[y][x + 1]->getPosition().x - pos.x);

			if (dist < minBoxDist) {
				being->setPosition({being->getPosition().x - (minBoxDist - dist), 0, being->getPosition().z});
				being->setMoveDir({0, 0, 0});
			}
		}
	}
}

void LevelRunner::beingWorldInteraction() {
	auto being = _beings.begin();
	while (being != _beings.end()) {
		glm::vec3 oldpos = (*being)->getPosition();

		if (!(*being)->update(*_inputManager, _entShader, _window.getFrameTime())) {
			_beings.erase(being);
		} else if ((*being)->isAlive()) {
			glm::vec3 pos = (*being)->getPosition();
			int x = roundf(pos.x);
			int y = roundf(pos.z);

			if ((*being)->get_n_moveDir().x != 0 || (*being)->get_n_moveDir().z != 0 || (*being)->isPlaceBomb()) {
				if (*being == _player) {
					if (_powerUpInstance != nullptr) {
						glm::vec3 dist = _player->getPosition() - _powerUpInstance->getPosition();
						float fdist = cge::Maths::vec3Len(dist);
						float hit = _player->getHitBoxRadius() + _powerUpInstance->getHitBoxRadius();

						if (_state == levelState::PLAY && fdist < hit && _powerUpInstance->isActive()) {
							_powerUpInstance->Powerup(*_player);
							_powerUpInstance->deActivete();
							_player->playSound("activate");
						}
					}

					if (_gate != nullptr && _gate->isActive() && y == _gate->getPosition().z &&
						x == _gate->getPosition().x) {
						_player->setPosition(_gate->getPosition());
						_state = levelState::COMPLETE;
					}

				}

				if (roundf(oldpos.x) != roundf(pos.x) && _level[roundf(pos.z)][roundf(pos.x)] != nullptr) {
					(*being)->setPosition({pos.x, 0, oldpos.z});
				}

				if (roundf(oldpos.z) != roundf(pos.z) && _level[roundf(pos.z)][roundf(pos.x)] != nullptr) {
					(*being)->setPosition({oldpos.x, 0, (*being)->getPosition().z});
				}

				bumpBeing(*being);
				pos = (*being)->getPosition();
				x = roundf(pos.x);
				y = roundf(pos.z);

				if ((*being)->isPlaceBomb() && _level[y][x] == nullptr) {
					_objtLoader.setDamage((*being)->getDamage());
					_objtLoader.setBombTime((*being)->getBombTime());
					Bomb *nbomb = dynamic_cast<Bomb *>(_objtLoader.loadObject("Bomb", {x, 0, y}));
					_level[y][x] = nbomb;
					_bombs.push_back(nbomb);
					(*being)->placeBomb(nbomb);
				}
			}

			being++;
		} else
			being++;
	}

	for (auto &colBeing : _beings) {
		if (colBeing != _player) {
			glm::vec3 dist = _player->getPosition() - colBeing->getPosition();
			float fdist = cge::Maths::vec3Len(dist);
			float hit = _player->getHitBoxRadius() + colBeing->getHitBoxRadius();
			if (_state == levelState::PLAY && colBeing->isAlive() && fdist < hit) {
				_state = levelState::FAIL;
				_player->loseLife();
			}
		}
	}
}

void LevelRunner::checkBeingBlast(float x, float y) {
	for (auto &being : _beings) {
		auto beingPos = being->getPosition();

		if (roundf(beingPos.x) == static_cast<int>(x) && roundf(beingPos.z) == static_cast<int>(y)) {
			if (being == _player) {
				_player->loseLife();
				_state = levelState::WANTS_QUIT;
			} else {
				being->setAlive(false);
				_player->addScore(being->getPoints());
			}
		}
	}
}

void LevelRunner::bombWorldInteraction() {
	for (auto bomb = _bombs.begin(); bomb != _bombs.end();) {
		unsigned shield = 0;

		if (!(*bomb)->update(*_inputManager, _entShader, _window.getFrameTime())) {
			bool found = false;
			auto bombPos = (*bomb)->getPosition();
			auto being = _beings.begin();
			while (being != _beings.end() && !found) {
				if ((*being)->checkBombDeterNation(*bomb)) {
					found = true;
				} else {
					being++;
				}
			}

			checkGateDamage(bombPos, *being);
			checkBeingBlast(bombPos.x, bombPos.z);
			fireEffect({bombPos.x, bombPos.y + .5, bombPos.z}, 500);
			{
				unsigned i = 0;
				while (_floors[i]->getPosition() != (*bomb)->getPosition() && i < _floors.size()) i++;
				_floors.erase(_floors.begin() + i);
				_floors.push_back(_objtLoader.loadObject("FloorBurn", bombPos));
			}

			for (int i = 1; i < (*bomb)->getBombradius(); i++) {
				if (bombPos.z + i < _level.size() && (shield & Shield::UP) == 0) {
					checkGateDamage({bombPos.x, bombPos.y, bombPos.z + i}, *being);

					if (checkWallBlast(bombPos.x, bombPos.z + i)) {
						shield |= Shield::UP;
					} else {
						fireEffect({bombPos.x, bombPos.y + 0.5, bombPos.z + i}, 100);
					}

					checkBeingBlast(bombPos.x, bombPos.z + i);
					checkBombBlast(bombPos.x, bombPos.z + i);
				}

				if (bombPos.z - i >= 0 && (shield & Shield::DOWN) == 0) {
					checkGateDamage({bombPos.x, bombPos.y, bombPos.z - i}, *being);

					if (checkWallBlast(bombPos.x, bombPos.z - i)) {
						shield |= Shield::DOWN;
					} else {
						fireEffect({bombPos.x, bombPos.y + 0.5, bombPos.z - i}, 100);
					}

					checkBeingBlast(bombPos.x, bombPos.z - i);
					checkBombBlast(bombPos.x, bombPos.z - i);
				}

				if (bombPos.x + i < _level[bombPos.z].size() && (shield & Shield::RIGHT) == 0) {
					checkGateDamage({bombPos.x + i, bombPos.y, bombPos.z}, *being);

					if (checkWallBlast(bombPos.x + i, bombPos.z)) {
						shield |= Shield::RIGHT;
					} else {
						fireEffect({bombPos.x + i, bombPos.y + .5, bombPos.z}, 100);
					}

					checkBeingBlast(bombPos.x + i, bombPos.z);
					checkBombBlast(bombPos.x + i, bombPos.z);
				}

				if (bombPos.x - i >= 0 && (shield & Shield::LEFT) == 0) {
					checkGateDamage({bombPos.x - i, bombPos.y, bombPos.z}, *being);

					if (checkWallBlast(bombPos.x - i, bombPos.z)) {
						shield |= Shield::LEFT;
					} else {
						fireEffect({bombPos.x - i, bombPos.y + .5, bombPos.z}, 100);
					}

					checkBeingBlast(bombPos.x - i, bombPos.z);
					checkBombBlast(bombPos.x - i, bombPos.z);
				}
			}

			_level[bombPos.z][bombPos.x] = nullptr;
			Bomb *tmpBomb = *bomb;
			auto bombEffects = tmpBomb->getSoundEffects();
			delete tmpBomb;

			/// Add entity's sound effects to a vector to be cleaned up
			/// Delete the sources that aren't playing
			for (auto &source : bombEffects) {
				if (source.second->isPlaying()) {
					this->_sources.push_back(source.second);
				} else {
					delete source.second;
				}
			}

			_bombs.erase(bomb);
		} else
			bomb++;
	}
}

void LevelRunner::loadMapEntitys() {
	srand(static_cast<unsigned int>(time(nullptr)));
	cge::Entity *tmpEnt;
	Being *tmpBeing;

	_dwalls = 0;
	_level.resize(_map.size());
	for (size_t i = 0; i < _map.size(); ++i) {
		_level[i].resize(_map[i].size());
		for (size_t j = 0; j < _map[i].length(); ++j) {
			switch (_map[i][j]) {
				case 'w':
					if ((tmpEnt = _objtLoader.loadObject("Wall", {j, 0, i})) != nullptr) {
						_level[i][j] = tmpEnt;
					}

					break;
				case 'p':
					_player->setPosition({j, 0, i});
					_beings.emplace_back(this->_player);
					_floors.push_back(_objtLoader.loadObject("Floor", {j, 0, i}));
					_map[i][j] = '.';

					break;
				case 'd':
					if ((tmpEnt = _objtLoader.loadObject("DestructWall", {j, 0, i})) != nullptr) {
						_level[i][j] = tmpEnt;
						_dwalls++;
					}

					break;
				default:
					_floors.push_back(_objtLoader.loadObject("Floor", {j, 0, i}));

					break;
			}
		}
	}

	_objtLoader.setLevel(_level);

	if (_objtLoader.has("Balloon")) {
		while (_balloons > 0) {
			tmpBeing = dynamic_cast<Being *>(_objtLoader.loadObject("Balloon", {0, 0, 0}));
			_beings.push_back(tmpBeing);
			placeBeing(tmpBeing);
			_balloons--;
		}
	}

	if (_objtLoader.has("Onile")) {
		while (_onil > 0) {
			tmpBeing = dynamic_cast<Being *>(_objtLoader.loadObject("Onile", {0, 0, 0}));
			_beings.push_back(tmpBeing);
			placeBeing(tmpBeing);
			_onil--;
		}
	}

	if (_objtLoader.has("Ovapi")) {
		while (_ovapi > 0) {
			if ((tmpBeing = dynamic_cast<Being *>(_objtLoader.loadObject("Ovapi", {0, 0, 0}))) != nullptr) {
				_beings.push_back(tmpBeing);
				placeBeing(tmpBeing);
			}

			_ovapi--;
		}
	}
}

bool LevelRunner::checkWallBlast(float x, float y) {
	auto ix = static_cast<int>(x);
	auto iy = static_cast<int>(y);

	cge::Entity *tmpEnt;

	if (_level[iy][ix] != nullptr) {
		if (dynamic_cast<DestructWall *>(_level[iy][ix]) != nullptr) {
			_floors.push_back(_objtLoader.loadObject("Floor", {ix, 0, iy}));
			delete (_level[iy][ix]);
			_level[iy][ix] = nullptr;
			_dwalls--;
			wallBrakeEffect({ix, 0, iy}, 1000);
			fireEffect({ix, 0, iy}, 50);
			srand(static_cast<unsigned int>(time(nullptr) + _dwalls));

			if (_gate == nullptr) {
				if (_dwalls == 0) {
					if ((tmpEnt = _objtLoader.loadObject("Gate", {ix, 0, iy})) != nullptr)
						_gate = dynamic_cast<Gate *>(tmpEnt);
				} else if (_beings.size() == 0) {
					if (rand() % 3 == 1)
						if ((tmpEnt = _objtLoader.loadObject("Gate", {ix, 0, iy})) != nullptr)
							_gate = dynamic_cast<Gate *>(tmpEnt);
				} else {
					if (rand() % 20 == 1)
						if ((tmpEnt = _objtLoader.loadObject("Gate", {ix, 0, iy})) != nullptr)
							_gate = dynamic_cast<Gate *>(tmpEnt);
				}
			}

			if (!_powerup) {
				if (rand() % 10 == 1 && _powerUpInstance != nullptr) {
					_powerUpInstance->setPosition({ix, 0, iy});
					_powerUpInstance->activete();
					_powerup = true;
				}
			}
		}

		return true;
	}

	return false;
}

void LevelRunner::endLevel() {
	unsigned endTime = 0;
	while (endTime < 1000) {
		_player->setRotation({0, endTime * M_PI / 180, 0});
		if (_gate != nullptr && _gate->isActive() && _player->getPosition() == _gate->getPosition()) {
			portalUseEffect(_gate->getPosition(), 20);
		}

		render();
		endTime += _window.getFrameTime();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	if (_state == levelState::COMPLETE) {
		_textRenderer.DrawText("level complected", (_window.getWidth() - (8 * 48)) / 2, (_window.getHeight() - 48) /2, {255, 255, 255}, 1, _window.getWidth(), _window.getHeight());
	} else {
		_textRenderer.DrawText("level failed", (_window.getWidth() - (6 * 48)) / 2, (_window.getHeight() - 48) /2, {0, 0, 0}, 1, _window.getWidth(), _window.getHeight());
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
	start = std::chrono::system_clock::now();
	_window.swapBuffers();
	cleanLevel();

	do {
		end = std::chrono::system_clock::now();
		elapsed_seconds = end-start;
	} while (elapsed_seconds.count() < 2);
}

void LevelRunner::loadMapFromFile(const std::string &path) {
	std::ifstream ifs(path);
	std::string line;
	std::smatch match;
	std::regex regEnemies(R"(^(?:(balloon:) ([0-9]{1,2})\s*)?(?:(onile:) ([0-9]{1,2})\s*)?(?:(ovapi:) ([0-9]{1,2})\s*)?$)");
	std::regex regPowerUp("^(FireUp|FullFire|FireDown|WallPass|WingBoot|AddBomb|Deternator)?$");

	_balloons = 0;
	_onil = 0;
	_ovapi = 0;
	_map.clear();

	if (ifs.good()) {
		std::getline(ifs, line);
		if (!std::regex_match(line, regEnemies)) {
			_state = levelState::FAIL_MAP_LOAD;
			return;
		}

		if (std::regex_match(line, match, regEnemies)) {
			for (size_t i = 1; i < match.size(); ++i) {
				std::ssub_match sub_match = match[i];
				std::string piece = sub_match.str();
				if (piece == "balloon:") {
					sub_match = match[++i];
					_balloons = stoi(sub_match.str());
				}
				if (piece == "onile:") {
					sub_match = match[++i];
					_onil = stoi(sub_match.str());
				}
				if (piece == "ovapi:") {
					sub_match = match[++i];
					_ovapi = stoi(sub_match.str());
				}
			}
		}

		std::getline(ifs, line);
		if (!std::regex_match(line, regPowerUp)) {
			_state = levelState::FAIL_MAP_LOAD;
			return;
		}

		if (std::regex_match(line, match, regPowerUp)) {
			cge::Entity *tmpEnt;
			std::ssub_match sub_match = match[1];
			std::string piece = sub_match.str();
			if ((tmpEnt = _objtLoader.loadObject(piece, {0, 0, 0})) != nullptr) {
				_powerUpInstance = dynamic_cast<PowerUPAbstract *>(tmpEnt);
			}
		}

		do {
			ifs >> line;
			_map.push_back(line);
		} while (ifs.good());
	} else {
		_state = levelState::FAIL_MAP_LOAD;
	}

	if (!checkMapWall()) {
		_state = levelState::FAIL_MAP_LOAD;
	}
}

bool LevelRunner::checkMapWall() {
	//check top and bottom lines are solid walls
	std::regex soilidwall("^w{6,}$");
	std::regex remainSoledWall("^w+$");
	bool player = false;

	if (_map.size() < 6) {
		return false;
	}

	if (!std::regex_match(_map[0], soilidwall) || !std::regex_match(_map[_map.size() - 1], soilidwall)) {
		return false;
	}

	for (size_t i = 1; i < _map.size(); ++i) {
		if (_map[i].find('p') != std::string::npos) {
			if (!player && _map[i].find('p', _map[i].find('p') + 1) == std::string::npos)
				player = true;
			else
				return false;
		}
		if (_map[i][_map[i].length() - 1] != 'w' || _map[i][0] != 'w')
			return false;
		if (_map[i].length() < _map[i - 1].length() &&
			!std::regex_match(&_map[i - 1][_map[i].length() - 1], remainSoledWall))
			return false;
		if (_map[i].length() > _map[i - 1].length() &&
			!std::regex_match(&_map[i][_map[i - 1].length() - 1], remainSoledWall))
			return false;
	}

	return player;
}

int LevelRunner::getState() const {
	return _state;
}

int LevelRunner::runLevel(const std::string &path) {
	if (_state == levelState::PAUSE) {
		cleanLevel();
	}

	loadMapFromFile(path);
	if (_state == levelState::FAIL_MAP_LOAD) {
		return (_state);
	}

	_levelTime = 200000;

	loadMapEntitys();
	_player->setPlaceBomb(false);
	_state = levelState::PLAY;
	runLevelLoop();
	if (_state != levelState::PAUSE) {
		endLevel();
	}

	return _state;
}

void LevelRunner::cleanLevel() {
	_player->setPlaceBomb(false);
	_particalRenderer.clearParticals();

	if (_state != levelState::COMPLETE && _powerup && !_powerUpInstance->isActive()) {
		_powerUpInstance->Reverse(*_player);
	}

	_powerup = false;
	delete _powerUpInstance;
	_powerUpInstance = nullptr;

	for (auto &bomb : this->_bombs) {
		for (auto &being : this->_beings) {
			if (being->checkBombDeterNation(bomb)) {
				break;
			}
		}
	}

	for (auto vecEnt : _level) {
		for (auto ent : vecEnt) {
			if (ent != nullptr)
				delete (ent);
		}

		vecEnt.clear();
	}

	_level.clear();
	_bombs.clear();

	for (auto &beingIter : _beings) {
		if (beingIter != _player) {
			delete beingIter;
		}
	}

	_beings.clear();

	if (_gate != nullptr) {
		delete _gate;
		_gate = nullptr;
	}

	for (auto &floorTile : _floors) {
		delete floorTile;
	}

	_floors.clear();

	for (auto &source : this->_sources) {
		source->setPlaying(false);
		delete source;
	}

	this->_sources.clear();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

int LevelRunner::resumeLevel() {
	if (_state == levelState::PAUSE) {
		_state = levelState::PLAY;
		runLevelLoop();
		if (_state != levelState::PAUSE)
			endLevel();
	}
	return _state;
}

void LevelRunner::runLevelLoop() {
	_inputManager->setInputCallBacks();

	while (_state == levelState::PLAY) {
		update();
		render();

		_inputManager->pollKeyEvnt();

		this->_audioDevice.setLocation(this->_player->getPosition(), true);

		/// Clean up sound effects from deleted entities
		this->_sources.erase(std::remove_if(
			this->_sources.begin(),
			this->_sources.end(),
			[](cge::Audio::Source *source) {
				if (!source->isPlaying()) {
					delete source;
					return true;
				}

				return false;
			}
		), this->_sources.end());
	}

	do {
		this->_inputManager->pollKeyEvnt();
	} while (this->_inputManager->isKeyPressed(this->_player->get_menue())
			|| this->_inputManager->isKeyPressed(this->_player->get_bomb())
			|| this->_inputManager->isKeyPressed(this->_player->get_up())
			|| this->_inputManager->isKeyPressed(this->_player->get_down())
			|| this->_inputManager->isKeyPressed(this->_player->get_left())
			|| this->_inputManager->isKeyPressed(this->_player->get_right())
			|| this->_inputManager->isKeyPressed(this->_player->get_special()));
}

void LevelRunner::wallBrakeEffect(const glm::vec3 &position, size_t numParticals) {
	particle_t particle {
		position,
		{ 0.5f, 0.5f, 0.5f },
		{ 0, 0, 0 },
		{ 0, 0, 0 },
		0.5f,
		0.1f,
		250,
		100,
		0.1f,
		0.01f,
		0.1f,
		1.0f,
		0.001,
		0.001,
		numParticals,
		_loader.loadTextureAtlas("resources/Textures/ConcreatFragment.png", 1),
		GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA
	};

	_particalRenderer.particleEffect(particle);
}

void LevelRunner::fireEffect(const glm::vec3 &position, size_t numParticals) {
	particle_t particle {
		position,
		{ 0.5f, 0.5f, 0.5f },
		{ 0.0f, 0.002f, 0.0f },
		{ 0.0f, 0.001f, 0.0f },
		0.0f,
		0.0f,
		200,
		300,
		0.4f,
		0.1f,
		0.1f,
		1.0f,
		0.00001f,
		0.0001f,
		numParticals,
		_loader.loadTextureAtlas("resources/TextureAtlas/FireBallAtlas.png", 4),
		GL_SRC_ALPHA,
		GL_ONE
	};

	_particalRenderer.particleEffect(particle);
}

void LevelRunner::portalActiveEffect(const glm::vec3 &position, size_t numParticals) {
	cge::TextureAtlas texture = this->_loader.loadTextureAtlas("resources/TextureAtlas/PortalEffect.png", 2);

	static std::default_random_engine gen;
	std::uniform_real_distribution<float> dispx(position.x - 0.2f, position.x + 0.2f);
	std::uniform_real_distribution<float> dispz(position.z - 0.2f, position.z + 0.2f);
	static std::uniform_real_distribution<float> disvx(0.01f, -0.01f);
	static std::uniform_real_distribution<float> disvy(0.06f, 0.04f);
	static std::uniform_real_distribution<float> disvz(0.01f, -0.01f);
	static std::uniform_real_distribution<float> dislife(1000, 10000);

	for (size_t i = 0; i < numParticals; ++i) {
		glm::vec3 position = { dispx(gen), 0, dispz(gen) };
		glm::vec3 velocity = { disvx(gen), disvy(gen), disvz(gen) };
		float life = dislife(gen);

		this->_particalRenderer.addPartical(cge::Partical(position, velocity, 0.01, life, 0.05, 0, 0, texture), GL_SRC_ALPHA, GL_ONE);
	}

}

void LevelRunner::portalUseEffect(const glm::vec3 &position, size_t numParticals) {
	cge::TextureAtlas texture = _loader.loadTextureAtlas("resources/TextureAtlas/PortalEffect.png", 2);
	static std::default_random_engine gen;
	std::uniform_real_distribution<float> dispx(position.x - 0.2f, position.x + 0.2f);
	std::uniform_real_distribution<float> dispz(position.z - 0.2f, position.z + 0.2f);
	static std::uniform_real_distribution<float> disvx(0.01f, -0.01f);
	static std::uniform_real_distribution<float> disvy(0.6f, 0.04f);
	static std::uniform_real_distribution<float> disvz(0.01f, -0.01f);
	static std::uniform_real_distribution<float> dislife(1000, 10000);
	static std::uniform_real_distribution<float> disscale(0.1f, 0.5f);
	static std::uniform_real_distribution<float> disrot(0, 1);

	for (size_t i = 0; i < numParticals; ++i) {
		glm::vec3 position = { dispx(gen), 0, dispz(gen) };
		glm::vec3 velocity = { disvx(gen), disvy(gen), disvz(gen) };

		float lifetime = dislife(gen);
		float scale = disscale(gen);
		float rotation = disrot(gen);
		_particalRenderer.addPartical(cge::Partical(position, velocity, 0.01, lifetime, scale, rotation, 0, texture), GL_SRC_ALPHA, GL_ONE);
	}

}

void LevelRunner::checkGateDamage(const glm::vec3 &position, Being *being) {
	if (this->_gate == nullptr) {
		return;
	}

	glm::vec3 gatePos = this->_gate->getPosition();
	if (being == this->_player && gatePos.x == position.x && gatePos.z == position.z) {
		this->_gate->damage(8);
	}
}

void LevelRunner::update() {
	static unsigned time = 0;
	rotatePowerUp();

	if (_inputManager->isExitCase() || _player->getLives() <= 0) {
		_state = levelState::WANTS_QUIT;
	}

	if (_player->isPauseMenue()) {
		_state = levelState::PAUSE;
	}
	if (_beings.size() == 1) {
		_player->playSound("activate");

		if (_gate != nullptr) {
			_gate->activate();
		}
	}

	beingWorldInteraction();
	if (_state == levelState::PLAY) {
		bombWorldInteraction();
	}

	glm::vec3 plpos = _player->getPosition();
	this->_camera.setPosition({plpos.x, 10, plpos.z});
	if (_gate != nullptr) {
		if (_gate->isDamage()) {
			Being *tmpEnt = dynamic_cast<Being *>(_objtLoader.loadObject("Ovapi", {_gate->getPosition().x, 0, _gate->getPosition().z}));

			if (tmpEnt != nullptr) {
				_beings.push_back(tmpEnt);
			}
		}

		_gate->update(*_inputManager, _entShader, 0);
		if (_gate->isActive() && time == 0) {
			portalActiveEffect(_gate->getPosition(), 1);
		}

		time += _window.getFrameTime();
		time = (time < 1000) ? time : 0;
	}
	if ((_levelTime <= _window.getFrameTime())) {
		_state = levelState::FAIL;
	} else {
		_levelTime -= _window.getFrameTime();
	}
}

void LevelRunner::render() {
	std::vector<cge::Entity *> entities;
	_entShader.begin();
	_renderer.prepare();
	_camera.setTrackEntity(*_player);
	_camera.setTrackOffset({0, 8, 5});
	_camera.update(_entShader);

	for (auto &floor : _floors) {
		entities.push_back(floor);
	}

	for (auto &vecit : _level) {
		for (auto &entit : vecit) {
			if (entit != nullptr) {
				entities.push_back(entit);
			}
		}
	}

	for (const auto being : _beings) {
		entities.push_back(dynamic_cast<cge::Entity *>(being));
	}

	if (_gate != nullptr) {
		entities.push_back(dynamic_cast<cge::Entity *>(_gate));
	}

	if (_powerUpInstance != nullptr && _powerUpInstance->isActive()) {
		entities.push_back(dynamic_cast<cge::Entity *>(_powerUpInstance));
	}

	_renderer.render(entities);
	_entShader.end();

	_particalRenderer.updateRender(_camera, _window.getFrameTime());
	_spriteRenderer.DrawSprite(_life, _window.getWidth(), _window.getHeight());
	_spriteRenderer.DrawSprite(_timer, _window.getWidth(), _window.getHeight());
	_textRenderer.DrawText((std::to_string(_player->getLives())), 84, _window.getHeight() - 100, {255, 0, 0}, 1, _window.getWidth(), _window.getHeight());
	_textRenderer.DrawText(std::to_string(_levelTime / 1000), _window.getWidth() - (4 * 48), _window.getHeight() - 100, {255, 255, 255}, 1, _window.getWidth(), _window.getHeight());
	_window.swapBuffers();
}

void LevelRunner::placeBeing(Being *being) {
	static std::default_random_engine gen;
	std::uniform_int_distribution<unsigned int> row(0, (unsigned int) _level.size() - 1);
	int rowNum = row(gen);
	std::uniform_int_distribution<unsigned int> col(0, (unsigned int) _level[rowNum].size() - 1);
	int colNum = col(gen);
	glm::vec3 dist = _player->getPosition() - glm::vec3({colNum, 0, rowNum});
	if (_level[rowNum][colNum] == nullptr && cge::Maths::vec3LenSqr(dist) > 2) {
		being->setPosition({colNum, 0, rowNum});
	} else {
		placeBeing(being);
	}
}

void LevelRunner::checkBombBlast(float x, float y) {
	for (auto &bomb : _bombs) {
		if (bomb->getPosition() == glm::vec3({ floorf(x), 0, floorf(y) })) {
			bomb->setDetonate(true);
		}
	}
}

void LevelRunner::rotatePowerUp() {
	static const float raidSec = 0.003185225;
	_powerUpInstance->addRotation({0, _window.getFrameTime() * raidSec, 0});
}

void LevelRunner::DrawEOGCredits() {
	int yTitle =  _window.getHeight() * 0.1;
	int yAuthors = yTitle - 80;
	int yAuthorOne = yAuthors - 30;
	int yAuthorTwo = yAuthorOne - 30;
	int yAuthorThree = yAuthorTwo - 30;
	int yAuthorFour = yAuthorThree - 30;
	int end = yAuthorFour - 20;

	int width = static_cast<int>(_window.getHeight());
	while (end < width) {
		this->_renderer.prepare();
		_textRenderer.DrawText("~ The End : Your Score: " + std::to_string(_player->getScore()) + " ~", 30, yTitle++, {0, 0, 0}, 1,
							   _window.getWidth(), _window.getHeight());
		_textRenderer.DrawText("Authors:", 40, yAuthors++, {0, 0, 0}, 0.5f,
							   _window.getWidth(), _window.getHeight());
		_textRenderer.DrawText(" - Angus Dippenaar (adippena)", 45, yAuthorOne++, {0, 0, 0}, 0.5f,
							   _window.getWidth(), _window.getHeight());
		_textRenderer.DrawText(" - Robert Jones (rojones)", 45, yAuthorTwo++, {0, 0, 0}, 0.5f,
							   _window.getWidth(), _window.getHeight());
		_textRenderer.DrawText(" - Owen Exall (oexall)", 45, yAuthorThree++, {0, 0, 0}, 0.5f,
							   _window.getWidth(), _window.getHeight());
		_textRenderer.DrawText(" - Mfanyana Malaba (mfmalaba)", 45, yAuthorFour++, {0, 0, 0}, 0.5f,
							   _window.getWidth(), _window.getHeight());

		_window.swapBuffers();
		end++;
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
