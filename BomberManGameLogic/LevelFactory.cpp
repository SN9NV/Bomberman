//
// Created by Robert JONES on 2017/08/24.
//

#include "LevelFactory.hpp"


LevelFactory::LevelFactory(cge::Loader &loader, std::vector<std::vector<cge::Entity *>> &level,
						   Player &player) : _loader(loader), _level(level), _player(player), _damage(2) {



	_map.emplace("AddBomb", std::pair<cge::Model, func> (cge::Model(resRoot + "Bomb.glb", resRoot + "ADDBombDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeAddBomb));
	_map.emplace("Wall", std::pair<cge::Model, func> (cge::Model(resRoot + "Wall.glb", resRoot + "SolidWallDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeWall));
	_map.emplace("DestructWall", std::pair<cge::Model, func> (cge::Model(resRoot + "DestructWall.glb", resRoot + "DestructWallDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeDestructWall));
	_map.emplace("Bomb", std::pair<cge::Model, func> (cge::Model(resRoot + "Bomb.glb", resRoot + "BombDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeBomb));
	//_map.emplace("Bomber", std::pair<cge::Model, func> (cge::Model(resRoot + "Bomber.glb", resRoot + "BomberManTextureDiffuseColor.png", _loader, cge::Model::Type::STREAMING), makeWall));
	_map.emplace("Balloon", std::pair<cge::Model, func> (cge::Model(resRoot + "Balloon.glb", resRoot + "BalloonDiffuseColor.png", _loader, cge::Model::Type::STREAMING), makeBalloon));
	_map.emplace("Onile", std::pair<cge::Model, func> (cge::Model(resRoot + "Onile.glb", resRoot + "OnileDiffuseColor.png", _loader, cge::Model::Type::STREAMING), makeOnile));
	_map.emplace("Gate", std::pair<cge::Model, func> (cge::Model(resRoot + "Gate.glb", resRoot + "GateDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeGate));
	_map.emplace("FireUp", std::pair<cge::Model, func> (cge::Model(resRoot + "FireUp.glb", resRoot + "FireUpDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeFireUp));
	_map.emplace("FireDown", std::pair<cge::Model, func> (cge::Model(resRoot + "FireDown.glb", resRoot + "FireDownDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeFireDown));
	_map.emplace("FullFire", std::pair<cge::Model, func> (cge::Model(resRoot + "FullFire.glb", resRoot + "FullFireDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeFullFire));
	_map.emplace("WingBoot", std::pair<cge::Model, func> (cge::Model(resRoot + "WingBoot.glb", resRoot + "WingdBootDiffuseColor.png", _loader, cge::Model::Type::STATIC), makeWingBoot));

}

cge::Entity *LevelFactory::makeAddBomb(glm::vec3 position, cge::Model &model) {
	return new AddBomb(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeBalloon(glm::vec3 position, cge::Model &model) {
	return new Balloon(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeBomb(glm::vec3 position, cge::Model &model) {
	return new Bomb(position, {0,0,0}, 1, model,_loader, _damage, 0.3);
}

cge::Entity *LevelFactory::makeDestructWall(glm::vec3 position, cge::Model &model) {
	srand(time(NULL));
	float rotation = (rand() % 4) * 90;
	return new DestructWall(position, {0, glm::radians(rotation), 0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeFireDown(glm::vec3 position, cge::Model &model) {
	return new FireDown(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeFireUp(glm::vec3 position, cge::Model &model) {
	return new FireUp(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeFullFire(glm::vec3 position, cge::Model &model) {
	return new FullFire(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeGate(glm::vec3 position, cge::Model &model) {
	return new Gate(position, {0,0,0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeOnile(glm::vec3 position, cge::Model &model) {
	return new Onil(position, {0,0,0}, 1, model,_loader, _player, _level);
}

cge::Entity *LevelFactory::makeWall(glm::vec3 position, cge::Model &model) {
	return new Wall(position, {0,0,0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeWingBoot(glm::vec3 position, cge::Model &model) {
	return new WingBoot(position, {0,0,0}, 1, model,_loader, 0.3);
}

void LevelFactory::setDamage(int _damage) {
	LevelFactory::_damage = _damage;
}

void LevelFactory::setLevel(std::vector<std::vector<cge::Entity *>> &_level) {
	LevelFactory::_level = _level;
}

cge::Entity *LevelFactory::loadObject(std::string object, glm::vec3 position) {
	auto find = _map.find(object);

	if (find == _map.end())
		return nullptr;
	return (find->second.second)(position, find->second.first);
}

bool LevelFactory::has(std::string object) {
	return  (_map.find(object) != _map.end());

}
