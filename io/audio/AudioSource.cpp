#include "AudioSource.hpp"

cge::Audio::Source::Source() {
	this->Init(1.0, 1.0, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, false);
}

cge::Audio::Source::Source(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping) {
	this->Init(pitch, gain, position, velocity, isLooping);
}

cge::Audio::Source::~Source() {
	alDeleteSources(1, &this->_sourceID);
}

void cge::Audio::Source::Init(ALfloat pitch, ALfloat gain, const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping) {
	alGenSources(1, &this->_sourceID);

	this->setPitch(pitch);
	this->setGain(gain);
	this->setPosition(position);
	this->setVelocity(velocity);
	this->setLooping(isLooping);
}

void cge::Audio::Source::setPitch(ALfloat pitch) {
	this->_pitch = pitch;
	alSourcef(this->_sourceID, AL_PITCH, this->_pitch);
}

void cge::Audio::Source::setGain(ALfloat gain) {
	this->_gain = gain;
	alSourcef(this->_sourceID, AL_GAIN, this->_gain);
}

void cge::Audio::Source::setPosition(const glm::vec3 &position) {
	this->_position = position;
	alSource3f(this->_sourceID, AL_POSITION, this->_position.x, this->_position.y, this->_position.z);
}

void cge::Audio::Source::setVelocity(const glm::vec3 &velocity) {
	this->_velocity = velocity;
	alSource3f(this->_sourceID, AL_VELOCITY, this->_velocity.x, this->_velocity.y, this->_velocity.z);
}

void cge::Audio::Source::setLooping(bool isLooping) {
	this->_isLooping = isLooping;
	alSourcei(this->_sourceID, AL_LOOPING, this->_isLooping ? AL_TRUE : AL_FALSE);
}

cge::Audio::Source::Source(const std::string &audioFilePath) {

}