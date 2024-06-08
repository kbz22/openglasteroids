#include <OpenGLEngine/Camera.h>
#include <stdexcept>
#include <cmath>

void OpenGLEngine::Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);
	
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

OpenGLEngine::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(defaultMovementSpeed), m_mouseSensitivity(defaultSensitivity), m_fov(defaultFOV)
{
	m_position = position;
	m_worldUp = up;
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}

OpenGLEngine::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(defaultMovementSpeed), m_mouseSensitivity(defaultSensitivity), m_fov(defaultFOV)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(upX, upY, upZ);
	m_yaw = yaw;
	m_pitch = pitch;
	updateCameraVectors();
}

glm::mat4 OpenGLEngine::Camera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void OpenGLEngine::Camera::SetPos(float x, float y, float z) {

	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	updateCameraVectors();
}

void OpenGLEngine::Camera::SetRot(float yaw, float pitch, float roll)
{
	m_yaw = yaw;
	m_pitch = pitch;
	m_roll = roll;

	updateCameraVectors();
}

void OpenGLEngine::Camera::Turn(float xoffset, float yoffset)
{
	xoffset *= m_mouseSensitivity;
	yoffset *= m_mouseSensitivity;

	m_yaw += xoffset;
	m_pitch = m_pitch + yoffset > 89.0f ? 89.0f :
		m_pitch + yoffset < -89.0f ? -89.0f : m_pitch + yoffset;

	updateCameraVectors();
}

void OpenGLEngine::Camera::Zoom(float yoffset)
{
	m_fov -= (float)yoffset;
	if (m_fov < 1.0f)
		m_fov = 1.0f;
	if (m_fov > 45.0f)
		m_fov = 45.0f;
}

float OpenGLEngine::Camera::GetFov() const
{
	return m_fov;
}

float OpenGLEngine::Camera::GetYaw() const
{
	return m_yaw;
}

float OpenGLEngine::Camera::GetPitch() const
{
	return m_pitch;
}

glm::vec3 OpenGLEngine::Camera::GetFront() const
{
	return m_front;
}

glm::vec3 OpenGLEngine::Camera::GetUp() const
{
	return m_up;
}

glm::vec3 OpenGLEngine::Camera::GetPos() const
{
	return m_position;
}

