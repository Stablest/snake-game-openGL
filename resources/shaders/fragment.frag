#version 330 core

layout (location = 0) out vec4 fragColor;

in vec3 colorRGB;

void main() {
    fragColor = vec4(colorRGB, 1);
}