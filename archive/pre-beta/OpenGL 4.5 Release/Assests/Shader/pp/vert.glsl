#version 330 core
layout(location=0) in vec4 attribs;
out vec2 uv;
void main(void){
	gl_Position = vec4(attribs.xy, 1.0, 1.0);
	uv = attribs.zw;
}