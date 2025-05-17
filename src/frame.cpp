#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "frame.hpp"

namespace engine {
	float engine::Frame::calculateDeltaTime() {
		currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		return deltaTime;
	}
};
