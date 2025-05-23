#include "snake.hpp"
#include "span"
#include "tiled_render.hpp"
#include "vector"

namespace game {

	game::Snake::Snake(std::vector<engine::SimpleTile> parts, Vec2 dir, Vec2 mapLimit) : parts(parts), eatenTiles(std::queue<engine::SimpleTile>()), dir(dir), mapLimit(mapLimit), isEatenTileBuffered(false) {
	}

	void game::Snake::process(GLFWwindow* window, float deltaTime) {
		integrateEatenTile();
		move();
	}

	void game::Snake::integrateEatenTile() {
		if (eatenTiles.size() == 0) {
			return;
		}
		if (isEatenTileBuffered) {
			parts.insert(parts.begin(), eatenTiles.front());
			eatenTiles.pop();
		}
		if (eatenTiles.size() == 0) {
			return;
		}
		if (eatenTiles.front().position == getTail().position) {
			isEatenTileBuffered = true;
		}
	}

	void game::Snake::move() {
		if (parts.size() == 0) {
			return;
		}
		for (size_t i = 0; i < parts.size(); ++i) {
			if (i + 1 < parts.size()) {
				parts[i].position = parts[i + 1].position;
			}
			else {
				Vec2 nextPos = Vec2{ parts[i].position.x + dir.x, parts[i].position.y + dir.y };
				parts[i].position = normalizeHeadNextPos(nextPos);
			}
		}
	}

	Vec2 game::Snake::normalizeHeadNextPos(Vec2& nextPos) const {
		if (nextPos.x < 0) {
			nextPos.x = mapLimit.x - 1;
		}
		else {
			if (nextPos.x > (mapLimit.x - 1)) {
				nextPos.x = 0;
			}
		}
		if (nextPos.y < 0) {
			nextPos.y = mapLimit.y - 1;
		}
		else {
			if (nextPos.y > (mapLimit.y - 1)) {
				nextPos.y = 0;
			}
		}
		return nextPos;
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

	void game::Snake::on_collision(Vec2 colPos) {
		eatenTiles.push(engine::SimpleTile{ colPos, Vec3f{0, 0, 0}, 0 });
	}

	engine::SimpleTile game::Snake::getHead() {
		return parts.front();
	}

	engine::SimpleTile game::Snake::getTail() {
		return parts.back();
	}

	std::vector<engine::SimpleTile> game::Snake::getParts() {
		return parts;
	}

}
