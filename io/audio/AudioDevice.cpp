#include <iostream>
#include "AudioDevice.hpp"

cge::Audio::Device::Device(const std::string &deviceName) {
	this->_device = alcOpenDevice(deviceName.c_str());

	this->_context = alcCreateContext(this->_device, nullptr);

	if (alcMakeContextCurrent(this->_context) == AL_FALSE) {
		std::cerr << "failed to make default context\n";
		exit(1);
	}
}

std::vector<std::string> cge::Audio::Device::listDevices() {
	const ALCchar				*device = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
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
