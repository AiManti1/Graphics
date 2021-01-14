#include "mtlpch.h"
#include "MEngine.h"
#include "imgui.h"
#include "ImGuiLayer.h"
#include "OpenGL/ImGuiRenderer.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace mtl {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TODO: should be key codes from 'KeyCodes.h'.
		io.KeyMap[ImGuiKey_Tab]			= GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow]	= GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow]	= GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow]		= GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow]	= GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp]		= GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown]	= GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home]		= GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End]			= GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert]		= GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete]		= GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace]	= GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space]		= GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter]		= GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape]		= GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A]			= GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C]			= GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V]			= GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X]			= GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y]			= GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z]			 = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 430");					
	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		MEngine& engine = MEngine::Get(); // from being the singleton class
		io.DisplaySize = ImVec2(engine.GetWindow().GetWidth(), engine.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f); // seconds since last frame
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	// When an event comes in to the layer, we check its type and then
	// forward this event to one of the functions below (OnMouseButtonPressedEvent() etc.)
// (std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::1)) -> &fn
#define MTL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		// If 'event' of dispatcher matches MouseButtonPressedEvent type (dispatcher checks for this),
		// then it will call (be propagated to) the specified function:
		// Binding because it is of ImGui layer.
		dispatcher.Dispatch<MouseButtonPressedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(MTL_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		// false means we haven't handled this. And want other layer to handle this.
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();	// horisontal
		io.MouseWheel += e.GetYOffset();	// vertical
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		// For modifying keys.
		// TODO: should be replaced with the Engine's key codes.
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	// Char callback (used for typing in a text box).
	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		// TODO: Temporary! Remove.
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}

}