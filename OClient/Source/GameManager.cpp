#include "GameManager.h"

namespace client {

	// In Log, engine will be the 1st to get the events. Then the Client app will get events through layers.
	
	class ExampleLayer : public mtl::Layer
	{
	public:
		ExampleLayer()
			: Layer("Game Example")
		{
		}

		void OnUpdate() override
		{
			//LOG_APP_INFO("Game ExampleLayer::OnUpdate");

			//Polling.
			if (mtl::Input::IsKeyPressed(MTL_KEY_TAB))
				LOG_APP_TRACE("Tab key is pressed (poll).");
		}

		void OnEvent(mtl::Event& event) override
		{
			LOG_APP_TRACE("Game OnEvent events {0}", event);

			if (event.GetEventType() == mtl::EventType::KeyPressed)
			{
				mtl::KeyPressedEvent& e = (mtl::KeyPressedEvent&)event;
				if (e.GetKeyCode() == MTL_KEY_TAB)
				LOG_APP_TRACE("Tab key is pressed (event).");
				LOG_APP_TRACE("{0}", (char)e.GetKeyCode());
			}
		}
	};

	GameManager::GameManager()
	{
		m_gameState = GameState::GAME_PLAY;

		LOG_MTL_INFO("Client application launched.");
		PushLayer(new ExampleLayer());
		PushOverlay(new mtl::ImGuiLayer());
	}

	GameManager::~GameManager()
	{
	}
}

mtl::MEngine* mtl::StartClient()
{
	return new client::GameManager();
}
