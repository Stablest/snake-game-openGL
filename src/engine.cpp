#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "window.hpp"
#include "stdexcept"
#include "frame.hpp"
#include "game.hpp"
#include "engine.hpp"
#include "tiled_render.hpp"
#include "coordinates.hpp"
#include "span"
#include "thread"

namespace engine {

	int start() {
		constexpr float TARGET_LOOPS_SEC = 8;
		constexpr float TARGET_LOOP_TIME = 1.0F / TARGET_LOOPS_SEC;

		Vec2 windowSize{ 800, 600 };
		window::WindowData windowData = window::WindowData{ windowSize.x, windowSize.y, std::string("Snake openGL") };
		Frame frame;
		Frame physicsFrame;
		GLFWwindow* window = window::initDefaultWindow(windowData);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD");
		}
		glViewport(0, 0, windowData.width, windowData.height);
		Vec2 mapSize = Vec2{ 40, 30 };
		game::Game game = game::Game{ window, mapSize };
		engine::TiledRender render = engine::TiledRender{ engine::Window{ window, windowSize }, engine::Canvas { Vec2{0, 0}, mapSize } };
		float loopTime = 0;
		float frameTime = 0;

		while (!glfwWindowShouldClose(window)) {
			loopTime = 0;
			const float physicsDeltaTime = physicsFrame.calculateDeltaTime();
			game.physicsProcess(physicsDeltaTime);
			// Draw/Process loop
			while (loopTime < TARGET_LOOP_TIME) {
				const float deltaTime = frame.calculateDeltaTime();
				game.process(deltaTime);
				std::vector<engine::SimpleTile> tilesVec = game.draw(deltaTime);
				std::span<engine::SimpleTile> tiles = tilesVec;
				render.draw(tiles);
				loopTime += deltaTime;
			}
		}
		return 1;
	}

	int end() {
		return 1;
	}
}
