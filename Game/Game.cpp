#include <Game/Game.h>

#include <GLFW/glfw3.h>

void Game::Game::input()
{
	GLFWwindow* window = m_window.GetGLFWwindow();
	float deltaTime = m_currentFrameTime - m_lastFrameTime;

	switch (m_gameState) {

	case stateGame:

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			m_spaceship.Move(deltaTime, -1.0f, 0.0f, 0.0f);
			if(m_spaceship.OutOfBounds())
				m_spaceship.Move(deltaTime, 1.0f, 0.0f, 0.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			m_spaceship.Move(deltaTime, 1.0f, 0.0f, 0.0f);
			if (m_spaceship.OutOfBounds())
				m_spaceship.Move(deltaTime, -1.0f, 0.0f, 0.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			m_spaceship.Move(deltaTime, 0.0f, 0.0f, 1.0f);
			m_spaceship.SetRot(0.0f, 0.0f, 15.0f);
			if (m_spaceship.OutOfBounds())
				m_spaceship.Move(deltaTime, 0.0f, 0.0f, -1.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			m_spaceship.Move(deltaTime, 0.0f, 0.0f, -1.0f);
			m_spaceship.SetRot(0.0f, 0.0f, -15.0f);
			if (m_spaceship.OutOfBounds())
				m_spaceship.Move(deltaTime, 0.0f, 0.0f, 1.0f);
		}

		if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE &&
			glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) ||
			(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS &&
				glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)) {
			m_spaceship.SetRot(0.0f, 0.0f, 0.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			m_gameState = stateGoToPause;
		}

		break;

	case stateGoToPause:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			m_gameState = statePause;
		}

		break;

	case statePause:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			m_gameState = stateGoToGame;
		}

		break;

	case stateGoToGame:
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			m_gameState = stateGame;
		}

		break;

	case stateGameOver:
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			Restart();			
		}
		break;
	}
}

Game::Game::Game()
	: 
	m_window{ "Asteroids Game" },
	m_asteroids{},	
	m_spaceship{},
	m_lastFrameTime{ 0.0f },
	m_currentFrameTime{0.0f}
{	
	m_window.SetMainCameraPosition(0.0, 2.0, 0.0);
	m_window.SetMainCameraRotation(0.0, -90.0);

	for (int i = 0; i < 10; i++) {
		m_asteroids.push_back(Asteroid());
		if (i < 6) m_asteroids[i].Start();
	}
	
	for (int i = 0; i < m_heartsMax; i++) {
		float scale = 50.0f;
		float offset = m_window.GetScreenWidth() / 2 - 3.0f * scale;
		m_hearts.push_back(
			new OpenGLEngine::Sprite(
				*(new OpenGLEngine::Texture("./res/textures/heart.png")),
				glm::vec2(offset + i * scale,-scale/2),
				*(new OpenGLEngine::Shader("./res/shaders/Interface.vertex.glsl", "./res/shaders/Interface.fragment.glsl")),
				glm::vec2(scale)
		));
	}

	m_pauseText = new OpenGLEngine::Sprite(
		*(new OpenGLEngine::Texture("./res/textures/pause.png")),
		glm::vec2(120.0f,0.0f),
		*(new OpenGLEngine::Shader("./res/shaders/Interface.vertex.glsl", "./res/shaders/Interface.fragment.glsl")),
		glm::vec2(220.0f,80.0f)
	);
	m_gameOverText = new OpenGLEngine::Sprite(
		*(new OpenGLEngine::Texture("./res/textures/gameover.png")),
		glm::vec2(-360.0f, -100.0f),
		*(new OpenGLEngine::Shader("./res/shaders/Interface.vertex.glsl", "./res/shaders/Interface.fragment.glsl")),
		glm::vec2(400.0f, 150.0f)
	);
	m_gameOverSubText = new OpenGLEngine::Sprite(
		*(new OpenGLEngine::Texture("./res/textures/presstorestart.png")),
		glm::vec2(-100.0f, 300.0f),
		*(new OpenGLEngine::Shader("./res/shaders/Interface.vertex.glsl", "./res/shaders/Interface.fragment.glsl")),
		glm::vec2(300.0f, 40.0f)
	);
}

bool Game::Game::Loop()
{
	m_lastFrameTime = m_currentFrameTime;
	m_currentFrameTime = static_cast<float>(glfwGetTime());
	float dt = m_currentFrameTime - m_lastFrameTime;	

	if (m_loadingTimer > 0.0f) {
		m_loadingTimer -= dt;
		return true;
	}

	m_window.BeginDraw();	
	
	switch (m_gameState) {

	case stateGame:
		if (m_invincibilityTimer > 0.0f) m_invincibilityTimer -= dt;
		else m_invincibilityTimer == 0.0f;

		m_asteroidTimer += dt;

		for (auto& asteroid : m_asteroids) {
			if (asteroid.OutOfBounds() && m_asteroidTimer > 2.0f) {
				m_asteroidTimer == 0.0f;
				asteroid.Reset();
				asteroid.Start();
				continue;
			}
			asteroid.Update(dt);
			if (m_invincibilityTimer <= 0.0f && asteroid.CheckCollision(m_spaceship)) {
				asteroid.SetPos(1.0f, 0.0f, 0.0f);
				m_heartsCnt--;
				m_invincibilityTimer = m_invincibilityTime;
			}
			asteroid.Draw(m_window);
		}

		m_spaceship.Update(dt);
		if (static_cast<int>(m_invincibilityTimer*8.0f) % 2 == 1)
			m_spaceship.SetColor(1.0f, 0.0f, 0.0f);			
		else
			m_spaceship.SetColor(1.0f, 1.0f, 1.0f);
		m_spaceship.Draw(m_window);

		for (int i = 0; i < m_heartsMax; i++) {
			if (i + 1 > m_heartsCnt)
				m_hearts[i]->SetColor(glm::vec3(0.2f, 0.2f, 0.2f));
			else
				m_hearts[i]->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
			m_hearts[i]->Draw(m_window);
		}

		break;

	case stateGoToPause:
	case statePause:
		m_spaceship.SetColor(0.1, 0.1, 0.1);
		m_spaceship.Draw(m_window);
		for (auto& asteroid : m_asteroids) {
			asteroid.SetColor(0.2, 0.2, 0.2);
			asteroid.Draw(m_window);
		}
		m_pauseText->Draw(m_window);
		break;

	case stateGoToGame:
		m_spaceship.SetColor(1, 1, 1);
		for (auto& asteroid : m_asteroids)
			asteroid.SetColor(1, 1, 1);
		break;

	case stateGameOver:
		m_gameOverText->Draw(m_window);
		m_gameOverSubText->Draw(m_window);
		break;

	}		

	if (m_heartsCnt == 0) {
		m_gameState = stateGameOver;
	}

	m_window.Update();
	input();

	m_window.EndDraw();

	return m_window.Closed();
	
}

void Game::Game::Restart()
{
	m_heartsCnt = m_heartsMax;
	m_invincibilityTimer = 0.0;
	m_asteroidTimer = 0.0f;
	m_gameState = stateGame;

	m_spaceship.SetPos(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < m_asteroids.size(); i++) {
		m_asteroids[i].Reset();
		if (i < 6) m_asteroids[i].Start();
	}
}
