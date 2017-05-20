#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Camera {
public:
	Camera(float screenWidth, float screenHeight);
	void draw();
	glm::vec3 screenToWorldSpace(glm::vec2 screenSpace);

	glm::mat4 getView();
	glm::mat4 getProjection();
private:
	float screenWidth, screenHeight;
	glm::vec3 position, lookAt, up, halfScreen;
	glm::vec4 viewport;
	glm::mat4 view, projection;
};