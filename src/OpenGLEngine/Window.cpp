#include <OpenGLEngine/Window.h>

OpenGLEngine::Window::Window(std::string windowTitle, unsigned int windowWidth, unsigned int windowHeight, unsigned int viewportX, unsigned int viewportY, unsigned int viewportWidth, unsigned int viewportHeight)	
{
	m_screen.width = windowWidth;
	m_screen.height = windowHeight;

	m_viewport.x = viewportX;
	m_viewport.y = viewportY;
	m_viewport.width = viewportWidth;
	m_viewport.height = viewportHeight;

	m_mainCamera = std::make_unique<Camera>(Camera(glm::vec3(0.0f, 0.0f, 0.0f)));

	glfwInit();

	// Set OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// No backwards compatiblity for obsolete functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Disable window resizing
	glfwWindowHint(GLFW_RESIZABLE, false);

	m_window.reset(glfwCreateWindow(m_screen.width, m_screen.height, windowTitle.c_str(), NULL, NULL));

	if (m_window.get() == NULL) {
		throw std::runtime_error("Failed to create a window");
	}
	
	glfwMakeContextCurrent(m_window.get());	

	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Renderer: failed to initialize GLAD");
	}

	// blend options for sprites to work correctly
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(m_viewport.x, m_viewport.y, m_viewport.width, m_viewport.height);

	glEnable(GL_BLEND);
}

OpenGLEngine::Window::Window(std::string windowTitle, unsigned int windowSize[2], unsigned int viewport[4])
	: Window(windowTitle, windowSize[0], windowSize[1], viewport[0], viewport[1], viewport[2], viewport[3])
{}

OpenGLEngine::Window::~Window()
{
	glfwTerminate();
}

void OpenGLEngine::Window::BeginDraw(glm::vec3 clearColor)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLEngine::Window::EndDraw()
{
	glfwSwapBuffers(m_window.get());
}

void OpenGLEngine::Window::Update()
{	
	glfwPollEvents();	
}

void OpenGLEngine::Window::SetMainCameraPosition(float x, float y, float z)
{
	m_mainCamera->SetPos(x, y, z);
}

void OpenGLEngine::Window::SetMainCameraRotation(float pitch, float yaw, float roll)
{
	m_mainCamera->SetRot(pitch, yaw, roll);
}

GLFWwindow* OpenGLEngine::Window::GetGLFWwindow()
{
	return m_window.get();
}

OpenGLEngine::Camera* OpenGLEngine::Window::GetMainCamera()
{
	return m_mainCamera.get();
}

unsigned int OpenGLEngine::Window::GetScreenHeight()
{
	return m_screen.height;
}

unsigned int OpenGLEngine::Window::GetScreenWidth()
{
	return m_screen.width;
}

glm::mat4 OpenGLEngine::Window::GetViewMatrix()
{
	return m_mainCamera->GetViewMatrix();
}

glm::mat4 OpenGLEngine::Window::GetPerspectiveMatrix()
{
	return glm::perspective(glm::radians(m_mainCamera->GetFov()),
		static_cast<float>(m_screen.width) / static_cast<float>(m_screen.height),
		0.1f,
		100.0f);
}

glm::mat4 OpenGLEngine::Window::GetOrthoMatrix()
{
	return glm::ortho(0.0f,
		static_cast<float>(m_screen.width),
		static_cast<float>(m_screen.height),
		0.0f, 
		-1.0f,
		1.0f);
}

bool OpenGLEngine::Window::Closed()
{
	return !glfwWindowShouldClose(m_window.get());
}
