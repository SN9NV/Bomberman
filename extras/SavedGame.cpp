//
// Created by Owen Exall on 2017/08/18.
//

#include "SavedGame.hpp"

int cge::Saves::SavedGame::getSlot() const {
	return _slot;
}

void cge::Saves::SavedGame::setSlot(int _slot) {
	SavedGame::_slot = _slot;
}

bool cge::Saves::SavedGame::isAvailable() const {
	return _available;
}

void cge::Saves::SavedGame::setAvailable(bool _available) {
	SavedGame::_available = _available;
}

const std::string &cge::Saves::SavedGame::getFileName() const {
	return _fileName;
}

void cge::Saves::SavedGame::setFileName(const std::string &_fileName) {
	SavedGame::_fileName = _fileName;
}

const std::string &cge::Saves::SavedGame::getCreationTime() const {
	return _creationTime;
}

void cge::Saves::SavedGame::setCreationTime(const std::string &_creationTime) {
	SavedGame::_creationTime = _creationTime;
}

cge::Saves::SavedGame::SavedGame() {

}

cge::Saves::SavedGame::~SavedGame() {

}
