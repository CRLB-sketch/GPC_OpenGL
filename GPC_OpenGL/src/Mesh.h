// Referencias: https://learnopengl.com/

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh 
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(TheShader& shader);
	
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};