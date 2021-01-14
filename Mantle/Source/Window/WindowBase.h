#pragma once
#include "mtlpch.h"
#include "Macros.h"
#include "Events/Event.h"

/*	This is the platform-independent base Window interface class for desktop.	*/

#define MTL_ARROW_CURSOR             0x0
#define MTL_IBEAM_CURSOR             0x1
#define MTL_CROSSHAIR_CURSOR         0x2
#define MTL_HAND_CURSOR              0x3
#define MTL_HRESIZE_CURSOR           0x4
#define MTL_VRESIZE_CURSOR           0x5
#define MTL_CURSOR_LAST              MTL_VRESIZE_CURSOR

namespace mtl {

	struct WindowBaseParams
	{
		/*
		std::string Title = "Mantle Engine";
		unsigned int Width = 800;
		unsigned int Height = 600;
		*/

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowBaseParams(const std::string& Title = "Mantle Engine",
			unsigned int Width = 800,
			unsigned int Height = 600)
			: Title(Title), Width(Width), Height(Height)
		{
		}
	};

	class MTL WindowBase
	{
	public:
		virtual ~WindowBase() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual double GetTime() const = 0;

		virtual const float* GetJoystickAxes(int Joystick, int* Count) const = 0;
		virtual const unsigned char* GetJoystickButtons(int Joystick, int* Count) const = 0;

		// Window attributes.
		using EventCallbackFn = std::function<void(Event&)>;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0; // for setting a callback function on the window
		virtual void SetVSync(bool VSyncEnabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void SetFullScreen(bool FullScreenEnabled) = 0;
		virtual bool IsFullScreen() const = 0;
		virtual void SetCursorVisible(bool Visible) = 0;
		virtual void SetCursor(int Cursor) = 0;
		//virtual unsigned int AspectRatio() const = 0;

		/**
			@brief Used in Window64Input class.
			@type void*, i.e. may be returning another type of window.
			@return A GLFW-window.
		*/
		virtual void* GetNativeWindow() const = 0;

		/**
		   @brief  To be implemented per platform.
		   @param  The Window parameters from struct WindowBaseParams:
					   * std::string Title;
					   * unsigned int Width;
					   * unsigned int Height.
		   @return A type of Window, like "Windows window", "macOS window" etc.
	   */
		static WindowBase* Create(const WindowBaseParams& params = WindowBaseParams());

		// TODO: Entity-Game component system
		// const std::vector<GameComponent*>& Components() const;
	};
}
