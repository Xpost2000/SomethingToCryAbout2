#pragma once
#include "dllDef.h"
#include <SDL2/SDL.h>
/*
	Enumeration for abstraction purposes
*/
enum class TimeMeasure{
	TIME_MILLISECONDS,
	TIME_SECONDS
};
/*
	ClockTimer for delta time
*/
class ClockTimer
{
public:
	ClockTimer();
	~ClockTimer();
	/*
		Ticks the timer and calculates the delta time.
		Call every frame.
	*/
	OATS_LIB_API static void Tick();
	/*
		return the calculated delta time in the format of your choosing
	*/
	OATS_LIB_API static float returnDeltatime(const TimeMeasure);
	/*
		return the total elasped time in the format of your choosing
	*/
	OATS_LIB_API static float returnElaspedTime(const TimeMeasure);
private:
	static uint32_t delta;
	static uint32_t last;
};

