#include "FPSCounter.hpp"

FPSCounter::FPSCounter(unsigned numSamples) :
	_numSamples(numSamples),
	_currentFrame(0),
	_previousTicks(SDL_GetTicks())
{
	this->_frameTimes.resize(this->_numSamples, 0.0);
}

FPSCounter::~FPSCounter()
{

}

double FPSCounter::fps(bool printFPS)
{
	double	currentTicks = SDL_GetTicks();

	this->_frameTime = currentTicks - this->_previousTicks;
	this->_previousTicks = currentTicks;

	this->_frameTimes[this->_currentFrame] = this->_frameTime;
	this->_currentFrame = (this->_currentFrame + 1) % this->_numSamples;

	double averageFrameTime = 0;

	for (auto frameTime : this->_frameTimes) {
		averageFrameTime += frameTime;
	}

	averageFrameTime /= this->_numSamples;

	double	fps = 0.0;

	if (averageFrameTime > 0.0) {
		fps = 1000 / averageFrameTime;
	}

	if (printFPS && this->_currentFrame == 0) {
		std::cout << fps << "\n";
	}

	return fps;
}

double FPSCounter::frameTime() const
{
	return this->_frameTime;
}
