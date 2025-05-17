#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aRGB;

out vec3 colorRGB;

uniform mat4 projection;

void main() {
	gl_Position = projection * vec4(aPos, 1.0);
	colorRGB = aRGB;
}