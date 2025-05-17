#pragma once

#include "iostream"
#include <functional>

struct Vec2 {
	int x;
	int y;

	Vec2 operator/(Vec2 const& obj) {
		return Vec2{ x / obj.x, y / obj.y };
	}

	bool operator==(Vec2 const& obj) const {
		return obj.x == x && obj.y == y;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vec2& p) {
		os << "x: " << p.x << ", y: " << p.y;
		return os;
	}
};

struct Vec3 {
	int x;
	int y;
	int z;
};

struct Vec3f {
	float x;
	float y;
	float z;

	friend std::ostream& operator<<(std::ostream& os, const Vec3& p) {
		os << "x: " << p.x << ", y: " << p.y << ", z: " << p.z;
		return os;
	}
};

namespace std {
	template <>
	struct hash<Vec2> {
		size_t operator()(const Vec2& v) const {
			return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
		}
	};
}