#include <iostream>
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

	this->_bufferID = 0;
	this->_sfInfo = {};
}

void cge::Audio::Source::setAudio(const std::string &audioFilePath, cge::Loader &loader) {
	cge::Loader::AudioFile audioFile = loader.loadAudio(audioFilePath);

	this->_bufferID = audioFile.bufferID;
	this->_sfInfo = audioFile.info;

	alSourcei(this->_sourceID, AL_BUFFER, this->_bufferID);
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

ALfloat cge::Audio::Source::getPitch() const {
	return this->_pitch;
}

ALfloat cge::Audio::Source::getGain() const {
	return this->_gain;
}

glm::vec3 &cge::Audio::Source::getPosition() const {
	return this->_position;
}

glm::vec3 &cge::Audio::Source::getVelocity() const {
	return this->_velocity;
}

bool cge::Audio::Source::isLooping() const {
	return this->_isLooping;
}

void cge::Audio::Source::setPlay(bool play) {
	if (this->_bufferID == 0) {
		std::cout << "No audio file is set\n";
		return;
	}

	if (play) {
		alSourcePlay(this->_sourceID);
	} else {
		alSourcePause(this->_sourceID);
	}
}

bool cge::Audio::Source::isPlaying() {
	ALint	state;

	alGetSourcei(this->_sourceID, AL_SOURCE_STATE, &state);

	return (state == AL_PLAYING);
}

unsigned cge::Audio::Source::getPlayOffset(cge::Audio::Source::Offset offsetType) {
	if (offsetType == cge::Audio::Source::Offset::MILLISECONDS) {
		ALfloat	seconds;

		alGetSourcef(this->_sourceID, static_cast<ALenum>(offsetType), &seconds);

		return static_cast<unsigned>(seconds * 1000.0);
	}

	ALint	offset;

	alGetSourcei(this->_sourceID, static_cast<ALenum>(offsetType), &offset);

	return static_cast<unsigned>(offset);
}
