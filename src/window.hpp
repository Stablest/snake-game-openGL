#pragma once

#include <string>
#include <GLFW/glfw3.h>

namespace window {
	struct WindowData {
		int width;
		int height;
		std::string name;
	};

	GLFWwindow* initDefaultWindow(WindowData& windowData);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

}