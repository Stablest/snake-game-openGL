#pragma once

namespace engine {
	class Frame {
	private:
		float deltaTime = 0;
		float currentFrame = 0;
		float lastFrame = 0;
	public:
		float calculateDeltaTime();
	};
}
