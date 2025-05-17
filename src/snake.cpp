#include "snake.hpp"
#include "span"
#include "tiled_render.hpp"
#include "vector"

namespace game {

	game::Snake::Snake(SnakeParts parts, Vec2 dir, Vec2 mapLimit) : parts(parts), dir(dir), mapLimit(mapLimit) {
	}

	void game::Snake::process(GLFWwindow* window, float deltaTime) {
		processInput(window, deltaTime);
		move();
	}

	void game::Snake::move() {
		std::vector<engine::SimpleTile>& localTiles = parts.tiles;
		if (localTiles.size() == 0) {
			return; // throw error
		}
		for (size_t i = 0; i < localTiles.size(); ++i) {
			if (i + 1 < localTiles.size()) {
				localTiles[i].position = localTiles[i + 1].position;
			}
			else {
				localTiles[i].position = Vec2{ localTiles[i].position.x + dir.x, localTiles[i].position.y + dir.y };
			}
		}
	}

	void game::Snake::normalizeMapDirection() {
		//if (dir.x < 0) {
		//	dir.x = mapLimit.x - 1;
		//}
		//else {
		//	if (dir.x > (mapLimit.x - 1)) {
		//		dir.x = 0;
		//	}
		//}
		//if (dir.y < 0) {
		//	dir.y = mapLimit.y - 1;
		//}
		//else {
		//	if (dir.y > (mapLimit.y - 1)) {
		//		dir.y = 0;
		//	}
		//}
	}

	void game::Snake::processInput(GLFWwindow* window, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			dir = Vec2::UP();
			return;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			dir = Vec2::DOWN();
			return;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			dir = Vec2::LEFT();
			return;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			dir = Vec2::RIGHT();
			return;
		}
	}

	size_t game::Snake::getSize() {
		return parts.index;
	}

	SnakeParts game::Snake::getParts() {
		return parts;
	}

	std::span<engine::SimpleTile> game::Snake::extractUsedTiles() {
		std::span<engine::SimpleTile> const_view(parts.tiles);
		return const_view.subspan(0, parts.index);
	}

}
