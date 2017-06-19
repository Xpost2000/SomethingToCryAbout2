#version 330 core
out vec4 color;
uniform vec3 iClr;
void main(){
	color = vec4(iClr.r / 255.0f, iClr.g / 255.0f, iClr.b / 255.0f, 1.0f);
}