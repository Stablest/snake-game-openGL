#include "food.hpp"

void game::Food::on_collision(Vec2 newPos) {
	tile.position = newPos;
}