#version 330 core
uniform sampler2D frameBuffer;
in vec2 uv;
out vec4 color;
vec2 texCoords;
// The Various Shader Effects
uniform bool waterFX = false;
uniform bool greyScale = false;
uniform bool glitch = false; // This is only single
uniform float offSet;
/*
Something To Cry About 2 Postproccesor Shader Code.

Master shader for framebuffer based post processing

Effects can only be enabled one at a time.
*/

vec4 WaterSinWave(){
	vec4 colorRes;
	texCoords.x += sin(texCoords.y * 4*2*3.14159 + offSet) / 100;
	texCoords.y += cos(texCoords.x * 4*2*3.14159 + offSet) / 100;
	color = vec4(texture(frameBuffer, texCoords));
	color -= vec4(0.4, 0.6, 0.0, 0.0);
	return colorRes;
}

vec4 GlitchError(){
	vec4 colorRes;

	texCoords.y -= tan(texCoords.x / 3.141592654 - offSet) / 2;
	color = vec4(texture(frameBuffer, texCoords));
	float average = (color.r / sin(color.g * offSet +  color.b) );
	colorRes = vec4(average, average, average, 1.0f);
	return colorRes;
}

vec4 GreyScale(){

	vec4 colorRes;
	color = vec4(texture(frameBuffer, texCoords));
	float average = (color.r + color.g + color.b) / 3.0f;
	colorRes = vec4(average, average, average, 1.0f);
	return colorRes;
	/*
	vec4 colorRes;
	float px = 2000;
	float dx = 17 * ( 1 / px);
	float dy = 17 * ( 1 / px);
	texCoords = vec2( dx * floor(texCoords.x / dx), dy * floor(texCoords.y / dy) - offSet *999);
	color = vec4(texture(frameBuffer, texCoords));
	colorRes = vec4(0.3, color.g *2, 0.1, 1.0f);
	return colorRes*0.6;
*/
}

void main(void){
	texCoords = uv;
	
	if(glitch == true){
			color = GlitchError();
			return;
	}
	if(greyScale == true){
		color = GreyScale();
	}
	if(waterFX == true){
		color += WaterSinWave();
	}
	if((!greyScale && !waterFX && !glitch))
	color = vec4(texture (frameBuffer, texCoords));
}