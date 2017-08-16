#include <iostream>
#include "AudioSource.hpp"

cge::Audio::Source::Source()
{
	this->Init({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, false, 1.0f, 1.0f);
}

cge::Audio::Source::Source(
		const glm::vec3 &position,
		const glm::vec3 &velocity,
		bool isLooping,
		ALfloat pitch,
		ALfloat gain)
{
	this->Init(position, velocity, isLooping, pitch, gain);
}

cge::Audio::Source::Source(
		const std::string &audioPath,
		cge::Loader &loader)
{
	this->Init({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, false, 1.0f, 1.0f);
	this->setAudio(audioPath, loader);
}

cge::Audio::Source::Source(
		const glm::vec3 &position,
		const glm::vec3 &velocity,
		bool isLooping,
		const std::string &audioPath,
		cge::Loader &loader,
		ALfloat pitch,
		ALfloat gain)
{
	this->Init(position, velocity, isLooping, pitch, gain);
	this->setAudio(audioPath, loader);
}

cge::Audio::Source::~Source() {
	alDeleteSources(1, &this->_sourceID);
}

void cge::Audio::Source::Init(const glm::vec3 &position, const glm::vec3 &velocity, bool isLooping, ALfloat pitch, ALfloat gain) {
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

	alGenBuffers(1, &this->_bufferID);
	if (this->_bufferID == AL_INVALID_VALUE) {
		std::cerr << "Error creating buffer\n";
		exit(1);
	}

	alBufferData(
			this->_bufferID,
			(audioFile.info.channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
			audioFile.buffer,
			static_cast<ALsizei>(audioFile.info.channels * audioFile.info.frames * sizeof(uint16_t)),
			audioFile.info.samplerate
	);

	this->_sfInfo = audioFile.info;
	this->_audioPath = audioFilePath;

	std::smatch	matches;
	if (std::regex_match(audioFilePath, matches, std::regex(".*/(.*?)\\..*?$"))) {
		this->_name = matches[1];
	} else {
		this->_name = "Unknown Audio File";
	}

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

glm::vec3 cge::Audio::Source::getPosition() const {
	return this->_position;
}

glm::vec3 cge::Audio::Source::getVelocity() const {
	return this->_velocity;
}

bool cge::Audio::Source::isLooping() const {
	return this->_isLooping;
}

void cge::Audio::Source::setPlaying(bool play) {
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

void cge::Audio::Source::setPlayOffset(cge::Audio::Source::Offset offsetType, unsigned offset) {
	if (offsetType == cge::Audio::Source::Offset::MILLISECONDS) {
		alSourcef(this->_sourceID, static_cast<ALenum>(offsetType), offset / 1000.0f);
	} else {
		alSourcei(this->_sourceID, static_cast<ALenum>(offsetType), static_cast<ALint>(offset));
	}
}

unsigned cge::Audio::Source::getFileSize(cge::Audio::Source::Offset offsetType) const {
	switch (offsetType) {
		case cge::Audio::Source::Offset::MILLISECONDS:
			return static_cast<unsigned>(static_cast<double>(this->_sfInfo.frames) /
					static_cast<double>(this->_sfInfo.samplerate) * 1000.0);
		case cge::Audio::Source::Offset::SAMPLES:
			return static_cast<unsigned>(this->_sfInfo.frames);
//		case cge::Audio::Source::Offset::BYTES:
		default:
			return static_cast<unsigned>(this->_sfInfo.frames * this->_sfInfo.channels * sizeof(int16_t));
	}
}

std::string cge::Audio::Source::getName() const {
	return this->_name;
}

SF_INFO cge::Audio::Source::getInfo() const {
	return this->_sfInfo;
}
