#pragma once

#include "vector"
#include "coordinates.hpp"
#include "shader.hpp"
#include "GLFW/glfw3.h"
#include "span"
#include "unordered_map"
#include "array"


namespace engine {
	using TileVertices = std::array<Vec3f, 6>;

	struct Canvas {
		Vec2 position;
		Vec2 mapSize;
	};

	struct InternalCanvas {
		Canvas canvas;
		Vec2 tileSize;
	};

	struct Window {
		GLFWwindow* window;
		Vec2 size;

	};

	struct SimpleTile {
		Vec2 position;
		Vec3 colorRGB;
		int padding;
	};

	struct Tile {
		TileVertices positions;
		Vec3 colorRGB;
		int padding;

		Tile() {

		}

		Tile(SimpleTile simpleTile, Vec2 tileSize, int zIndex) {
			Vec2 pos = simpleTile.position;
			positions = {
				Vec3f{
					(float)pos.x * tileSize.x + simpleTile.padding,
					(float)pos.y * tileSize.y - simpleTile.padding,
					(float)zIndex
				},
				Vec3f{
					(float)pos.x * tileSize.x + tileSize.x - simpleTile.padding,
					(float)pos.y * tileSize.y - simpleTile.padding,
					(float)zIndex
				},
				Vec3f{
					(float)pos.x * tileSize.x + simpleTile.padding,
					(float)pos.y * tileSize.y - tileSize.y + simpleTile.padding,
					(float)zIndex
				},
				Vec3f{
					(float)pos.x * tileSize.x + tileSize.x - simpleTile.padding,
					(float)pos.y * tileSize.y - simpleTile.padding,
					(float)zIndex
				},
				Vec3f{
					(float)pos.x * tileSize.x + simpleTile.padding,
					(float)pos.y * tileSize.y - tileSize.y + simpleTile.padding,
					(float)zIndex
				},
				Vec3f{
					(float)pos.x * tileSize.x + tileSize.x - simpleTile.padding,
					(float)pos.y * tileSize.y - tileSize.y + simpleTile.padding,
					(float)zIndex
				}
			};
			colorRGB = Vec3{ 0, 127, 0 };
			padding = simpleTile.padding;
		}

		Tile(Vec2 position, Vec2 tileSize, int zIndex) {
			positions = {
				Vec3f{
					(float)position.x * tileSize.x,
					(float)position.y * tileSize.y,
					(float)zIndex
				},
				Vec3f{
					(float)(position.x * tileSize.x) + tileSize.x,
					(float)position.y * tileSize.y,
					(float)zIndex
				},
				Vec3f{
					(float)position.x * tileSize.x,
					(float)(position.y * tileSize.y) + tileSize.y,
					(float)zIndex
				},
				Vec3f{
					(float)(position.x * tileSize.x) + tileSize.x,
					(float)position.y * tileSize.y,
					(float)zIndex
				},
				Vec3f{
					(float)position.x * tileSize.x,
					(float)(position.y * tileSize.y) + tileSize.y,
					(float)zIndex
				},
				Vec3f{
					(float)(position.x * tileSize.x) + tileSize.x,
					(float)(position.y * tileSize.y) + tileSize.y,
					(float)zIndex
				}
			};
			colorRGB = Vec3{ 0, 127, 0 };
			padding = 0;
		}
	};

	class TiledRender {
	private:
		Window window;
		InternalCanvas canvas;
		Shader shader;
		std::unordered_map<Vec2, Tile> tileMap;

		unsigned int VBO, VAO;

		void updateModifiedTiles(std::span<SimpleTile> simpleTiles);
	public:
		TiledRender(Window window, Canvas canvas);
		void draw(std::span<engine::SimpleTile>);

		void setWindowSize(Vec2 windowSize);
	};

}