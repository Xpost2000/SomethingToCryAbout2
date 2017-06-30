#version 330 core
in vec2 texCoords;
uniform sampler2D text;
uniform vec3 iClr;
out vec4 color;
void main(){
	vec4 sampled = vec4(1, 1, 1, texture(text, texCoords).r); // Use red value as alpha
	color = vec4(iClr, 1.) * sampled;
}