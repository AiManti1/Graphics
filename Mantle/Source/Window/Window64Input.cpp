#include "mtlpch.h"
#include "Window/Window64Input.h"
#include "MEngine.h"
#include "GLFW/glfw3.h"

namespace mtl {

	Input* Input::s_Instance = new Window64Input();

	bool Window64Input::IsKeyPressed_Impl(int keycode)
	{
		auto window64 = static_cast<GLFWwindow*>(MEngine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window64, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Window64Input::IsMouseButtonPressed_Impl(int button)
	{
		auto window64 = static_cast<GLFWwindow*>(MEngine::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window64, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Window64Input::GetMousePosition_Impl()
	{
		auto window64 = static_cast<GLFWwindow*>(MEngine::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window64, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	float Window64Input::GetMouseX_Impl()
	{
		/*
		auto window64 = static_cast<GLFWwindow*>(MEngine::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window64, &xPos, &yPos);
		return (float)xPos;
		*/
		// For C++17 (since we have already named these two floats x, y):
		auto[x, y] = GetMousePosition_Impl();
		return x;
	}

	float Window64Input::GetMouseY_Impl()
	{
		/*
		auto window64 = static_cast<GLFWwindow*>(MEngine::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window64, &xPos, &yPos);
		return (float)yPos;
		*/
		// For C++17 (since we have already named these two floats x, y):
		auto[x, y] = GetMousePosition_Impl();
		return y;
	}
}
