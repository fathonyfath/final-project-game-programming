#version 330 core
in vec2 TexCoord;

// Texture samplers
uniform sampler2D ourTexture;
uniform vec3 spriteColor;

void main()
{
    gl_FragColor = vec4(spriteColor, 1.0) * texture(ourTexture, TexCoord);
}