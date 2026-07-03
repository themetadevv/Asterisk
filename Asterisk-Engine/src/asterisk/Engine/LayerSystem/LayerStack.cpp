
#include "astpch.h"

#include "asterisk/Logger/Logger.h"

#include "asterisk/Engine/LayerSystem/LayerStack.h"

namespace asterisk {

	LayerStack::LayerStack() {

	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(begin() + m_InsertIndex, layer);
		++m_InsertIndex;
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(begin(), end() + m_InsertIndex, layer);
		if (it == end() + m_InsertIndex)
			return;
		
		layer->OnDetach();
		m_Layers.erase(it);
		m_InsertIndex--;
	}

	void LayerStack::PushOverlay(Layer* layer) {
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopOverlay(Layer* layer) {
		auto it = std::find(begin(), m_InsertIndex + end(), layer);
		if (it == m_InsertIndex + end())
			return;

		layer->OnDetach();
		m_Layers.erase(it);
		m_InsertIndex--;
	}
}
