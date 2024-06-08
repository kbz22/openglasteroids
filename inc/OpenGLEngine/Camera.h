#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <OpenGLEngine/UserPreferences.h>

namespace OpenGLEngine {

	enum CameraDirection {
		ecdForward = 0,
		ecdBackward,
		ecdLeft,
		ecdRight,
		ecdUp,
		ecdDown
	};

	const float defaultYaw = 0.0f;//-90.0f;
	const float defaultPitch = 0.0;//-180.0f;
	const float defaultMovementSpeed = 5e-1f;
	const float defaultSensitivity = 0.1f;
	const float defaultFOV = 45.0f;

	class Camera
	{
	private:
		glm::vec3 m_position;
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		float m_yaw;
		float m_pitch;
		float m_roll;

		float m_movementSpeed;
		float m_mouseSensitivity;
		float m_fov;

		void updateCameraVectors();		

	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = defaultYaw, float pitch = defaultPitch);
		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
		glm::mat4 GetViewMatrix();
				
		void Turn(float xoffset, float yoffset);
		void Zoom(float yoffset);

		void SetPos(float x, float y, float z);
		void SetRot(float yaw, float pitch, float roll = 0.0f);

		float GetFov() const;
		float GetYaw() const;
		float GetPitch() const;
		glm::vec3 GetFront() const;
		glm::vec3 GetPos() const;
		glm::vec3 GetUp() const;
	};

}