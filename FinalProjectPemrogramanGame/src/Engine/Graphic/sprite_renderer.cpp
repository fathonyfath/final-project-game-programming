#include "Engine\Graphic\sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader & shader) {
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
	glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::drawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size, float rotation, glm::vec3 color) {
	this->shader.use();
	glm::mat4 model;

	model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

	this->shader.setMatrix4("model", model);
	this->shader.setVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
	vertices.push_back(VertexFormat(	// Top Right
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec2(1.0f, 1.0f)
	));
	vertices.push_back(VertexFormat(	// Bottom right
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	));
	vertices.push_back(VertexFormat(	// Bottom Left
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec2(0.0f, 0.0f)
	));
	vertices.push_back(VertexFormat(	// Top left
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec2(0.0f, 1.0f)
	));
	indices = {
		0, 1, 3, // First Triangle
		1, 2, 3  // Second Triangle
	}; // Face
	
	// Init buffers
	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(this->VAO);

	// Bind VBO to VAO and verticies
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);

	// Bind EBO to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Bind Attrib Pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texCoord)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}
