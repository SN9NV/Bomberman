#include "AudioListener.hpp"

cge::Audio::Listener::Listener(cge::Audio::Device &device) :
	_device(device)
{

}

void cge::Audio::Listener::setLocation(const glm::vec3 &location) {
	this->_location = location;
	alListener3f(AL_POSITION, location.x, location.y, location.z);
}

void cge::Audio::Listener::setVelocity(const glm::vec3 &velocity) {
	this->_velocity = velocity;
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
}

void cge::Audio::Listener::setOrientation(float *orientation) {
	this->_orientation = orientation;
	alListenerfv(AL_ORIENTATION, orientation);
}
