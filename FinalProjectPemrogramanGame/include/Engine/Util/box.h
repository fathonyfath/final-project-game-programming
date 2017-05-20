#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <SOIL/SOIL.h>

#include "Engine\Util\vertex_format.h"

using namespace std;

namespace GKV {
	class Box {
	public:
		Box();
		Box(const glm::vec2& size, string textureFilename, const GLuint& shader);
		~Box();
		void render();
		glm::vec2 position;
		float rotation;
		glm::vec2 scale;
	private:
		glm::vec2 size;
		GLuint shader;
		GLuint texture;
		GLuint VAO;
		std::vector<VertexFormat> vertices;
		std::vector<unsigned int> indices;
	};
}