#include <Overlay/Overlay.h>

namespace Alice::Overlay
{
	OpenGL::OpenGL(const char* title, int width, int height) : Context(nullptr), Title(title), Width(width), Height(height) {}
	OpenGL::~OpenGL() { glfwTerminate(); }

	void OpenGL::Initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); 
		glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); 
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); 
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); 
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}

	int OpenGL::CreateContext()
	{
		this->Context = glfwCreateWindow(this->Width, this->Height, this->Title, NULL, NULL);
		if (this->Context == nullptr)
		{
			std::cout << "Failed to create context\n";
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(this->Context);

		if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
		{
			printf("GLAD : Failed to Load Open GL Loader\n");
			glfwTerminate();
			return -1;
		}

		glViewport(0, 0, this->Width, this->Height);
		glfwSetFramebufferSizeCallback(this->Context, Callbacks::Framebuffersize_Callback);

		return 0;
	}

	void OpenGL::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	VOID OpenGL::ClearColors()
	{
		glClearColor(40.0f / 255.0f, 40.0f / 255.0f, 40.0f / 255.0f, 1.0f);
	}

	void OpenGL::SwapAndPoll()
	{
		glfwSwapBuffers(this->Context);
		glfwPollEvents();
	}

	void OpenGL::Shutdown()
	{
		glfwSetWindowShouldClose(this->Context, true);
	}

	float OpenGL::GetElapsedTime()
	{
		elapsed_time = glfwGetTime();
		return elapsed_time;
	}
}