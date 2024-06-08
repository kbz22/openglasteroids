#include <Game/GameObject.h>

Game::GameObject::GameObject(std::string_view modelPath, std::string_view vertexShaderPath, std::string_view fragmentShaderPath)	
	:
	m_speed{ 0.0f },
	m_ambientStrength{ 0.8f },
	m_specularStrength{ 0.0f },
	m_collisionBox{nullptr}
{
	//! soo this works when they're pointers but doesnt when i create objects directly
	//! two game objects i create (asteroid and spaceship) merge - they both move when spaceship moves
	//! and have the same scale - so they have to send the same model matrix to shader
	//! but the models are different, so it's not the same model object
	m_shader = new OpenGLEngine::Shader(vertexShaderPath, fragmentShaderPath);
	m_model = new OpenGLEngine::Model(modelPath);
}

void Game::GameObject::SetPos(float x, float y, float z)
{
	m_model->SetPos(x,y,z);
}

void Game::GameObject::SetRot(float pitch, float yaw, float roll)
{
	m_model->SetRot(pitch, yaw, roll);
}

void Game::GameObject::SetColor(float r, float g, float b)
{
	m_model->SetColor(r, g, b);
}

void Game::GameObject::SetSpeed(float speed)
{
	m_speed = speed;
}

void Game::GameObject::Scale(float scale)
{
	m_model->Scale(scale);
}

void Game::GameObject::SetAmbient(float ambient)
{
	m_ambientStrength = ambient;
}

void Game::GameObject::SetSpecular(float speuclar)
{
	m_specularStrength = speuclar;
}

void Game::GameObject::SetShiness(float shiness)
{
	m_shiness = shiness;
}

void Game::GameObject::EnableCollisionBox(float sideLength)
{
	if (m_collisionBox == nullptr) {
		glm::vec3 pos = m_model->GetPos();
		m_collisionBox = new Game::CollisionBox2D(
			pos.x,
			pos.z,
			sideLength
		);
	}
}

bool Game::GameObject::CheckCollision(GameObject other)
{
	CollisionBox2D* cbptr = other.GetCollisionBox();
	if (m_collisionBox != nullptr || cbptr != nullptr) {
		return m_collisionBox->Collides(*other.GetCollisionBox());
	}
}

void Game::GameObject::EnableCollisionCircle(float radius)
{
	if (m_collisionBox == nullptr) {
		glm::vec3 pos = m_model->GetPos();
		m_collisionBox = new Game::CollisionBox2D(
			pos.x,
			pos.z,
			radius,
			CollisionBox2DType::Circle
		);
	}
}

Game::CollisionBox2D* Game::GameObject::GetCollisionBox()
{
	return m_collisionBox;
}

void Game::GameObject::Move(float deltaTime, float x, float y, float z, float pitch, float yaw, float roll)
{
	m_model->UnitMove(deltaTime * m_speed, x, y, z);
}

void Game::GameObject::Update(float deltaTime)
{
	if (m_collisionBox != nullptr) {
		glm::vec3 pos = m_model->GetPos();
		m_collisionBox->Set(pos.x, pos.z);
	}
}

void Game::GameObject::Draw(OpenGLEngine::Window& window)
{
	glm::mat4 perspective = window.GetPerspectiveMatrix();
	glm::mat4 view = window.GetViewMatrix();
	glm::mat4 model = m_model->GetMatrix();	

	m_shader->Use();

	m_shader->SetMat4("projection", perspective);
	m_shader->SetMat4("view", view);
	m_shader->SetMat4("model", model);
	m_shader->SetVec3("color", m_model->GetColor());
	
	m_shader->SetVec3("light.position", glm::vec3(-1.0f, 0.5f, 0.0f));
	m_shader->SetVec3("viewPos", glm::vec3(0.0, 2.0f, 0.0));

	m_shader->SetVec3("light.ambient", glm::vec3(m_ambientStrength, m_ambientStrength, m_ambientStrength));
	m_shader->SetVec3("light.diffuse", glm::vec3(m_diffuseStrength, m_diffuseStrength, m_diffuseStrength));
	m_shader->SetVec3("light.specular", glm::vec3(m_specularStrength, m_specularStrength, m_specularStrength));

	m_shader->SetFloat("material.shininess", m_shiness);
	
	m_model->Draw(*m_shader);
}

bool Game::GameObject::OutOfBounds()
{
	auto pos = m_model->GetPos();
	if(pos.x > 0.7f || pos.x < -0.8f || pos.z > 1.2f || pos.z < -1.2f)
		return true;
	return false;
}


