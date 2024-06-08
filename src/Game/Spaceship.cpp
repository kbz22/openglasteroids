#include <Game/Spaceship.h>

Game::Spaceship::Spaceship()
	: GameObject{ "./res/models/spaceship.obj", "./res/shaders/Lighting.vertex.glsl", "./res/shaders/Model.fragment.glsl" }
{
	float scale = 0.2f;
	Scale(scale);
	SetPos(0.0f, 0.0f, 0.0f);
	SetSpeed(0.5f);
	SetAmbient(0.8f);
	SetSpecular(1.0f);
	SetShiness(8.0f);
	EnableCollisionBox(scale);
}
