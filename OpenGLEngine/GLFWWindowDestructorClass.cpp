#include <OpenGLEngine/GLFWWindowDestructorClass.h>

void OpenGLEngine::GLFWwindowDestructorClass::operator()(GLFWwindow* ptr) {
	glfwDestroyWindow(ptr);
}
