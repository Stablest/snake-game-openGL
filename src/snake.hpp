#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include "coordinates.hpp"
#include "tiled_render.hpp"
#include "queue"

namespace game {

	struct SnakeParts {
		std::vector<engine::SimpleTile> tiles;
	};

	class Snake {
	private:
		SnakeParts parts;
		std::queue<engine::SimpleTile> eatenTiles;
		Vec2 dir;
		Vec2 mapLimit;
		bool isEatenTileBuffered;

		void move();


		Vec2 normalizeHeadNextPos(Vec2& nextPos) const;
	public:
		Snake(SnakeParts snakeParts, Vec2 dir, Vec2 mapLimit);

		void process(GLFWwindow* window, float deltaTime);

		void processInput(GLFWwindow* window, float deltaTime);

		void integrateEatenTile();

		void on_collision(Vec2 colPos);

		engine::SimpleTile getHead();

		engine::SimpleTile getTail();

		std::vector<engine::SimpleTile> getParts();
	};
}