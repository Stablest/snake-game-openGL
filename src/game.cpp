#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "vector"
#include "snake.hpp"
#include "coordinates.hpp"
#include "snake.hpp"
#include "game.hpp"
#include "tiled_render.hpp"
#include <algorithm>
#include <iterator>
#include "span"


namespace game {

	void game::Game::initMap(Vec2 mapSize) {
		map = std::vector<engine::SimpleTile>(mapSize.x * mapSize.y);
		for (int y = 0; y < mapSize.y; y++) {
			for (int x = 0; x < mapSize.x; x++) {
				map.push_back(engine::SimpleTile{ Vec2{ x, y}, Vec3f{ 0, 0, 0}, 0 });
			}
		}
	}

	game::Game::Game(GLFWwindow* window, Vec2 mapSize)
		: window(window)
		, mapSize(mapSize)
		, snake(SnakeParts{ std::vector<engine::SimpleTile>(1, {Vec2{mapSize.x / 2, mapSize.y / 2 }, Vec3f{0, 0, 0}, 0}), 1 }, Vec2{ 0, 1 }, mapSize)
		, point(engine::SimpleTile{ Vec2 {20, 20}, Vec3f{0, 255, 0 }, 5 })
	{
		initMap(mapSize);
	}

	game::Game::~Game() {

	}

	std::span<engine::SimpleTile> game::Game::process(float deltaTime) {
		snake.process(window, deltaTime);
		return snake.extractUsedTiles();
	}

}