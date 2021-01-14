#pragma once
#include "Window/Input.h"

namespace mtl {
	class Window64Input : public Input
	{
	protected:
		bool IsKeyPressed_Impl(int keycode) override;

		bool IsMouseButtonPressed_Impl(int button) override;
		std::pair<float, float> GetMousePosition_Impl() override;
		float GetMouseX_Impl() override;
		float GetMouseY_Impl() override;
	};
}

