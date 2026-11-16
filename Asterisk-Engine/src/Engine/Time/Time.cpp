
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Engine/Time/Time.h"

namespace asterisk {
	
	ScopedTime::ScopedTime(std::string name) : 
		m_Name(std::move(name))
	{
		Reset();
	}

	ScopedTime::~ScopedTime() {
		
	}

	void ScopedTime::Reset() {
		m_Start = Clock::now();
	}

	float ScopedTime::GetElapsedSeconds() {
		auto current = Clock::now();
		float es = std::chrono::duration<float>(current - m_Start).count();
		return es;
	}

	float ScopedTime::GetElapsedMilliSeconds() {
		return GetElapsedSeconds() * 1000.0f;
	}

	// time step

	TimeStep::TimeStep() :
		m_Start(Clock::now()),
		m_Last(m_Start)
	{

	}

	void TimeStep::Update() {
		auto current = Clock::now();
		m_DeltaTime = std::chrono::duration<float>(current - m_Last).count();
		m_Last = current;
	}
}
