#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include "coordinates.hpp"
#include "tiled_render.hpp"

namespace game {

	struct SnakeParts {
		std::vector<engine::SimpleTile> tiles;
		size_t index;
	};

	class Snake {
	private:
		SnakeParts parts;
		Vec2 dir;
		Vec2 mapLimit;

		void move();

		void processInput(GLFWwindow* window, float deltaTime);

		void normalizeMapDirection();
	public:
		Snake(SnakeParts snakeParts, Vec2 dir, Vec2 mapLimit);

		void process(GLFWwindow* window, float deltaTime);

		size_t getSize();

		SnakeParts getParts();

		std::span<engine::SimpleTile> extractUsedTiles();
	};
}