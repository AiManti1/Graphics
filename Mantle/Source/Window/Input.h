#pragma once
#include "Macros.h"

/*	Global input manager ['Input polling'].	*/
namespace mtl {

	class MTL Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressed_Impl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressed_Impl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePosition_Impl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseX_Impl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseY_Impl(); }
	protected:
		// Gets dispatched to Window64Input class.
		virtual bool IsKeyPressed_Impl(int keycode) = 0;

		virtual bool IsMouseButtonPressed_Impl(int button) = 0;
		virtual std::pair<float, float> GetMousePosition_Impl() = 0;
		virtual float GetMouseX_Impl() = 0;
		virtual float GetMouseY_Impl() = 0;
	private:
		// Make it Singletone.
		static Input* s_Instance;
	};
}

