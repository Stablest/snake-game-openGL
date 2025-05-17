#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <filesystem>
#include <iostream>
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "tiled_render.hpp"
#include "span"

namespace engine {

	engine::TiledRender::TiledRender(Window window, Canvas canvas) :
		window(window),
		canvas(InternalCanvas{ canvas, window.size / canvas.mapSize }),
		shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag") {

		tileMap.clear();
		Vec2 tileSize = window.size / canvas.mapSize;
		for (int y = 0; y < canvas.mapSize.y; ++y) {
			for (int x = 0; x < canvas.mapSize.x; ++x) {
				Vec2 position{ x, y };
				Tile tile{ position, tileSize, 0 };
				tileMap.insert({ position, tile });
			}
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void engine::TiledRender::updateModifiedTiles(std::span<SimpleTile> simpleTiles) {
		for (int i = 0; i < simpleTiles.size(); ++i) {
			auto iterator = tileMap.find(simpleTiles[i].position);
			if (iterator != tileMap.end()) {
				iterator->second = Tile{
					simpleTiles[i],
					canvas.tileSize,
					0
				};
			}
		}
	}

	void engine::TiledRender::draw(std::span<engine::SimpleTile> simpleTiles) {
		glClear(GL_COLOR_BUFFER_BIT);

		updateModifiedTiles(simpleTiles);
		std::vector<Vec3f> vertices;
		vertices.reserve(tileMap.size() * sizeof(Tile));

		for (const auto& [key, value] : tileMap) {
			for (const auto& position : value.positions) {
				vertices.push_back(position);
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), 0);
		glEnableVertexAttribArray(0);

		glm::mat4 cameraOrtho = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

		shader.use();
		shader.setMatrix4fUniform("projection", glm::value_ptr(cameraOrtho));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glfwPollEvents();
		glfwSwapBuffers(window.window);
	}

	void engine::TiledRender::setWindowSize(Vec2 size) {
		window.size = size;
	}

}