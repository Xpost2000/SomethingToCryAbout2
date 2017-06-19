#version 330 core
out vec4 color;
sampler2D tex;
in vec2 uv;
void main(){
	color = texture(tex, uv);
}