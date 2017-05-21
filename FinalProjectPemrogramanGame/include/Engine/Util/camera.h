#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Engine\Graphic\shader.h"

class Camera {
public:
	Camera(float screenWidth, float screenHeight);
	void updateShaderViewProjection(Shader& shader);
	glm::vec3 screenToWorldSpace(glm::vec2 screenSpace);

private:
	float screenWidth, screenHeight;
	glm::vec3 position, lookAt, up, halfScreen;
	glm::vec4 viewport;
	glm::mat4 view, projection;
};