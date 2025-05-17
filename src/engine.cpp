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

namespace engine {

	int start() {
		Vec2 windowSize{ 800, 600 };
		window::WindowData windowData = window::WindowData{ windowSize.x, windowSize.y, std::string("Snake openGL") };
		Frame frame;
		GLFWwindow* window = window::initDefaultWindow(windowData);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD");
		}
		glViewport(0, 0, windowData.width, windowData.height);
		Vec2 mapSize = Vec2{ 20, 20 };
		game::Game game = game::Game{ window, mapSize };
		engine::TiledRender render = engine::TiledRender{ engine::Window{ window, windowSize }, engine::Canvas { Vec2{0, 0}, mapSize } };
		while (!glfwWindowShouldClose(window)) {
			const float deltaTime = frame.calculateDeltaTime();
			std::span<engine::SimpleTile> tiles = game.process(deltaTime);
			render.draw(tiles);
		}
		return 1;
	}

	int end() {
		return 1;
	}
}
