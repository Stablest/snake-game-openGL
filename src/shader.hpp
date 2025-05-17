#pragma once

#include <string>

class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBoolUniform(const std::string& name, bool value) const;

	void setIntUniform(const std::string& name, int value) const;

	void setFloatUniform(const std::string& name, float value) const;

	void setMatrix4fUniform(const std::string& name, float* value) const;

private:
	static int createVertexShader(const char* source, int success, char infoLog[512]);

	static int createFragmentShader(const char* source, int success, char infoLog[512]);

	static int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader, int success, char infoLog[512]);
};