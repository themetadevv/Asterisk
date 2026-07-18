#pragma once

#include <string>
#include <chrono>

#include "Core/Common.h"

namespace asterisk {
	using Clock = std::chrono::high_resolution_clock;

	class ASTERISK_ENGINE_API ScopedTime {
	private:
		std::string m_Name;
		Clock::time_point m_Start;

	public:
		explicit ScopedTime(std::string name);
		~ScopedTime();

		void Reset();

		float GetElapsedSeconds();
		float GetElapsedMilliSeconds();
	};

	class ASTERISK_ENGINE_API TimeStep {
	private:
		Clock::time_point m_Start;
		Clock::time_point m_Last;

		float m_DeltaTime = 0.0f;

	public:
		TimeStep();

	public:
		float GetDeltaTime() const { return m_DeltaTime; }

		void Update();
	};
}

