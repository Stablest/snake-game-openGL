#pragma once

#include "coordinates.hpp"
#include "GLFW/glfw3.h"
#include "vector"
#include "snake.hpp"
#include "tiled_render.hpp"
#include "span"
#include "food.hpp"

namespace game {

	class Game {
	private:
		GLFWwindow* window;
		game::Snake snake;
		std::vector<engine::SimpleTile> map;
		Vec2 mapSize;
		Food food;

		void initMap(Vec2 mapSize);
	public:
		Game(GLFWwindow* window, Vec2 mapSize);

		~Game();

		void process(float deltaTime);

		void physicsProcess(float deltaTime);

		std::vector<engine::SimpleTile> draw(float deltaTime);

		Vec2 generateRandomMapPosition();

		void verifyAndValidateCollisions();
	};
}