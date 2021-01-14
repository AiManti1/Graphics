#include "mtlpch.h"
#include "Window/Window64.h"
#include "Events/EngineEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/JoystickEvent.h"

namespace mtl {
	// It will return a pointer. And unique_ptr will be created in MEngine class.
	WindowBase* WindowBase::Create(const WindowBaseParams& params)
	{
		return new Window64(params);
	}

	Window64::Window64(const WindowBaseParams& params)
	{
		Init(params);
	}

	Window64::~Window64()
	{
		Quit();
	}

	void Window64::Init(const WindowBaseParams& params)
	{
		params64.Title = params.Title;
		params64.Width = params.Width;
		params64.Height = params.Height;
		params64.m_VSync = true;
		params64.m_IsFullScreen64 = false;

		LOG_MTL_INFO("Window parameters: {0} ({1}, {2})", params.Title, params.Width, params.Height);

		if (!glfwInit())
		{
			LOG_MTL_ERROR("GLFW failed.");
		}

		SetFullScreen(params64.m_IsFullScreen64);
		SetVSync(params64.m_VSync);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		LOG_MTL_INFO("OpenGL Version {0}.{1} loaded", GLVersion.major, GLVersion.minor);
		GLint majVers = 0, minVers = 0, profile = 0, flags = 0, num_ext = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &majVers);
		glGetIntegerv(GL_MINOR_VERSION, &minVers);
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile); // GL_CONTEXT_CORE_PROFILE_BIT or GL_CONTEXT_COMPATIBILITY_PROFILE_BIT.
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);		 // To check whether debug/forward-compatible/robust/... flags are set.
		glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext);
		LOG_MTL_INFO("OpenGL version: {0}.{1}, Profile: {2} (core), Flags: {3}, Extensions: {4}", majVers, minVers, profile, flags, num_ext);

		/* Set GLFW callbacks to then specify a function that is to be called when we press a key to resize. */
		// It gets the 'Window64Params' struct, from which all the data are fetched (params and functions).
		glfwSetWindowSizeCallback(m_Window64, [](GLFWwindow* window, int width, int height)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);
			prm64.Width = width;
			prm64.Height = height;
			
			WindowResizeEvent event(width, height);
			// Now dispatch this event to the MEngine class.
			prm64.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window64, [](GLFWwindow* window)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			prm64.EventCallback(event);
		});

		// Here we dispatch events to EventCallbackFn function.
		glfwSetKeyCallback(m_Window64, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				prm64.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				prm64.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				prm64.EventCallback(event);
				break;
			}
			}
		});

		// KeyTyped event.
		glfwSetCharCallback(m_Window64, [](GLFWwindow* window, unsigned int keycode)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			prm64.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window64, [](GLFWwindow* window, int button, int action, int mods)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				prm64.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				prm64.EventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window64, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			prm64.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window64, [](GLFWwindow* window, double xPos, double yPos)
		{
			Window64Params& prm64 = *(Window64Params*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			prm64.EventCallback(event);
		});

		glfwSetJoystickCallback([](int joystick, int action)
		{
			switch (action)
			{
			case GLFW_CONNECTED:
			{
				//TODO: fn.
				JoystickConnectedEvent event(joystick);
				//((Window64&) MEngine::Get().GetWindow()).SetEventCallback(event);
				break;
			}
			case GLFW_DISCONNECTED:
			{
				//TODO: fn.
				JoystickDisconnectedEvent event(joystick);
				//((Window64&) MEngine::Get().GetWindow()).SetEventCallback(event);
				break;
			}
			}
		});

		m_Cursors64[MTL_ARROW_CURSOR]		= glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		m_Cursors64[MTL_IBEAM_CURSOR]		= glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		m_Cursors64[MTL_CROSSHAIR_CURSOR]	= glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		m_Cursors64[MTL_HAND_CURSOR]		= glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		m_Cursors64[MTL_VRESIZE_CURSOR]		= glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		m_Cursors64[MTL_HRESIZE_CURSOR]		= glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	}

	void Window64::Quit()
	{
		for (GLFWcursor* cursor : m_Cursors64)
		{
			glfwDestroyCursor(cursor);
		}

		glfwDestroyWindow(m_Window64);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}

	void Window64::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window64);
	}

	void Window64::SetFullScreen(bool FullScreenEnabled)
	{
		m_Monitor64 = glfwGetPrimaryMonitor();
		m_Mode64 = glfwGetVideoMode(m_Monitor64);
		m_Window64 = glfwCreateWindow((int)params64.Width, (int)params64.Height, params64.Title.c_str(), nullptr, nullptr);

		if (FullScreenEnabled)
		{
			glfwWindowHint(GLFW_RED_BITS, m_Mode64->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, m_Mode64->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, m_Mode64->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, m_Mode64->refreshRate);
			// ALT+TAB will cause a fullscreen window to iconify.
			glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);				
			glfwSetWindowMonitor(m_Window64, m_Monitor64, 0, 0, m_Mode64->width, m_Mode64->height, m_Mode64->refreshRate);
			LOG_MTL_INFO("Fullscreen mode ON.");
		}

		else
		{
			glfwSetWindowPos(m_Window64, (m_Mode64->width - params64.Width) / 2, (m_Mode64->height - params64.Height) / 2);
			LOG_MTL_INFO("Window mode ON.");
		}

		glfwMakeContextCurrent(m_Window64);
		glfwSetWindowUserPointer(m_Window64, &params64);

		params64.m_IsFullScreen64 = FullScreenEnabled;
	}

	bool Window64::IsFullScreen() const
	{
		return params64.m_IsFullScreen64;
	}

	void Window64::SetVSync(bool VSyncEnabled)
	{
		if (VSyncEnabled)
		{
			glfwSwapInterval(1);
			LOG_MTL_INFO("VSync ON.");
		}

		else
		{
			glfwSwapInterval(0);
			LOG_MTL_INFO("VSync OFF.");
		}

		params64.m_VSync = VSyncEnabled;
	}

	bool Window64::IsVSync() const
	{
		return params64.m_VSync;
	}

	void Window64::SetCursorVisible(bool Visible)
	{
		if (Visible)
		{
			glfwSetInputMode(m_Window64, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else
		{
			glfwSetInputMode(m_Window64, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
	}

	void Window64::SetCursor(int Cursor)
	{
		glfwSetCursor(m_Window64, m_Cursors64[Cursor]);
	}

	double Window64::GetTime() const
	{
		return glfwGetTime();
	}

	const float* Window64::GetJoystickAxes(int Controller, int* Count) const
	{
		return glfwGetJoystickAxes(Controller, Count);
	}

	const unsigned char* Window64::GetJoystickButtons(int Controller, int* Count) const
	{
		return glfwGetJoystickButtons(Controller, Count);
	}
}