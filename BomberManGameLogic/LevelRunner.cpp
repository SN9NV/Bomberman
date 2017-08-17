//
// Created by rojones on 2017/08/09.
//

#include "LevelRunner.hpp"
#include "DestructWall.hpp"
#include "Gate.hpp"
#include "Balloon.hpp"
#include "../extras/Maths.hpp"
#include "Wall.h"
#include "../io/audio/AudioSource.hpp"
#include "../extras/glmOstream.hpp"

LevelRunner::LevelRunner(cge::Loader &_loader, Player *_player,
						 cge::Window &_window, cge::InputManager *inputManager) : _loader(_loader),
																				  _player(_player),
																				  _gate(nullptr),
																				  _window(_window),
																				  _entShader("../shaders/vertex.glsl",
																							 "../shaders/fragment.glsl"),
																				  _partShader(
																						  "../shaders/particalVertex.glsl",
																						  "../shaders/particalFragment.glsl"),
																				  _renderer(_entShader),
																				  _camera(glm::vec3(0.0f, 5.0f, 0.0f),
																						  glm::vec3(1.5f, 0.0f, 0.0f),
																						  _window),
																				  _particalRenderer(_partShader) {
	_inputManager = inputManager;

	_models.emplace("Wall",
					cge::Model("../resources/models/Wall.glb", "../resources/models/SolidWallDiffuseColor.png",
							   this->_loader));
	_models.emplace("DestructWall", cge::Model("../resources/models/DestructWall.glb",
											   "../resources/models/DestructWallDiffuseColor.png", this->_loader));
	_models.emplace("Bomb",
					cge::Model("../resources/models/Bomb.glb", "../resources/models/BombDiffuseColor.png",
							   this->_loader));
	_models.emplace("Bomber",
					cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							   this->_loader));
	_models.emplace("Balloon",
					cge::Model("../resources/models/Balloon.glb", "../resources/models/BalloonDiffuseColor.png",
							   this->_loader));
	_models.emplace("Gate",
					cge::Model("../resources/models/Gate.glb", "../resources/models/GateDiffuseColor.png",
							   this->_loader));
}

cge::Model *LevelRunner::getModel(std::string name) {
	auto found = _models.find(name);
	if (found != _models.end())
		return (&found->second);
	return (nullptr);
}

