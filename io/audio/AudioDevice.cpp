#include <iostream>
#include "AudioDevice.hpp"

cge::Audio::Device::Device() {
	this->_Init(this->defaultDevice());
}

cge::Audio::Device::Device(const std::string &deviceName) {
	this->_Init(deviceName);
}

void cge::Audio::Device::_Init(const std::string &deviceName) {
	this->_deviceName	= deviceName;
	this->_device		= alcOpenDevice(deviceName.c_str());
	this->_context		= alcCreateContext(this->_device, nullptr);

	this->_location		= { 0.0f, 0.0f, 0.0f };
	this->_velocity		= { 0.0f, 0.0f, 0.0f };
	this->_orientation	= { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	this->setToCurrentContext();
}

std::vector<std::string> cge::Audio::Device::listDevices() {
	const ALCchar				*device = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
	const ALCchar				*next = device + 1;
	std::vector<std::string>	devices;

	while (device != nullptr && *device != 0 && next != nullptr && *next != 0) {
		std::string	deviceStr(device);
		devices.push_back(deviceStr);

		size_t len = deviceStr.length();
		device += (len + 1);
		next += (len + 2);
	}

	return devices;
}

std::string cge::Audio::Device::defaultDevice() {
	return std::string(alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER));
}

cge::Audio::Device::~Device() {
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(this->_context);
	alcCloseDevice(this->_device);
}

std::string cge::Audio::Device::getDeviceName() const {
	return this->_deviceName;
}

void cge::Audio::Device::setToCurrentContext() const {
	if (alcMakeContextCurrent(this->_context) == AL_FALSE) {
		std::cerr << "failed to make context current\n";
		exit(1);
	}
}

void cge::Audio::Device::update() const {
	this->updateLocation();
	this->updateVelocity();
	this->updateOrientation();
}

const ALCdevice *cge::Audio::Device::getDevice() const {
	return this->_device;
}

const ALCcontext *cge::Audio::Device::getContext() const {
	return this->_context;
}

void cge::Audio::Device::setLocation(const glm::vec3 &location, bool update) {
	this->_location = location;

	if (update) {
		this->updateVelocity();
	}
}

void cge::Audio::Device::updateLocation() const {
	alListener3f(AL_POSITION, this->_location.x, this->_location.y, this->_location.z);
}

void cge::Audio::Device::setVelocity(const glm::vec3 &velocity, bool update) {
	this->_velocity = velocity;

	if (update) {
		this->updateVelocity();
	}
}

void cge::Audio::Device::updateVelocity() const {
	alListener3f(AL_VELOCITY, this->_velocity.x, this->_velocity.y, this->_velocity.z);
}

void cge::Audio::Device::setOrientation(const std::vector<float> &orientation, bool update) {
	if (orientation.size() != 6) {
		std::cerr << "Size of orientation vector has to be 6\n";
		exit(1);
	}

	this->_orientation = orientation;

	if (update) {
		this->updateOrientation();
	}
}

void cge::Audio::Device::updateOrientation() const {
	alListenerfv(AL_ORIENTATION, this->_orientation.data());
}

glm::vec3 cge::Audio::Device::getLocation() const {
	return this->_location;
}

glm::vec3 cge::Audio::Device::getVelocity() const {
	return this->_velocity;
}

std::vector<float> cge::Audio::Device::getOrientation() const {
	return this->_orientation;
}


