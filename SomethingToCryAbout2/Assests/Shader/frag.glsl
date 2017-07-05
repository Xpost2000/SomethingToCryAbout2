// GLSL Shader Fragment BASE SHADER
#version 330 core
out vec4 color;
uniform sampler2D tex;
uniform vec3 iClr;
uniform int textured;
uniform float offset;
in vec2 uv;

/*
This shader belongs to SomethingToCryAbout 2's Engine Source Code.
This is a basic GLSL shader that has the 4 capacities.

Render Texture.
Render Flat Color.
Render Texture + Color.
Render With Sin Wave and Cos Wave pattern ( for dat water fx )

The output depends on the textured uniform variable
in order respective to above
0 1 2 3
*/

void main(){

	vec2 TexUV = uv;
	if(textured == 3){
		TexUV.x += sin(TexUV.y * 8*2*3.14159 + offset) / 30;
		TexUV.y += cos(TexUV.x * 8*2*3.14159 /  offset) / 30;
		color = texture(tex, TexUV); // Textured
	}else if(textured == 1)
	color = texture(tex, TexUV); // Textured
	else if(textured == 2){
	color = vec4(iClr/255.f , 1.0f) * texture(tex, TexUV);
	}
	else if( textured == 0)
	color = vec4(iClr/255.0f, 1.0f); // Get RGB8 style color
	}