#pragma once
#include <chrono>
#include "Time.h"

using namespace std::chrono;

namespace sdl{
	class Clock
	{
	public:
		Clock();
		sdl::Time getElapsedTime();
		sdl::Time restart();
	private:
		high_resolution_clock::time_point elapsedTimeSinceLastRestart;
	};
}
