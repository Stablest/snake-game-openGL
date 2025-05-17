#pragma once

#include "coordinates.hpp"
#include "GLFW/glfw3.h"
#include "vector"
#include "snake.hpp"
#include "tiled_render.hpp"
#include "span"

namespace game {

	class Game {
	private:
		GLFWwindow* window;
		game::Snake snake;
		std::vector<engine::SimpleTile> map;
		Vec2 mapSize;
		engine::SimpleTile point;

		void initMap(Vec2 mapSize);
	public:
		Game(GLFWwindow* window, Vec2 mapSize);

		~Game();

		std::span<engine::SimpleTile> process(float deltaTime);
	};
}