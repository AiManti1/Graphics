#include "mtlpch.h"
#include "MEngine.h"
#include "Log.h"
#include "Window/Input.h"
#include "Glad/glad.h"


#define BIND_EVENT_FN(x) std::bind(&MEngine::x, this, std::placeholders::_1)

namespace mtl {

	MEngine* MEngine::s_Instance = nullptr;

	MEngine::MEngine()
	{
		s_Instance = this;

		// Because it is an explicit constructor, unique_ptr is used.
		WindowBase64 = std::unique_ptr<WindowBase>(WindowBase::Create());

		// Set a callback function on the window.
		// Event callback goes to Window64 -> params64 -> EventCallbackFn.
		// WindowBase64->SetEventCallback(std::bind(&MEngine::OnEvent, this, std::placeholders::_1));	
		WindowBase64->SetEventCallback(BIND_EVENT_FN(OnEvent));		
	}

	MEngine::~MEngine()
	{
	}
	
	void MEngine::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		// For ImGui.
		layer->OnAttach();
	}

	void MEngine::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		// For ImGui.
		layer->OnAttach();
	}
	
	void MEngine::OnEvent(Event& e)
	{
		LOG_MTL_INFO("{0}", e);

		EventDispatcher dispatcher(e);
		// Template T:: -> dispatcher. T is WindowCloseEvent here.
		// if 'Dispatch' sees WindowCloseEvent under param. 'e', it'll dispatch it to 'OnWindowClose', binding this function.
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// To go backwards for layers.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}
	
	void MEngine::Run()
	{	
		while (m_Running)
		{
			const float CornflowerBlue[] = { 0.392f, 0.584f, 0.929f, 1.0f };
			glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(); // goes from the beginnning to the end, including overlays
			
			auto[x, y] = Input::GetMousePosition();
			LOG_MTL_TRACE("{0}, {1}", x, y);

			WindowBase64->OnUpdate();
		}
	}
	
	bool MEngine::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		
		//m_Handled = true;
		return true;
	}
}
