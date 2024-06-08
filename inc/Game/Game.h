#pragma once

#include <OpenGLEngine/Window.h>
#include <OpenGLEngine/Sprite.h>
#include <Game/Asteroid.h>
#include <Game/Spaceship.h>

#include <vector>
#include <array>

namespace Game {	

	enum gameState {
		stateGame,
		stateGoToPause,
		statePause,
		stateGoToGame,
		stateGameOver
	};

	class Game {

	private:
		OpenGLEngine::Window m_window;

		//GameObject m_spaceship;
		Spaceship m_spaceship;
		std::vector<Asteroid> m_asteroids;

		std::vector<OpenGLEngine::Sprite*> m_hearts;
		unsigned int m_heartsMax = 3;
		unsigned int m_heartsCnt = 3;

		OpenGLEngine::Sprite* m_pauseText;
		OpenGLEngine::Sprite* m_gameOverText;
		OpenGLEngine::Sprite* m_gameOverSubText;

		float m_lastFrameTime;
		float m_currentFrameTime;
		gameState m_gameState = stateGame;
				
		const float m_invincibilityTime = 2.0f;
		float m_invincibilityTimer = 0.0;

		float m_asteroidTimer = 0.0f;

		float m_loadingTimer = 1.0f;

		void input();

	public:
		Game();	
		bool Loop();
		void Restart();

	};


}