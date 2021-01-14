#include "mtlpch.h"
#include "Layers/LayerStack.h"

namespace mtl {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	// All layers will be deleted on closing the application.
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	// To push at the 1st half of the list (before Overlay).
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	// To pushed at the 2st half of the list (Overlay zone).
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	// If poped out of the vector<Layers*> m_Layers, it is not deleted.
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}