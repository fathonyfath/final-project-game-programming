#include "Engine\Util\box.h"

GKV::Box::Box() {
}

GKV::Box::Box(const glm::vec2& size, string textureFilename, const GLuint& shader) {
	this->shader = shader;
	this->size = size;
	this->scale = glm::vec2(1.0f, 1.0f);
	this->rotation = 0.0f;

	vertices.push_back(VertexFormat(	// Bottom left
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f)
	));
	vertices.push_back(VertexFormat(	// Bottom right
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
	));
	vertices.push_back(VertexFormat(	// Top right
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(1.0f, 1.0f)
	));
	vertices.push_back(VertexFormat(	// Top left
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f)
	));
	indices = { 0, 1, 2, 0, 2, 3 }; // Face

									// Init buffers
	GLuint VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenTextures(1, &texture);

	// Load Texture
	int width, height;
	unsigned char* image = SOIL_load_image(textureFilename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO to VAO and verticies
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	// Bind EBO to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Bind Attrib Pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texCoord)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

GKV::Box::~Box() {
}

void GKV::Box::render() {
	glUseProgram(this->shader);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(this->position.x, this->position.y, 0.0f));
	model = glm::rotate(model, glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->size.x, this->size.y, 1.0f));
	model = glm::scale(model, glm::vec3(this->scale.x, this->scale.y, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
