#include <Game/Asteroid.h>
#include <random>

float random(float maxval = 1.0f, float minval = 0.0f) {
	return minval + static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (maxval - minval);
}

Game::Asteroid::Asteroid()
	: 
	GameObject{ "./res/models/asteroid.obj",
			"./res/shaders/Lighting.vertex.glsl",
			"./res/shaders/Model.fragment.glsl" },
	m_horizontalPos{ random(0.99f, -0.99f) },
	m_pitchRot{ random(30.0f, -30.0f) },
	m_rollRot{ random(10.0f, -10.0f) },
	m_yawRot{random(30.0f, -30.0f)}
{
	Reset();
}

void Game::Asteroid::Update(float deltaTime)	
{
	Game::GameObject::Update(deltaTime);	
	Move(deltaTime,1.0f,0.0f, 0.0f, m_pitchRot, m_yawRot, m_rollRot);		
}

void Game::Asteroid::Start()
{
	SetSpeed(random(0.6f, 0.35f));
}

void Game::Asteroid::Reset()
{	
	float scale = random(0.35f, 0.2f);

	m_horizontalPos = random(0.99f, -0.99f);

	Scale(scale);
	SetPos(-0.799f, -0.01f, m_horizontalPos);	
	SetAmbient(0.8f);
	SetSpecular(0.0f);
	SetSpeed(0.0f);
	EnableCollisionCircle(scale);
}
