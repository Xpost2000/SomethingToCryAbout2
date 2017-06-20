#include "ClockTimer.h"

 uint32_t ClockTimer::delta = 0;
 uint32_t ClockTimer::last = 0;

ClockTimer::ClockTimer()
{
	delete this;
}


ClockTimer::~ClockTimer()
{
}

/*
	This calculates the delta time.
	Call every frame possible.
*/
void ClockTimer::Tick(){
	uint32_t tickTime = SDL_GetTicks();
	delta = tickTime - last;
	last = tickTime;
}
/*
	return the value of delta time in either milliseconds or seconds
*/
float ClockTimer::returnDeltatime(const TimeMeasure m){
	switch (m){
	case TimeMeasure::TIME_MILLISECONDS:
		return static_cast<float>(delta);
		break;
	case TimeMeasure::TIME_SECONDS:
		return delta / 1000.0f;
		break;
	default:
		break;
	}
}
/*
	return the total amount of elasped time in either milliseconds or seconds
*/
float ClockTimer::returnElaspedTime(const TimeMeasure m){
	switch (m){
	case TimeMeasure::TIME_MILLISECONDS:
		return static_cast<float>(SDL_GetTicks());
		break;
	case TimeMeasure::TIME_SECONDS:
		return SDL_GetTicks() / 1000.0f;
		break;
	default:
			break;
	}
}

float ClockTimer::returnFramesPerSecond(){
	// WIP
	return 1;
}