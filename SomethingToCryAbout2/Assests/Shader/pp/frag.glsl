#version 330 core
uniform sampler2D frameBuffer;
in vec2 uv;
out vec4 color;
void main(void){
	color = texture (frameBuffer, uv);
}