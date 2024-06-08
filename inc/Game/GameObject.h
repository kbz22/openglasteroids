#pragma once

#include <OpenGLEngine/Shader.h>
#include <OpenGLEngine/Model.h>
#include <OpenGLEngine/Window.h>

#include <Game/CollisionBox2D.h>
#include <memory>

namespace Game {

	class GameObject {

	private:
		OpenGLEngine::Shader* m_shader;
		OpenGLEngine::Model* m_model;		
		float m_ambientStrength;
		float m_diffuseStrength = 0.8f;
		float m_specularStrength;
		float m_shiness;
		CollisionBox2D* m_collisionBox;

	protected:
		float m_speed;

	public:
		GameObject(std::string_view modelPath, std::string_view vertexShaderPath, std::string_view fragmentShaderPath);
		void SetPos(float x, float y, float z);
		void SetRot(float pitch, float yaw, float roll);
		void SetColor(float r, float g, float b);
		void SetSpeed(float speed);
		void Scale(float scale);
		void SetAmbient(float ambient);
		void SetSpecular(float speuclar);
		void SetShiness(float shiness);

		void EnableCollisionBox(float sideLength);
		void EnableCollisionCircle(float radius);
		bool CheckCollision(GameObject other);
		CollisionBox2D* GetCollisionBox();

		void Move(float deltaTime,
			float x, float y, float z,
			float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f);

		bool OutOfBounds();

		virtual void Update(float deltaTime);
		void Draw(OpenGLEngine::Window &window);
	};

}