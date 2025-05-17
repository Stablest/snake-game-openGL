#pragma once

#include "tiled_render.hpp"

namespace game {

	class Food {
	public:
		engine::SimpleTile tile;

		Food(Vec2 position) {
			tile = engine::SimpleTile{ position, Vec3f(0, 0, 0), 0 };
		}

		void on_collision(Vec2 newPos);

	};
}