#pragma once

#include "Core/Common.h"

#include "Types/Containers.h"

#include "Engine/LayerSystem/LayerBase.h"

namespace asterisk {
	class ASTERISK_ENGINE_API LayerStack {
	private:
		Vector<Layer*> m_Layers;
		uint32_t m_InsertIndex = 0;

	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		constexpr auto begin()  { return m_Layers.begin();}
		constexpr auto rbegin() { return m_Layers.rbegin(); }

		constexpr auto cbegin()  const { return m_Layers.cbegin(); }
		constexpr auto crbegin() const { return m_Layers.crbegin(); }

		constexpr auto end()  { return m_Layers.end(); }
		constexpr auto rend() { return m_Layers.rend(); }

		constexpr auto cend()  const { return m_Layers.cend(); }
		constexpr auto crend() const { return m_Layers.crend(); }
	};
}