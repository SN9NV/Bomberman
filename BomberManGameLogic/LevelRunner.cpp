//
// Created by rojones on 2017/08/09.
//

#include "LevelRunner.hpp"
#include "DestructWall.hpp"
#include "Gate.hpp"
#include "Balloon.hpp"
#include "../extras/Maths.hpp"

LevelRunner::LevelRunner(cge::Loader &_loader, Player *_player,
						 const cge::Window &_window) : _loader(_loader), _player(_player),
													   _gate(nullptr),
													   _window(_window),
													   _shader("../shaders/vertex.glsl", "../shaders/fragment.glsl"),
													   _renderer(_shader),
													   _camera(glm::vec3(0.0f, 3.0f, 0.0f),
															   glm::vec3(1.4f, 0.0f, 0.1f), _window)
{
	this->_inputManager = new cge::InputManager(_window);

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

cge::Model *LevelRunner::getModel(std::string name)
{
	auto found = _models.find(name);
	if (found != _models.end())
		return (&found->second);
	return (nullptr);
}

void LevelRunner::bumpBeing(Being *being)
{
	glm::vec3 pos;
	int x;
	int y;
	float minBoxDist;
	float dist;

	pos = being->getPosition();
	x = (int) (round(pos.x));
	y = (int) (round(pos.z));
	//colision box up
	if ((y - 1) > -1 && _level[y - 1][x] != nullptr)
	{
		minBoxDist = being->getHitBox().z + _level[y - 1][x]->getHitBox().z;
		dist = (float) (fabs(_level[y - 1][x]->getPosition().z - pos.z));
		if (dist < minBoxDist)
		{
			being->setPosition({pos.x, 0, pos.z + (minBoxDist - dist)});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box down
	if (y + 1 < (int) _level.size() && _level[y + 1][x] != nullptr)
	{
		minBoxDist = being->getHitBox().z + _level[y + 1][x]->getHitBox().z;
		dist = (float) (fabs(_level[y + 1][x]->getPosition().z - pos.z));
		if (dist < minBoxDist)
		{
			being->setPosition({pos.x, 0, pos.z - (minBoxDist - dist)});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box left
	if (x - 1 > -1 && _level[y][x - 1] != nullptr)
	{
		minBoxDist = being->getHitBox().x + _level[y][x - 1]->getHitBox().x;
		dist = (float) (fabs(_level[y][x - 1]->getPosition().x - pos.x));
		if (dist < minBoxDist)
		{
			being->setPosition({pos.x + (minBoxDist - dist), 0, pos.z});
			being->setMoveDir({0, 0, 0});
		}
	}
	//colision box right
	if (x + 1 < (int) _level[y].size() && _level[y][x + 1] != nullptr)
	{
		minBoxDist = being->getHitBox().x + _level[y][x + 1]->getHitBox().x;
		dist = (float) (fabs(_level[y][x + 1]->getPosition().x - pos.x));
		if (dist < minBoxDist)
		{
			being->setPosition({pos.x - (minBoxDist - dist), 0, pos.z});
			being->setMoveDir({0, 0, 0});
		}
	}
}

void LevelRunner::beingWorldInteraction()
{
	glm::vec3 oldpos;
	glm::vec3 pos;
	cge::Model *tmpmdl;
	int x;
	int y;



	for (auto &being : _beings)
	{
		oldpos = being->getPosition();
		being->update(*_inputManager, _window.getFrameTime());
		pos = being->getPosition();
		x = (int) (round(pos.x));
		y = (int) (round(pos.z));
		if (being->get_n_moveDir().x != 0 || being->get_n_moveDir().z != 0 || being->is_placeBomb())
		{
			if (being == _player)
			{
				if (_gate && _gate->isActive() && y == _gate->getPosition().z &&
					x == _gate->getPosition().x)
					_state = levelState::COMPLEAT;

			}
			if (_level[y][x] != nullptr)
			{
				if (_level[(int) (round(oldpos.z))][(int) (round(oldpos.x))] == nullptr)
				{
					being->setPosition(oldpos);
					being->setMoveDir({0, 0, 0});
				} else if ((int) (round(oldpos.z)) != y ||
						   (int) (round(oldpos.x)) != x)
				{
					being->setPosition(oldpos);
					being->setMoveDir({0, 0, 0});
				}
			}
			bumpBeing(being);
			pos = being->getPosition();
			x = (int) (round(pos.x));
			y = (int) (round(pos.z));
			if (being->is_placeBomb() && (tmpmdl = getModel("Bomb")) != nullptr)
			{
				Bomb *nbomb = new Bomb({x, 0, y}, {0, 0, 0}, 1, *tmpmdl, 2);
				_level[y][x] = nbomb;
				_bombs.push_back(nbomb);
				being->placeBomb(nbomb);
			}
		}
	}
	for (auto &colBeing : _beings)
	{
		if (colBeing != _player)
		{
			glm::vec3 dist =_player->getPosition() - colBeing->getPosition();
			float fdist = cge::Maths::vec3Len(dist);
			glm::vec3 hit = _player->getHitBox() + colBeing->getHitBox();
			float fhit = cge::Maths::vec3Len(hit);
			std::cout << "pos len: " << fdist << " hit len " << fhit << std::endl;
			/*if (glm::length() < glm::length())
			{
				std::cout << "player being collision" << std::endl;
				_state = levelState ::FAIL;
				_player->loseLife();
			}*/
		}
	}
}

void LevelRunner::checkBeingBlast(int x, int y)
{
	std::vector<Being *>::iterator being;
	glm::vec3 beingPos;

	being = _beings.begin();
	while (being != _beings.end())
	{
		beingPos = (*being)->getPosition();
		if ((int) round(beingPos.x) == x && (int) round(beingPos.z) == y)
		{
			if ((*being) == _player)
			{
				std::cout << "player loose life. Player: " << (int) round(beingPos.x) << " " << (int) round(beingPos.z)
						  << std::endl;
				_player->loseLife();
				_state = levelState::WANTS_QUIT;
				being++;
			} else
			{
				delete ((*being));
				_beings.erase(being);
			}
		} else
			being++;
	}
}

void LevelRunner::bombWorldInteraction()
{
	int i;
	bool found;
	Bomb *tmpBomb;
	glm::vec3 bombPos;
	glm::vec3 beingPos;
	std::vector<Bomb *>::iterator bomb = _bombs.begin();
	std::vector<Being *>::iterator being;

	while (bomb != _bombs.end())
	{
		(*bomb)->update(*_inputManager, _window.getFrameTime());
		if ((*bomb)->isDeternate())
		{
			found = false;
			bombPos = (*bomb)->getPosition();
			being = _beings.begin();
			while (being != _beings.end())
			{
				if (!found && (*being)->checkBombDeterNation((*bomb)))
					found = true;
				beingPos = (*being)->getPosition();
				if ((int) beingPos.x == (int) bombPos.x && (int) beingPos.z == (int) bombPos.z)
				{
					if ((*being) == _player)
					{
						std::cout << "player loose life" << std::endl;
						being++;
					} else
					{
						delete ((*being));
						_beings.erase(being);
					}
				} else
					being++;
			}
			i = 0;
			while (++i < (*bomb)->getBombradius())
			{
				if (bombPos.z + i < _level.size())
				{
					checkWallBlast((int) (bombPos.x), (int) (bombPos.z + i));
					checkBeingBlast((int) (bombPos.x), (int) (bombPos.z + i));

				}
				if (bombPos.z - i >= 0)
				{
					checkWallBlast((int) (bombPos.x), (int) (bombPos.z - i));
					checkBeingBlast((int) (bombPos.x), (int) (bombPos.z - i));
				}
				if (bombPos.x + i < _level[bombPos.z].size())
				{
					checkWallBlast((int) (bombPos.x + i), (int) (bombPos.z));
					checkBeingBlast((int) bombPos.x + i, (int) (bombPos.z));
				}
				if (bombPos.x - i >= 0)
				{
					checkWallBlast((int) (bombPos.x - i), (int) (bombPos.z));
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

void LevelRunner::loadMapEntitys()
{
	srand((unsigned int) (time(NULL)));
	cge::Model *tmpMdl;
	cge::Entity *tmpEnt;
	int enemys;

	_dwalls = 0;
	enemys = stoi(_map[0]);
	_map.erase(_map.begin());
	_level.resize(_map.size());
	for (size_t i = 0; i < _map.size(); ++i)
	{
		_level[i].resize(_map[i].size());
		for (size_t j = 0; j < _map[i].length(); ++j)
		{
			switch (_map[i][j])
			{
				case 'w':
					if ((tmpMdl = getModel("Wall")) != nullptr)
					{
						tmpEnt = new cge::Entity({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, {0.5f, 0.0f, 0.5f});
						_level[i][j] = tmpEnt;
					}
					break;
				case 'p':
					_player->setPosition({j, 0, i});
					_beings.push_back(_player);
					_map[i][j] = '.';
					break;
				case 'd':
					if ((tmpMdl = getModel("DestructWall")) != nullptr)
					{
						tmpEnt = new DestructWall({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, {0.5f, 0.0f, 0.5f});
						_level[i][j] = tmpEnt;
						_dwalls++;
					}
					break;
				default:
					if (enemys > 0)
					{

						if (rand() % 6 == 1)
						{
							if ((tmpMdl = getModel("Balloon")) != nullptr)
							{
								_beings.push_back(new Balloon({j, 0, i}, {0, 0, 0}, 1, *tmpMdl, {0.5f, 0.0f, 0.5f}));
								enemys--;
							}
						}
					}
					break;
			}
		}
	}
}

void LevelRunner::checkWallBlast(int x, int y)
{
	cge::Model *tmpMdl;

	if (dynamic_cast<DestructWall *>(_level[y][x]) != NULL)
	{
		delete (_level[y][x]);
		_level[y][x] = nullptr;
		_dwalls--;
		srand((unsigned int) time(NULL) + _dwalls);
		if (_gate == nullptr)
		{
			if (_dwalls == 0)
			{
				if ((tmpMdl = getModel("Gate")) != nullptr)
					_gate = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
				std::cout << "make gate" << std::endl;
			} else if (rand() % 2 == 1)
			{
				if ((tmpMdl = getModel("Gate")) != nullptr)
					_gate = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
			}
		}

	}
}

void LevelRunner::endlevel()
{
	unsigned endTime = 0;
	while (endTime < 1000)
	{
		_shader.start();
		_renderer.prepare();
		_camera.update(_shader);
		for (auto &vecit : _level)
		{
			for (auto &entit : vecit)
			{
				if (entit != nullptr)
					_renderer.render(*entit);
			}
		}
		for (auto being : _beings)
			_renderer.render(*being);
		if (_gate != nullptr)
			_renderer.render(*_gate);
		_shader.end();
		_window.swapBuffers();
		endTime += _window.getFrameTime();
	}
}

int LevelRunner::runLevel(std::vector<std::string> map)
{
	//std::cout << levelPath << "\n";
	_map = map;
	_gate = nullptr;
	_state = levelState::PLAY_MENU;
	loadMapEntitys();

	while (_state == levelState::PLAY_MENU)
	{
		_inputManager->poolKeyEvnt();
		if (_inputManager->isExitCase() || _inputManager->isKeyPressed(GLFW_KEY_ESCAPE) || _player->getLives() <= 0)
		{
			_state = levelState::WANTS_QUIT;
		}
		if (_beings.size() == 1 && _gate != nullptr)
			_gate->actervate();
		beingWorldInteraction();
		bombWorldInteraction();
		glm::vec3 plpos = _player->getPosition();
		_camera.setPosition({plpos.x, 10, plpos.z});
		_shader.start();
		_renderer.prepare();
		_camera.update(_shader);
		for (auto &vecit : _level)
		{
			for (auto &entit : vecit)
			{
				if (entit)
					_renderer.render(*entit);
			}
		}
		for (auto being : _beings)
			_renderer.render(*being);
		if (_gate != nullptr)
			_renderer.render(*_gate);
		_shader.end();
		_window.swapBuffers();
	}
	endlevel();
	return _state;
}









