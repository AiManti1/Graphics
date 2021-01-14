#pragma once
#include "Layer.h"

/*	Wrapper around a vector of layers.	*/
namespace mtl {

	class MTL LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;

		// `m_LayerInsert` is not supposed to point to `begin()`, but to the top of the layer stack
		// (or the bottom of the Overlay stack), so that new layers will always be added below overlays.
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}
