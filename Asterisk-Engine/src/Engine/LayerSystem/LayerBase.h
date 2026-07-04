#pragma once

#include <string>

#include "Core/Common.h"

#include "Engine/EventSystem/EventBase.h"

namespace asterisk {
	class ASTERISK_ENGINE_API Layer {
	private:
		std::string m_LayerName;

	public:
		Layer(std::string name);
		virtual ~Layer() = default;

		const std::string& GetName() const { return m_LayerName; }

		virtual void OnAttach() {}

		virtual void OnEvent(Event& e)  {}
		virtual void OnUpdate(float dt) {}
		virtual void OnRender(float dt) {}

		virtual void OnDetach() {}
	};
}

