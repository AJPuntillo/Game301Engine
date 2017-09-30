#include "Timer.h"

using namespace ENGINE;

LARGE_INTEGER Timer::m_counter;
LARGE_INTEGER Timer::m_ticksPerSecond;
bool Timer::m_highResolutionSupported = false;

Timer::Timer()
{
	//Empty
}

Timer::~Timer()
{
	//Empty
}


void Timer::init()
{
	m_highResolutionSupported = QueryPerformanceFrequency(&m_ticksPerSecond);
	m_counter = getHardwareCounterValue();
}