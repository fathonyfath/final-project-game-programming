/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#pragma once

#include <GL/glew.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
public:
	// Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
	GLuint id;
	// Texture image dimensions
	GLuint width, height; // Width and height of loaded image in pixels
						  // Texture Format
	GLuint internalFormat; // Format of texture object
	GLuint imageFormat; // Format of loaded image
						 // Texture configuration
	GLuint wrapS; // Wrapping mode on S axis
	GLuint wrapT; // Wrapping mode on T axis
	GLuint filterMin; // Filtering mode if texture pixels < screen pixels
	GLuint filterMax; // Filtering mode if texture pixels > screen pixels
					   // Constructor (sets default texture modes)
	Texture2D();
	// Generates texture from image data
	void generate(GLuint width, GLuint height, unsigned char* data);
	// Binds the texture as the current active GL_TEXTURE_2D texture object
	void bind() const;
};
