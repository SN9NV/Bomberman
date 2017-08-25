//
// Created by Robert JONES on 2017/08/24.
//

#ifndef BOMBERMAN_LEVELFACTORY_HPP
#define BOMBERMAN_LEVELFACTORY_HPP


#include "../loaders/Loader.hpp"
#include "Bomb.hpp"
#include "Wall.hpp"
#include "Balloon.hpp"
#include "DestructWall.hpp"
#include "FireDown.hpp"
#include "FireUp.hpp"
#include "FullFire.hpp"
#include "Gate.hpp"
#include "Onil.hpp"
#include "WingBoot.hpp"
#include "AddBomb.hpp"

class LevelFactory {

	typedef cge::Entity *(*func) (glm::vec3 position, cge::Model &model);

public:
	enum objID{
		AddBomb = 0,
		Balloon,
		Bomb,
		DestructWall,
		Deternator,
		FireDown,
		FireUp,
		FullFire,
		Gate,
		Onile,
		Ovapi,
		Wall,
		WingBoot
	};

private:
	cge::Loader &_loader;
	std::vector<std::vector<cge::Entity *>> &_level;
	Player &_player;
	const std::string resRoot = "resources/models/";
	int _damage;
	float _bombtime;
	std::map<std::string, std::pair<cge::Model, unsigned int>> _map;

	cge::Entity *makeAddBomb(glm::vec3 position, cge::Model &model);
	cge::Entity *makeBalloon(glm::vec3 position, cge::Model &model);
	cge::Entity *makeBomb(glm::vec3 position, cge::Model &model);
	cge::Entity *makeDestructWall(glm::vec3 position, cge::Model &model);
	cge::Entity *makeDeternator(glm::vec3 position, cge::Model &model);
	cge::Entity *makeFireDown(glm::vec3 position, cge::Model &model);
	cge::Entity	*makeFireUp(glm::vec3 position, cge::Model &model);
	cge::Entity *makeFullFire(glm::vec3 position, cge::Model &model);
	cge::Entity *makeGate(glm::vec3 position, cge::Model &model);
	cge::Entity *makeOnile(glm::vec3 position, cge::Model &model);
	cge::Entity *makeOvapi(glm::vec3 position, cge::Model &model);
	cge::Entity *makeWall(glm::vec3 position, cge::Model &model);
	cge::Entity *makeWingBoot(glm::vec3 position, cge::Model &model);

public:
	void setLevel(std::vector<std::vector<cge::Entity *>> &_level);
	LevelFactory(cge::Loader &_loader,  std::vector<std::vector<cge::Entity *>> &level,  Player &player);
	cge::Entity *loadObject(std::string object, glm::vec3 position);
	void setDamage(int _damage);
	bool has(std::string object);
	void setBombTime(float time);

};


#endif //BOMBERMAN_LEVELFACTORY_HPP
