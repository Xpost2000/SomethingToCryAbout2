// GLSL Base Shader VERTEX SHADER

#version 330 core
layout(location=0) in vec2 position;
layout(location =1) in vec2 texCoords;

/*
Define Matrix Uniforms.
*/
uniform mat4 model; // Model
uniform mat4 view; // View (Camera)
uniform mat4 projection; // Projection

out vec2 uv; // Out variable to send UVs to the Fragment Shader
void main(){
	gl_Position = projection*model*vec4(position, 0.0f, 1.0f);
	uv = texCoords;
}