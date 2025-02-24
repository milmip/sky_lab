#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	
	Shader();
    ~Shader();

	void Init(const char* vertexPath, const char* fragmentPath);


	void Use(); 
	

	static void setBool(int ID, const std::string &name, bool value);
	static void setInt(int ID, const std::string &name, int value);
	static void setFloat(int ID, const std::string &name, float value);
	static void setVec2(int ID, const std::string &name, const glm::vec2 &value);
	static void setVec2(int ID, const std::string &name, float x, float y);
	static void setVec3(int ID, const std::string &name, const glm::vec3* vec);
	static void setVec3(int ID, const std::string &name, float x, float y, float z);
	static void setVec4(int ID, const std::string &name, const glm::vec4 &value);
	static void setVec4(int ID, const std::string &name, float x, float y, float z, float w);
	static void setMat2(int ID, const std::string &name, const glm::mat2* mat);
	static void setMat3(int ID, const std::string &name, const glm::mat3* mat);
	static void setMat4(int ID, const std::string &name, glm::mat4* mat);

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif
