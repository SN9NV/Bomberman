//
// Created by rojones on 2017/08/09.
//

#include "LevelRunner.hpp"
#include "DestructWall.hpp"

LevelRunner::LevelRunner(cge::Loader &_loader, Player *_player,
						 const cge::Window &_window) : _loader(_loader), _player(_player),
													   _window(_window),
													   _shader("../shaders/vertex.glsl", "../shaders/fragment.glsl"),
													   _renderer(_shader),
													   _camera(glm::vec3(0.0f, 20.0f, 0.0f),
															   glm::vec3(1.4f, 0.0f, 0.0f), _window)
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
	cge::Model *tmpmdl;
	glm::vec3 pos;
	float dir;
	bool upx;
	bool upy;
	int x;
	int y;

	for (auto &being : _beings)
	{
		pos = being->getPosition();
		//	_level[(int)pos.z][(int)pos.x] = nullptr;
		//	std::cout <<"on "<< pos.x << " " << pos.z << " nclearing " << (int)pos.x << " " << (int)pos.z << std::endl;
		being->update(_inputManager, _window.getFrameTime());
		pos = being->get_n_moveDir();
		if (pos.x != 0 || pos.z != 0 || being->is_placeBomb())
		{
			pos = being->getPosition();
			upx = false;
			upy = false;
			pos = being->getPosition();
			dir = being->getDirAngle();
			if (dir > -90 && dir < 90)
			{
				y = (int) ceil(pos.z);
				upy = true;
			} else if (dir == -90 || dir == 90)
				y = (int) round(pos.z);
			else
				y = (int) floor(pos.z);
			if (dir > 0 && dir < 180)
			{
				x = (int) ceil(pos.x);
				upx = true;
			} else if (dir == 180 || dir == 0)
				x = (int) round(pos.x);
			else
				x = (int) floor(pos.x);
			if (_level[y][x] != nullptr || being->is_placeBomb())
				being->setPosition({(upx) ? floor(pos.x) : ceil(pos.x), pos.y, (upy) ? floor(pos.z) : ceil(pos.z)});
			if (being->is_placeBomb() && (tmpmdl = getModel("Bomb")) != nullptr)
			{
				std::cout << "plaving bomb" << std::endl;
				Bomb *nbomb = new Bomb(being->getPosition(), {0, 0, 0}, 1, *tmpmdl, 2);
				_map[being->getPosition().z][being->getPosition().x] = 'b';
				_level[being->getPosition().z][being->getPosition().x] = nbomb;
				_bombs.push_back(nbomb);
				being->placeBomb(nbomb);
			}
		}
		//	pos = being->getPosition();
		//	_level[(int)pos.z][(int)pos.x] = being;
	}
}

void LevelRunner::bombWorldInteraction()
{
	int i;
	Bomb *tmpBomb;
	glm::vec3 bomPos;
	std::vector<Bomb *>::iterator bomb = _bombs.begin();

	while (bomb != _bombs.end())
	{
		(*bomb)->update(_inputManager, _window.getFrameTime());
		if ((*bomb)->isDeternate())
		{
			for (std::vector<Being *>::iterator being = _beings.begin(); being != _beings.end(); being++)
			{
				if ((*being)->checkBombDeterNation((*bomb)))
					break;
			}
			i = 0;
			bomPos = (*bomb)->getPosition();
			while (++i < (*bomb)->getBombradius())
			{
				if (bomPos.z + i < _level.size() && _level[bomPos.z + i][bomPos.x] != nullptr)
				{
					if (dynamic_cast<DestructWall *>(_level[bomPos.z + i][bomPos.x]) != NULL)
					{
						delete (_level[bomPos.z + i][bomPos.x]);
						_level[bomPos.z + i][bomPos.x] = nullptr;
					}
				}
				if (bomPos.z - i >= 0 && _level[bomPos.z - i][bomPos.x] != nullptr)
				{
					if (dynamic_cast<DestructWall *>(_level[bomPos.z - i][bomPos.x]) != NULL)
					{
						delete (_level[bomPos.z - i][bomPos.x]);
						_level[bomPos.z - i][bomPos.x] = nullptr;
					}
				}
				if (bomPos.x + i < _level[bomPos.z].size() && _level[bomPos.z][bomPos.x + i] != nullptr)
				{
					if (dynamic_cast<DestructWall *>(_level[bomPos.z][bomPos.x + i]) != NULL)
					{
						delete (_level[bomPos.z][bomPos.x + i]);
						_level[bomPos.z][bomPos.x + i] = nullptr;
					}
				}
				if (bomPos.x - i >= 0 && _level[bomPos.z][bomPos.x - i] != nullptr)
				{
					if (dynamic_cast<DestructWall *>(_level[bomPos.z][bomPos.x - i]) != NULL)
					{
						delete (_level[bomPos.z][bomPos.x - i]);
						_level[bomPos.z][bomPos.x - i] = nullptr;
					}
				}
			}
			_level[bomPos.z][bomPos.x] = NULL;
			tmpBomb = (*bomb);
			delete (tmpBomb);
			_bombs.erase(bomb);
		} else
			bomb++;

	}
}

void LevelRunner::loadMapEntitys()
{
	cge::Model *tmpMdl;
	cge::Entity *tmpEnt;

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
						//_walls.push_back(tmpEnt);
						_level[i][j] = tmpEnt;
					}
					break;
				case 'p':
					//_level[i][j] = _player;
					_player->setPosition({j, 0, i});
					_beings.push_back(_player);
					_map[i][j] = '.';
					break;
				case 'd':
					if ((tmpMdl = getModel("DestructWall")) != nullptr)
					{
						tmpEnt = new DestructWall({j, 0, i}, {0, 0, 0}, 1, *tmpMdl);
						_level[i][j] = tmpEnt;
						//_destructWalls.push_back(tmpEnt);
					}
			}
		}
	}
}

void LevelRunner::runLevel(std::vector<std::string> map)
{
	//std::cout << levelPath << "\n";
	_map = map;

	int state = levelState::PLAY;
	loadMapEntitys();
	while (state != levelState::WANTS_QUIT)
	{
		_inputManager.poolKeyEvnt();
		if (_inputManager.isExitCase() || _inputManager.isKeyPressed(SDLK_ESCAPE))
		{
			state = levelState::WANTS_QUIT;
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
		/*for (auto &wall : _walls)
		{
			_renderer.render(*wall);
		}
		for (auto &dwall : _destructWalls)
			_renderer.render(*dwall);
		for (auto bomb : _bombs)
		{
			_renderer.render(*bomb);
		}
		*/
		_shader.end();
		_window.swapBuffers();
	}

}


