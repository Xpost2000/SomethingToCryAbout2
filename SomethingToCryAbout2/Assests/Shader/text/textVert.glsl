#version 330 core
layout(location =0) in vec4 attributes;
uniform mat4 proj;
out vec2 texCoords;

void main(){
		gl_Position = proj*vec4(attributes.xy, 1.f, 1.f);
		texCoords = attributes.zw;
}