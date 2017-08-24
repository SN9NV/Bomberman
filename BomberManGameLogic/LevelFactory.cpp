//
// Created by Robert JONES on 2017/08/24.
//

#include "LevelFactory.hpp"
#include "Deternator.hpp"


LevelFactory::LevelFactory(cge::Loader &loader, std::vector<std::vector<cge::Entity *>> &level,
						   Player &player) : _loader(loader), _level(level), _player(player), _damage(2), _bombtime(2000) {



	_map.emplace("AddBomb", std::pair<cge::Model, unsigned int>(cge::Model(resRoot + "Bomb.glb", resRoot + "ADDBombDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::AddBomb));
	_map.emplace("Wall", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Wall.glb", resRoot + "SolidWallDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::Wall));
	_map.emplace("Deternator", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Deternator.glb", resRoot + "DetornatorDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::Deternator));
	_map.emplace("DestructWall", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "DestructWall.glb", resRoot + "DestructWallDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::DestructWall));
	_map.emplace("Bomb", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Bomb.glb", resRoot + "BombDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::Bomb));
	//_map.emplace("Bomber", std::pair<cge::Model, func> (cge::Model(resRoot + "Bomber.glb", resRoot + "BomberManTextureDiffuseColor.png", _loader, cge::Model::Type::STREAMING), makeWall));
	_map.emplace("Balloon", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Balloon.glb", resRoot + "BalloonDiffuseColor.png", _loader, cge::Model::Type::STREAMING), objID::Balloon));
	_map.emplace("Onile", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Onile.glb", resRoot + "OnileDiffuseColor.png", _loader, cge::Model::Type::STREAMING), objID::Onile));
	_map.emplace("Gate", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "Gate.glb", resRoot + "GateDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::Gate));
	_map.emplace("FireUp", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "FireUp.glb", resRoot + "FireUpDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::FireUp));
	_map.emplace("FireDown", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "FireDown.glb", resRoot + "FireDownDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::FireDown));
	_map.emplace("FullFire", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "FullFire.glb", resRoot + "FullFireDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::FullFire));
	_map.emplace("WingBoot", std::pair<cge::Model, unsigned int> (cge::Model(resRoot + "WingBoot.glb", resRoot + "WingdBootDiffuseColor.png", _loader, cge::Model::Type::STATIC), objID::WingBoot));

}

cge::Entity *LevelFactory::makeAddBomb(glm::vec3 position, cge::Model &model) {
	return new class AddBomb(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeBalloon(glm::vec3 position, cge::Model &model) {
	return new class Balloon(position, {0,0,0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeBomb(glm::vec3 position, cge::Model &model) {
	return new class Bomb(position, {0,0,0}, 1, model,_loader, _damage, _bombtime, 0.3);
}

cge::Entity *LevelFactory::makeDestructWall(glm::vec3 position, cge::Model &model) {
	srand(time(NULL));
	float rotation = (rand() % 4) * 90;
	return new class DestructWall(position, {0, glm::radians(rotation), 0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeFireDown(glm::vec3 position, cge::Model &model) {
	return new class FireDown(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeFireUp(glm::vec3 position, cge::Model &model) {
	return new class FireUp(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeFullFire(glm::vec3 position, cge::Model &model) {
	return new class FullFire(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeGate(glm::vec3 position, cge::Model &model) {
	return new class Gate(position, {0,0,0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeOnile(glm::vec3 position, cge::Model &model) {
	return new Onil(position, {0,0,0}, 1, model,_loader, _player, _level);
}

cge::Entity *LevelFactory::makeWall(glm::vec3 position, cge::Model &model) {
	return new class Wall(position, {0,0,0}, 1, model,_loader, 0.5);
}

cge::Entity *LevelFactory::makeWingBoot(glm::vec3 position, cge::Model &model) {
	return new class WingBoot(position, {0,0,0}, 1, model,_loader, 0.3);
}

cge::Entity *LevelFactory::makeDeternator(glm::vec3 position, cge::Model &model) {
	return new class Deternator(position, {0,0,0}, 1, model,_loader, 0.3);
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
	switch(find->second.second){
		case objID::AddBomb :
			return makeAddBomb(position, find->second.first);
		case objID::Wall :
			return makeWall(position, find->second.first);
		case objID::DestructWall :
			return makeDestructWall(position, find->second.first);
		case objID::Deternator:
			return makeDeternator(position, find->second.first);
		case objID::Balloon :
			return makeBalloon(position, find->second.first);
		case objID::Bomb :
			return makeBomb(position, find->second.first);
		case objID::FireDown :
			return makeFireDown(position, find->second.first);
		case objID::FireUp :
			return makeFireUp(position, find->second.first);
		case objID::FullFire :
			return makeFullFire(position, find->second.first);
		case objID::Gate :
			return makeGate(position, find->second.first);
		case objID::Onile :
			return makeOnile(position, find->second.first);
		case objID::WingBoot :
			return makeWingBoot(position, find->second.first);
		default:
			return nullptr;
	}
}

bool LevelFactory::has(std::string object) {
	return  (_map.find(object) != _map.end());

}

void LevelFactory::setBombTime(float time) {
	_bombtime = time;
}


