//
// Created by Owen Exall on 2017/08/18.
//

#include "Settings.hpp"

cge::Settings::Settings *cge::Settings::Settings::s_instance = nullptr;

void cge::Settings::Settings::Initialise(std::string file) {
	if (s_instance == nullptr) {
		s_instance = new cge::Settings::Settings(file);
	}
}

cge::Settings::Settings *cge::Settings::Settings::getSingleton() {
	if (s_instance == nullptr) {
		throw BombermanException("Settings not initialized");
	}
	return (s_instance);
}

cge::Settings::Settings::Settings(std::string file) {
	this->_fileName = file;
	this->readFromBinaryFile();
}

cge::Settings::t_settings cge::Settings::Settings::getSettings() const {
	return (this->_settings);
}

void cge::Settings::Settings::readFromBinaryFile() {
	std::ifstream ifs(this->_fileName, std::ios::binary);
	if (ifs.good()) {
		ifs.read((char*)&_settings, sizeof(_settings));
		ifs.close();
	} else {
		this->setToDefaults();
		this->writeToBinaryFile();
	}
}

void cge::Settings::Settings::writeToBinaryFile() {
	std::ofstream ofs(this->_fileName, std::ios::binary);
	if (ofs.good()) {
		ofs.write((char*)&_settings, sizeof(_settings));
		ofs.close();
	} else {
		std::cerr << "Failed to write settings file." << std::endl;
	}
}

void cge::Settings::Settings::setMasterVolume(float mv) {
	this->_settings.MasterVolume = mv;
}

void cge::Settings::Settings::setMusicVolume(float mv) {
	this->_settings.MusicVolume = mv;
}

void cge::Settings::Settings::setSfxVolume(float mv) {
	this->_settings.SfxVolume = mv;
}

void cge::Settings::Settings::setKeyUpwards(unsigned int ku) {
	this->_settings.KeyUpwards = ku;
}

void cge::Settings::Settings::setKeyRight(unsigned int kr) {
	this->_settings.KeyRight = kr;
}

void cge::Settings::Settings::setKeyDown(unsigned int kd) {
	this->_settings.KeyDown = kd;
}

void cge::Settings::Settings::setKeyLeft(unsigned int kl) {
	this->_settings.KeyLeft = kl;
}

void cge::Settings::Settings::setToDefaults() {
	this->_settings.KeyUpwards = GLFW_KEY_W;
	this->_settings.KeyRight = GLFW_KEY_D;
	this->_settings.KeyDown = GLFW_KEY_S;
	this->_settings.KeyLeft = GLFW_KEY_A;

	this->_settings.MasterVolume = 0.5f;
	this->_settings.MusicVolume = 0.8f;
	this->_settings.SfxVolume = 0.01f;
}
