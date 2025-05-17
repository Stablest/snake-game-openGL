#include "snake.hpp"
#include "span"
#include "tiled_render.hpp"
#include "vector"

namespace game {

	game::Snake::Snake(SnakeParts parts, Vec2 dir) {
		this->parts = parts;
		this->dir = dir;
	}

	void game::Snake::process(GLFWwindow* window, float deltaTime) {
		processInput(window, deltaTime);
	}

	void game::Snake::processInput(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {

		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {

		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

		}
	}

	size_t game::Snake::getSize() {
		return parts.index;
	}

	SnakeParts game::Snake::getParts() {
		return parts;
	}

	std::span<engine::SimpleTile> game::Snake::extractUsedTiles() {
		std::span<engine::SimpleTile> const_view(parts.positions);
		return const_view.subspan(0, parts.index);
	}

}
