#pragma once
#include "Glad/glad.h"
#include <GLFW/glfw3.h>
#include "MEngine.h"
#include "Window/WindowBase.h"


namespace mtl {

	class Window64 : public WindowBase
	{
	public:
		Window64(const WindowBaseParams& params);
		virtual ~Window64();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return params64.Width; }
		inline unsigned int GetHeight() const override { return params64.Height; }

		// Window attributes.
		 /**
			*  @brief  This func. is called from the Engine to request the window to call the events back to Engine and then to layers.
			*  @param  callback of EventCallbackFn& type.
			*  @return callback.
		*/
		inline void SetEventCallback(const EventCallbackFn& callback) override { params64.EventCallback = callback; }

		double GetTime() const override;

		void SetVSync(bool VSyncEnabled) override;
		bool IsVSync() const override;

		void SetFullScreen(bool FullScreenEnabled) override;
		bool IsFullScreen() const;

		void SetCursorVisible(bool Visible) override;
		void SetCursor(int Cursor) override;

		inline virtual void* GetNativeWindow() const { return m_Window64; }

		const float* GetJoystickAxes(int Joystick, int* Count) const override;
		const unsigned char* GetJoystickButtons(int Joystick, int* Count) const override;

	private:
		virtual void Init(const WindowBaseParams& params);
		virtual void Quit();

		GLFWmonitor* m_Monitor64;
		const GLFWvidmode* m_Mode64;
		GLFWwindow* m_Window64;
		GLFWcursor* m_Cursors64[MTL_CURSOR_LAST + 1];

		// We'll pass this struct to GLFW, not the whole class.
		struct Window64Params
		{
			unsigned int Width, Height;
			std::string Title;
			bool m_VSync;
			bool m_IsFullScreen64;
			EventCallbackFn EventCallback; // for dispatching back to MEngine
		} params64;

		// Constructors and assignments.
		 /**
			*  @brief  The copy operator is deleted, i.e. a Window can not be copied.
			*  @param  The Window to copy.
			*  @return A reference to this Window.
		 */
		 //WindowBase(const WindowBase& other) = delete;

		 /**
			 *  @brief  The move constructor is deleted, i.e. a Window can not be moved.
			 *  @param  The Window to move.
		 */
		 //WindowBase(WindowBase&& other) = delete;

		 /**
			*  @brief  The copy operator is deleted, i.e. a Window can not be copied.
			*  @param  The Window to copy.
			*  @return A reference to this Window.
		*/
		//WindowBase& operator=(const WindowBase& other) = delete;

		 /**
			*  @brief  The move operator is deleted, i.e. a Window can not be moved.
			*  @param  The Window to move.
			*  @return A reference to this Window.
		*/
		//template <typename T>
		 //WindowBase& operator=(const T&& other) = delete;
	};
}
