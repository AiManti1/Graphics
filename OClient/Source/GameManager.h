#pragma once
#include "MTL.h"
#include "glm/glm.hpp"

namespace client {

	enum class GameState
	{
		GAME_PLAY,
		GAME_OVER,
		GAME_MENU,
		GAME_PAUSE,
		GAME_EXIT
	};

	class GameManager : public mtl::MEngine
	{
	public:
		GameManager();
		~GameManager();

		void processInput();

		void drawGame();

	private:
		void setState(GameState state);

		// Record the current game state to class State.
		GameState m_gameState;

		float m_time;
	};
}
