//
// Created by rojones on 2017/08/09.
//

#include "LevelRunner.hpp"
#include "DestructWall.hpp"
#include "Gate.hpp"
#include "Balloon.hpp"

LevelRunner::LevelRunner(cge::Loader &_loader, Player *_player,
						 const cge::Window &_window) : _loader(_loader), _player(_player),
													   _window(_window),
													   _shader("../shaders/vertex.glsl", "../shaders/fragment.glsl"),
													   _renderer(_shader),
													   _camera(glm::vec3(0.0f, 20.0f, 0.0f),
															   glm::vec3(1.4f, 0.0f, 0.0f), _window),
													   _gate(false)
{
	_models.emplace("Wall",
					cge::Model("../resources/models/Wall.glb", "../resources/models/SolidWallDiffuseColor.png",
							   _loader));
	_models.emplace("DestructWall", cge::Model("../resources/models/DestructWall.glb",
											   "../resources/models/DestructWallDiffuseColor.png", _loader));
	_models.emplace("Bomb",
					cge::Model("../resources/models/Bomb.glb", "../resources/models/BombDiffuseColor.png", _loader));
	_models.emplace("Bomber",
					cge::Model("../resources/models/Bomber.glb", "../resources/models/BomberManTextureDiffuseColor.png",
							   _loader));
	_models.emplace("Balloon",
					cge::Model("../resources/models/Balloon.glb", "../resources/models/BalloonDiffuseColor.png",
							   _loader));
	_models.emplace("Gate",
					cge::Model("../resources/models/Gate.glb", "../resources/models/GateDiffuseColor.png",
							   _loader));
}

cge::Model *LevelRunner::getModel(std::string name)
{
	auto found = _models.find(name);
	if (found != _models.end())
		return (&found->second);
	return (nullptr);
}

void LevelRunner::beingWorldInteraction()
{
	glm::vec3 oldpos;
	glm::vec3 pos;
	cge::Model *tmpmdl;
	Gate *gate;

	for (auto &being : _beings)
	{
		oldpos = being->getPosition();
		being->update(_inputManager, _window.getFrameTime());
		pos = being->getPosition();
		if (being->get_n_moveDir().x != 0 || being->get_n_moveDir().z != 0 || being->is_placeBomb())
		{
			if (_level[(int) (round(pos.z))][(int) (round(pos.x))] != nullptr)
			{
				if ((gate = dynamic_cast<Gate *>(_level[(int) (round(pos.z))][(int) (round(pos.x))])) != NULL)
				{
					if (_beings.size() == 1)
						gate->actervate();
					if (being == _player && gate->isActive())
						_state = levelState::COMPLEAT;
				} else if (_level[(int) (round(oldpos.z))][(int) (round(oldpos.x))] == nullptr)
				{
					being->setPosition(oldpos);
					being->setMoveDir({0,0,0});
				}
				else if ((int) (round(oldpos.z)) != (int) (round(pos.z)) ||
						 (int) (round(oldpos.x)) != (int) (round(pos.x)))
				{
					being->setPosition(oldpos);
					being->setMoveDir({0,0,0});
				}
			}
			pos = being->getPosition();
			if (being->is_placeBomb() && (tmpmdl = getModel("Bomb")) != nullptr)
			{
				std::cout << "plaving bomb" << std::endl;
				Bomb *nbomb = new Bomb({(int) (round(pos.x)), 0, (int) (round(pos.z))}, {0, 0, 0}, 1, *tmpmdl, 2);
				_level[(int) (round(pos.z))][(int) (round(pos.x))] = nbomb;
				_bombs.push_back(nbomb);
				being->placeBomb(nbomb);
			}
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
		(*bomb)->update(_inputManager, _window.getFrameTime());
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
						tmpEnt = new cge::Entity({j, 0, i}, {0, 0, 0}, 1, *tmpMdl);
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
						tmpEnt = new DestructWall({j, 0, i}, {0, 0, 0}, 1, *tmpMdl);
						_level[i][j] = tmpEnt;
						_dwalls++;
					}
					break;
				default:
					if (enemys > 0)
					{

						if (rand()%6 == 1)
						{
							if ((tmpMdl = getModel("Balloon")) != nullptr)
							{
								_beings.push_back(new Balloon({j, 0, i}, {0, 0, 0}, 1, *tmpMdl));
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
	cge::Entity *tmpEnt;

	if (dynamic_cast<DestructWall *>(_level[y][x]) != NULL)
	{
		delete (_level[y][x]);
		_level[y][x] = nullptr;
		_dwalls--;
		srand((unsigned int) time(NULL) + _dwalls);
		if (!_gate)
		{
			if (_dwalls == 0)
			{
				if ((tmpMdl = getModel("Gate")) != nullptr)
				{
					tmpEnt = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
					_level[y][x] = tmpEnt;
				}
				_gate = true;
				std::cout << "make gate" << std::endl;
			} else if (rand() % 2 == 1)
			{
				if ((tmpMdl = getModel("Gate")) != nullptr)
				{
					tmpEnt = new Gate({x, 0, y}, {0, 0, 0}, 1, *tmpMdl);
					_level[y][x] = tmpEnt;
				}
				_gate = true;
				std::cout << "make gate" << std::endl;
			}
		}

	}
}

int LevelRunner::runLevel(std::vector<std::string> map)
{
	//std::cout << levelPath << "\n";
	_map = map;
	_state = levelState::PLAY;
	loadMapEntitys();

	while (_state == levelState::PLAY)
	{
		_inputManager.poolKeyEvnt();
		if (_inputManager.isExitCase() || _inputManager.isKeyPressed(SDLK_ESCAPE) || _player->getLives() <= 0)
		{
			_state = levelState::WANTS_QUIT;
		}

		beingWorldInteraction();
		bombWorldInteraction();
		glm::vec3 plpos = _player->getPosition();
		_camera.setPosition({plpos.x, 20, plpos.z});
		_shader.start();
		_renderer.prepare();
		_camera.update(_shader);
		for (std::vector<std::vector<cge::Entity *>>::iterator vecit = _level.begin(); vecit != _level.end(); vecit++)
		{
			for (std::vector<cge::Entity *>::iterator entit = (*vecit).begin(); entit != (*vecit).end(); entit++)
			{
				if ((*entit))
					_renderer.render(*(*entit));
			}
		}
		for (auto being : _beings)
			_renderer.render(*being);
		_shader.end();
		_window.swapBuffers();
	}
	return _state;
}





