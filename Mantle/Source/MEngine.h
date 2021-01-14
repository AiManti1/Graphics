#pragma once
#include "Macros.h"
#include "Window/WindowBase.h"
#include "Layers/LayerStack.h"
#include "Events/Event.h"
#include "Events/EngineEvent.h"

namespace mtl {

	class MTL MEngine
	{
	public:
		MEngine();
		//MEngine(GameManager* game);
		virtual ~MEngine();

		void Run();

		/**
		@brief	'MEngine' implements IEventListener interface by OnEvent() function.
				IEventListener*, goes through IEventListeners and call an event-function.
				F.e., it gets MouseButtonPressedEvent etc.then we call the function.		
		@type	bool
		*/
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline WindowBase& GetWindow() { return *WindowBase64; }

		inline static MEngine& Get() { return *s_Instance; }

	private:
		static MEngine* s_Instance;
		bool m_Running = true;
		std::unique_ptr<WindowBase> WindowBase64;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;		
	};

	// To be defined in Client-project.
	MEngine* StartClient();
}