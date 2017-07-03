// GLSL Shader Fragment BASE SHADER
#version 330 core
out vec4 color;
uniform sampler2D tex;
uniform vec3 iClr;
uniform int textured;
in vec2 uv;

/*
This shader belongs to SomethingToCryAbout 2's Engine Source Code.
This is a basic GLSL shader that has the 3 capacities.

Render Texture.
Render Flat Color.
Render Texture + Color.

The output depends on the textured uniform variable
*/

void main(){

	vec2 TexUV = uv;
	TexUV.x = TexUV.x;
	TexUV.y = TexUV.y;
    if(textured == 1)
	color = texture(tex, TexUV); // Textured
	else if(textured == 2){
	color = vec4(iClr/255.f , 1.0f) * texture(tex, TexUV);
	}
	else if( textured == 0)
	color = vec4(iClr/255.0f, 1.0f); // Get RGB8 style color
	}