void LevelRunner::bumpBeing(Being *being) {
	glm::vec3 pos;
	int x;
	int y;
	float minBoxDist;
	float dist;

	pos = being->getPosition();
	x = (int) (round(pos.x));
	y = (int) (round(pos.z));
	//colision box up
	if ((y - 1) > -1 && _level[y - 1][x] != nullptr) {
		minBoxDist = being->getHitBoxRadius() + _level[y - 1][x]->getHitBoxRadius();
		dist = (float) (fabs(_level[y - 1][x]->getPosition().z - pos.z));
		if (dist < minBoxDist) {
			being->setPosition({pos.x, 0, pos.z + (minBoxDist - dist)});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box down
	if (y + 1 < (int) _level.size() && _level[y + 1][x] != nullptr) {
		minBoxDist = being->getHitBoxRadius() + _level[y + 1][x]->getHitBoxRadius();
		dist = (float) (fabs(_level[y + 1][x]->getPosition().z - pos.z));
		if (dist < minBoxDist) {
			being->setPosition({pos.x, 0, pos.z - (minBoxDist - dist)});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box left
	if (x - 1 > -1 && _level[y][x - 1] != nullptr) {
		minBoxDist = being->getHitBoxRadius() + _level[y][x - 1]->getHitBoxRadius();
		dist = (float) (fabs(_level[y][x - 1]->getPosition().x - pos.x));
		if (dist < minBoxDist) {
			being->setPosition({pos.x + (minBoxDist - dist), 0, pos.z});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box right
	if (x + 1 < (int) _level[y].size() && _level[y][x + 1] != nullptr) {
		minBoxDist = being->getHitBoxRadius() + _level[y][x + 1]->getHitBoxRadius();
		dist = (float) (fabs(_level[y][x + 1]->getPosition().x - pos.x));
		if (dist < minBoxDist) {
			being->setPosition({pos.x - (minBoxDist - dist), 0, pos.z});
			being->setMoveDir({0, 0, 0});
		}
	}
}

void LevelRunner::beingWorldInteraction() {
	glm::vec3 oldpos;
	glm::vec3 pos;
	cge::Model *tmpmdl;
	std::vector<Being *>::iterator being;
	int x;
	int y;


	being = _beings.begin();
	while (being != _beings.end()) {
		oldpos = (*being)->getPosition();

		if (!(*being)->update(*_inputManager, _entShader, _window.getFrameTime())) {
			_beings.erase(being);
		} else if ((*being)->isAlive()) {
			pos = (*being)->getPosition();
			x = (int) (round(pos.x));
			y = (int) (round(pos.z));
			if ((*being)->get_n_moveDir().x != 0 || (*being)->get_n_moveDir().z != 0 || (*being)->is_placeBomb()) {
				if ((*being) == _player) {
					if (_gate != nullptr && _gate->isActive() && y == _gate->getPosition().z &&
						x == _gate->getPosition().x) {
						_player->setPosition(_gate->getPosition());
						_state = levelState::COMPLEAT;
					}

				}
				if (_level[y][x] != nullptr) {
					if (_level[(int) (round(oldpos.z))][(int) (round(oldpos.x))] == nullptr) {
						(*being)->setPosition(oldpos);
						(*being)->setMoveDir({0, 0, 0});
					} else if ((int) (round(oldpos.z)) != y ||
							   (int) (round(oldpos.x)) != x) {
						(*being)->setPosition(oldpos);
						(*being)->setMoveDir({0, 0, 0});
					}
				}
				bumpBeing((*being));
				pos = (*being)->getPosition();
				x = (int) (round(pos.x));
				y = (int) (round(pos.z));
				if ((*being)->is_placeBomb() && (tmpmdl = getModel("Bomb")) != nullptr) {
					Bomb *nbomb = new Bomb({x, 0, y}, {0, 0, 0}, 1, *tmpmdl, (*being)->getDamage());
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

void LevelRunner::checkBeingBlast(int x, int y) {
	std::vector<Being *>::iterator being;
	glm::vec3 beingPos;

	being = _beings.begin();
	while (being != _beings.end()) {
		beingPos = (*being)->getPosition();
		if ((int) round(beingPos.x) == x && (int) round(beingPos.z) == y) {
			if ((*being) == _player) {
				std::cout << "player loose life. Player: " << (int) round(beingPos.x) << " " << (int) round(beingPos.z)
						  << std::endl;
				_player->loseLife();
				_state = levelState::WANTS_QUIT;
			} else {
				(*being)->setAlive(false);
			}
		}
		being++;
	}
}

void LevelRunner::bombWorldInteraction() {
	int i;
	int sheild;
	bool found;
	Bomb *tmpBomb;
	glm::vec3 bombPos;
	glm::vec3 beingPos;
	std::vector<Bomb *>::iterator bomb = _bombs.begin();
	std::vector<Being *>::iterator being;

	while (bomb != _bombs.end()) {
		sheild = 0;
		if (!(*bomb)->update(*_inputManager, _window.getFrameTime())) {
			found = false;
			bombPos = (*bomb)->getPosition();
			being = _beings.begin();
			while (being != _beings.end() && !found) {
				if ((*being)->checkBombDeterNation((*bomb)))
					found = true;
				being++;
			}
			checkBeingBlast((int) bombPos.x, (int) bombPos.z);
			_particalRenderer.partivalEffect({bombPos.x, bombPos.y, bombPos.z}, {0.5, 0.5, 0.5},
											{0, 0.002, 0.00}, {0, 0.001, 0}, 0, 0.001, 1000, 1000, 0.1, 0.2,
											100, _loader.loadTextureAtlas(
							"../resources/TextureAtlas/Fireball_Atlas_d.png", 4));
			i = 0;
			while (++i < (*bomb)->getBombradius()) {
				if (bombPos.z + i < _level.size() && (sheild & 0b00000001) == 0) {

					if (checkWallBlast((int) (bombPos.x), (int) (bombPos.z + i)))
						sheild = sheild | 0b00000001;
					else {
						_particalRenderer.partivalEffect({bombPos.x, bombPos.y, bombPos.z + i}, {0.5, 0.5, 0.5},
														 {0, 0.002, 0.00}, {0, 0.001, 0}, 0, 0.001, 1000, 1000, .1, .3,
														 100, _loader.loadTextureAtlas(
										"../resources/TextureAtlas/Fireball_Atlas_d.png", 4));
					}
					checkBeingBlast((int) (bombPos.x), (int) (bombPos.z + i));

				}
				if (bombPos.z - i >= 0 && (sheild & 0b00000010) == 0) {

					if (checkWallBlast((int) (bombPos.x), (int) (bombPos.z - i)))
						sheild = sheild | 0b00000010;
					else {
						_particalRenderer.partivalEffect({bombPos.x, bombPos.y, bombPos.z - i}, {0.5, 0.5, 0.5},
														 {0, 0.002, -0}, {0, 0.001, 0}, 0, 0.001, 1000, 1000, .1, .3,
														 100, _loader.loadTextureAtlas(
										"../resources/TextureAtlas/Fireball_Atlas_d.png", 4));
					}
					checkBeingBlast((int) (bombPos.x), (int) (bombPos.z - i));
				}
				if (bombPos.x + i < _level[bombPos.z].size() && (sheild & 0b00000100) == 0) {
					if (checkWallBlast((int) (bombPos.x + i), (int) (bombPos.z)))
						sheild = sheild | 0b00000100;
					else {
						_particalRenderer.partivalEffect({bombPos.x + i, bombPos.y, bombPos.z}, {0.5, 0.5, 0.5},
														 {0.00, 0.002, 0}, {0, 0.001, 0}, 0, 0.001, 1000, 1000, .1, .3,
														 1000, _loader.loadTextureAtlas(
										"../resources/TextureAtlas/Fireball_Atlas_d.png", 4));
					}
					checkBeingBlast((int) bombPos.x + i, (int) (bombPos.z));
				}
				if (bombPos.x - i >= 0 && (sheild & 0b00001000) == 0) {

					if (checkWallBlast((int) (bombPos.x - i), (int) (bombPos.z)))
						sheild = sheild | 0b00001000;
					else {
						_particalRenderer.partivalEffect({bombPos.x - i, bombPos.y, bombPos.z}, {0.5, 0.5, 0.5},
														 {-0.0, 0.002, 0}, {0, 0.001, 0}, 0, 0.001, 1000, 1000, .1, .3,
														 1000, _loader.loadTextureAtlas(
										"../resources/TextureAtlas/Fireball_Atlas_d.png", 4));
					}
					checkBeingBlast((int) (bombPos.x - i), (int) (bombPos.z));
				}
			}
			_level[bombPos.z][bombPos.x] = NULL;
			tmpBomb = (*bomb);
			delete (tmpBomb);
			_bombs.erase(bomb);
		} else
			bomb++;

	}
}

void LevelRunner::loadMapEntitys() {
	srand((unsigned int) (time(NULL)));
	cge::Model *tmpMdl;
	cge::Entity *tmpEnt;

	_dwalls = 0;
	_level.resize(_map.size());
	for (size_t i = 0; i < _map.size(); ++i) {
		_level[i].resize(_map[i].size());
		for (size_t j = 0; j < _map[i].length(); ++j) {
			switch (_map[i][j]) {
				case 'w':
					if ((tmpMdl = getModel("Wall")) != nullptr) {
						tmpEnt = new Wall({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, 0.5f);
						_level[i][j] = tmpEnt;
					}
					break;
				case 'p':
					_player->setPosition({j, 0, i});
					_beings.push_back(this->_player);
					_map[i][j] = '.';
					break;
				case 'd':
					if ((tmpMdl = getModel("DestructWall")) != nullptr) {
						tmpEnt = new DestructWall({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, 0.5f);
						_level[i][j] = tmpEnt;
						_dwalls++;
					}
					break;
				default:
					if (_balloons + _onil > 0) {

						if (_balloons > 0 && rand() % 6 == 1) {
							if ((tmpMdl = getModel("Balloon")) != nullptr) {
								_beings.push_back(new Balloon({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, 0.5f));
								_balloons--;
							}
						} else if (_onil > 0 && rand() % 6 == 1) {
							/*if ((tmpMdl = getModel("Onil")) != nullptr)
							{
								_beings.push_back(new Onil({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, 0.5f));
								_onil--;
							}*/
							_onil--;
						}
					}
					break;
			}
		}
	}
}

bool LevelRunner::checkWallBlast(int x, int y) {
	cge::Model *tmpMdl;

	if (_level[y][x] != NULL) {
		if (dynamic_cast<DestructWall *>(_level[y][x]) != NULL) {
			delete (_level[y][x]);
			_level[y][x] = nullptr;
			_dwalls--;
			srand((unsigned int) time(NULL) + _dwalls);
			if (_gate == nullptr) {
				if (_dwalls == 0) {
					if ((tmpMdl = getModel("Gate")) != nullptr)
						_gate = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
					std::cout << "make gate" << std::endl;
				} else if (rand() % 20 == 1) {
					if ((tmpMdl = getModel("Gate")) != nullptr)
						_gate = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
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
		_entShader.start();
		_renderer.prepare();
		_camera.update(_entShader);
		_player->setRotation({0, endTime * M_PI / 180, 0});
		if (_gate != nullptr && _gate->isActive())
			_gate->setRotation({0, -(endTime * M_PI / 180), 0});
		for (auto &vecit : _level) {
			for (auto &entit : vecit) {
				if (entit != nullptr)
					_renderer.render(*entit);
			}
		}
		for (auto being : _beings)
			_renderer.render(*being);
		if (_gate != nullptr)
			_renderer.render(*_gate);
		_entShader.end();
		_particalRenderer.updateRender(_camera, _window.getFrameTime());
		_window.swapBuffers();
		endTime += _window.getFrameTime();
	}
	cleanlevel();
}

void LevelRunner::loadMapFromFile(std::string path) {
	//std::vector<std::string> map;
	std::ifstream ifs(path);
	std::string line;
	std::string enemies;
	std::smatch match;
	std::regex regEnemies("^(?:(balloon:) ([0-9]{1,2})\\s*)?(?:(onil:) ([0-9]{1,2})\\s*)?$");


	_balloons = 0;
	_onil = 0;
	_map.clear();
	if (ifs.good()) {
		std::getline(ifs, enemies);
		if (!std::regex_match(enemies, regEnemies)) {
			_state = levelState::FAIL_MAP_LOAD;
			return;
		} else {
			if (std::regex_match(enemies, match, regEnemies)) {
				for (size_t i = 1; i < match.size(); ++i) {
					std::ssub_match sub_match = match[i];
					std::string piece = sub_match.str();
					if (piece == "balloon:") {
						sub_match = match[++i];
						_balloons = stoi(sub_match.str());
					}
					if (piece == "onil:") {
						sub_match = match[++i];
						_onil = stoi(sub_match.str());
					}
				}
			}
			std::cout << "balloons: " << _balloons << " onils: " << _onil << std::endl;
		}
		do {
			ifs >> line;
			_map.push_back(line);

		} while (ifs.good());
	} else
		_state = levelState::FAIL_MAP_LOAD;
	if (!checkMapWall())
		_state = levelState::FAIL_MAP_LOAD;
}

bool LevelRunner::checkMapWall() {
	//check top and bottom lines are solid walls
	std::regex soilidwall("^w{6,}$");
	std::regex remainSoledWall("^w+$");
	bool player = false;

	if (_map.size() < 6)
		return false;
	if (!std::regex_match(_map[0], soilidwall) || !std::regex_match(_map[_map.size() - 1], soilidwall))
		return false;
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

int LevelRunner::runLevel(std::string path) {
	if (_state == levelState::PAUSE)
		cleanlevel();
	loadMapFromFile(path);
	if (_state == levelState::FAIL_MAP_LOAD)
		return (_state);
	_gate = nullptr;
	loadMapEntitys();
	_state = levelState::PLAY;
	runlevelLoop();
	if (_state != levelState::PAUSE)
		endLevel();
	std::cout << "about to eixit leve with state " << _state << std::endl;
	return _state;
}

void LevelRunner::cleanlevel() {
	std::vector<Being *>::iterator being;
	bool found;

	for (auto bomb : _bombs) {
		found = false;
		being = _beings.begin();
		while (being != _beings.end() && !found) {
			if ((*being)->checkBombDeterNation((bomb)))
				found = true;
			being++;
		}
	}
	for (auto vecEnt : _level) {
		for (auto ent : vecEnt) {
			if (ent != nullptr )
				delete (ent);
		}
		vecEnt.clear();
	}
	_level.clear();
	_bombs.clear();
	for (auto &being : _beings)
		if (being != _player)
			delete (being);
	_beings.clear();
	if (_gate != nullptr) {
		delete (_gate);
		_gate = nullptr;
	}
}

int LevelRunner::resumeLevel() {
	if (_state == levelState::PAUSE) {
		_state = levelState::PLAY;
		runlevelLoop();
		if (_state != levelState::PAUSE)
			endLevel();
		std::cout << "about to eixit leve with state " << _state << std::endl;
	}
	return _state;
}

void LevelRunner::runlevelLoop() {
	cge::Audio::Source	gameMusic("resources/audio/MainTheme.ogg", this->_loader);
	gameMusic.setLooping(true);
	gameMusic.setPlaying();

	while (_state == levelState::PLAY) {

		if (_inputManager->isExitCase() || _player->getLives() <= 0) {
			_state = levelState::WANTS_QUIT;
		}
		if (_player->isPauseMenue())
			_state = levelState::PAUSE;
		if (_beings.size() == 1 && _gate != nullptr)
			_gate->actervate();
		beingWorldInteraction();
		if (_state == levelState::PLAY)
			bombWorldInteraction();
		glm::vec3 plpos = _player->getPosition();
		_camera.setPosition({plpos.x, 10, plpos.z + 3});
		_camera.lookAt(plpos);

		_entShader.start();
		_renderer.prepare();
		_camera.update(_entShader);
		for (auto &vecit : _level) {
			for (auto &entit : vecit) {
				if (entit)
					_renderer.render(*entit);
			}
		}
		for (auto being : _beings)
			_renderer.render(*being);
		if (_gate != nullptr)
			_renderer.render(*_gate);
		_entShader.end();
		_particalRenderer.updateRender(_camera, _window.getFrameTime());
//		_textRenderer.DrawText("test", 5, 5);
		_window.swapBuffers();
		_inputManager->pollKeyEvnt();
	}
	//todo: fix nasty hack
	while (_inputManager->isKeyPressed(_player->get_menue())) {
		_inputManager->pollKeyEvnt();
	}
}
