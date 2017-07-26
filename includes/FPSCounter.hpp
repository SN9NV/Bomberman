#ifndef FPSCOUNTER_HPP
#define FPSCOUNTER_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

class FPSCounter
{
	public:
		FPSCounter(unsigned numSamples = 100);
		~FPSCounter();

		double	fps(bool printFPS = false);
		double	frameTime(void) const;

	private:
		unsigned			_numSamples;
		unsigned			_currentFrame;
		std::vector<double>	_frameTimes;
		double				_previousTicks;
		double				_frameTime;
};

#endif // FPSCOUNTER_HPP
