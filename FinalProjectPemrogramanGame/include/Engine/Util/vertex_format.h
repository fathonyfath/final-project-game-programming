#pragma once
#include <glm/glm.hpp>

struct VertexFormat {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;

	VertexFormat() {}
	VertexFormat(const glm::vec3& position, const glm::vec3& color, const glm::vec2& texCoord) {
		this->position = position;
		this->color = color;
		this->texCoord = texCoord;
	}
};