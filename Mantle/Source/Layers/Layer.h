#pragma once
#include "Events/Event.h"

// In Log, engine will be the 1st to get the events. Then Client will get events through layers.

namespace mtl {

	class MTL Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		// For debugging mode.
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}
