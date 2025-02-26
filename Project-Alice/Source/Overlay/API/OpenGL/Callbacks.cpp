#include "Callbacks.h"

void Callbacks::Framebuffersize_Callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
