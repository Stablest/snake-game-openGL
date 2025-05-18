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
#include "unordered_set"
#include <random>


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
		, snake(SnakeParts{ std::vector<engine::SimpleTile>(1, {Vec2{mapSize.x / 2, mapSize.y / 2 }, Vec3f{0, 0, 0}, 0}) }, Vec2{ 0, 1 }, mapSize)
		, food(Vec2{ mapSize.x / 2, 4 + mapSize.y / 2 })
	{
		initMap(mapSize);
	}

	game::Game::~Game() {

	}

	void game::Game::verifyAndValidateCollisions() {
		engine::SimpleTile head = snake.getHead();
		if (head.position == food.tile.position) {
			food.on_collision(generateRandomMapPosition());
			snake.on_collision(head.position);
		}
	}

	Vec2 game::Game::generateRandomMapPosition() {
		static std::random_device rd;
		static std::mt19937 gen(rd());

		std::uniform_int_distribution<> distX(0, mapSize.x);
		std::uniform_int_distribution<> distY(0, mapSize.y);

		return Vec2{ distX(gen), distY(gen) };
	}

	void game::Game::physicsProcess(float deltaTime) {
		verifyAndValidateCollisions();
		snake.process(window, deltaTime);
	}

	std::vector<engine::SimpleTile> game::Game::draw(float deltaTime) {
		std::vector<engine::SimpleTile> snakeParts = snake.getParts();
		std::vector<engine::SimpleTile> toRenderTiles;
		toRenderTiles.reserve(snakeParts.size() + 1);
		for (auto& snakePart : snakeParts) {
			toRenderTiles.push_back(snakePart);
		}
		toRenderTiles.push_back(food.tile);
		return toRenderTiles;
	}

	void game::Game::process(float deltaTime) {
		snake.processInput(window, deltaTime);
	}

}