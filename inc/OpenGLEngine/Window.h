#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <OpenGLEngine/GLFWWindowDestructorClass.h>
#include <OpenGLEngine/Camera.h>

#include <memory>
#include <string>
#include <stdexcept>

namespace OpenGLEngine {

	constexpr unsigned int DefaultWindowWidth = 1280;
	constexpr unsigned int DefaultWindowHeight = 720;

	class Window
	{
	private:
		struct {
			unsigned int width;
			unsigned int height;
		} m_screen;
		struct {
			unsigned int x;
			unsigned int y;
			unsigned int width;
			unsigned int height;
		} m_viewport;
		std::unique_ptr<GLFWwindow, GLFWwindowDestructorClass> m_window;
		std::unique_ptr<Camera> m_mainCamera;

	public:
		Window(
			std::string windowTitle,
			unsigned int windowWidth = DefaultWindowWidth,
			unsigned int windowHeight = DefaultWindowHeight,
			unsigned int viewportX = 0,
			unsigned int viewportY = 0,
			unsigned int viewportWidth = DefaultWindowWidth, 
			unsigned int viewportHeight = DefaultWindowHeight
		);
		Window(
			std::string windowTitle,
			unsigned int windowSize[2],
			unsigned int viewport[4]
		);
		~Window();

		void BeginDraw(glm::vec3 clearColor = glm::vec3(0,0,0));		
		void EndDraw();
		void Update();
		void SetMainCameraPosition(float x, float y, float z);
		void SetMainCameraRotation(float pitch, float yaw, float roll = 0.0f);
		GLFWwindow* GetGLFWwindow();
		Camera* GetMainCamera();		
		unsigned int GetScreenHeight();
		unsigned int GetScreenWidth();

		glm::mat4 GetViewMatrix();
		glm::mat4 GetPerspectiveMatrix();
		glm::mat4 GetOrthoMatrix();

		bool Closed();

	};

}
