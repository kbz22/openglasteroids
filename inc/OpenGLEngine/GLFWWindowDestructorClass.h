#pragma once
#include <GLFW/glfw3.h>

namespace OpenGLEngine {

	class GLFWwindowDestructorClass {

	public:
		void operator()(GLFWwindow* ptr);

	};

}