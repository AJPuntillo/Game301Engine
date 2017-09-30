//Andrew Puntillo
//---
//Timer Class:
//Queries the time running on the machine, when the machine started up, and how fast it ticks.
//Can only be initialized as a Singleton.
//---

#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

namespace ENGINE
{

	class Timer
	{
	public:
		~Timer();

		static void init();

		static inline double ticksToSeconds(LARGE_INTEGER ticks)
		{
			return (((double)ticks.QuadPart) / ((double)m_ticksPerSecond.QuadPart));
		}

		static inline LARGE_INTEGER secondsToTicks(double secs)
		{
			LARGE_INTEGER result;
			result.QuadPart = (LONGLONG)(secs * ((double)m_ticksPerSecond.QuadPart));
			return result;
		}

		static inline LARGE_INTEGER getCurrentTicks()
		{
			LARGE_INTEGER result;
			result.QuadPart = getHardwareCounterValue().QuadPart;
			return result;
		}

		static inline LARGE_INTEGER getResolution()
		{
			return m_ticksPerSecond;
		}

		static inline double getCurrentTime()
		{
			return ticksToSeconds(getCurrentTicks());
		}

		static inline bool isReady()
		{
			return m_highResolutionSupported;
		}

	private:
		Timer();

		static LARGE_INTEGER m_counter;
		static LARGE_INTEGER m_ticksPerSecond;
		static bool m_highResolutionSupported;

		static inline LARGE_INTEGER getHardwareCounterValue()
		{
			LARGE_INTEGER value;
			QueryPerformanceCounter(&value);
			return value;
		}

	};

}

#endif