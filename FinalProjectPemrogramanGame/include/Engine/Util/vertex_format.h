#pragma once
#include <glm/glm.hpp>

struct VertexFormat {
	glm::vec3 position;
	glm::vec2 texCoord;

	VertexFormat() {}
	VertexFormat(const glm::vec3& position, const glm::vec2& texCoord) {
		this->position = position;
		this->texCoord = texCoord;
	}
};