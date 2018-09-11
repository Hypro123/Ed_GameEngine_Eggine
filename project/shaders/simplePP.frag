#version 410

//takes in coordinates of texture
in vec2 vTexCoord;
//target colour
uniform sampler2D colourTarget;
//fragment colour output
out vec4 FragColour;

//output colour
vec4 Default(vec2 texCoord)
{
	//by default this does nothing
	return texture(colourTarget, texCoord);
}

//Blur
vec4 Blur(vec2 texCoord)
{
	//texel coordinates are calculated for a blur effet
	vec2 texel = 1.0f/ textureSize(colourTarget, 0);
	
	//colour initialised
	vec4 colour = texture(colourTarget, texCoord);
	//these calcuilations change the way the texture will look by adding values
	colour += texture(colourTarget, texCoord + texel * vec2(-1,1));
	colour += texture(colourTarget, texCoord + texel * vec2(-1,0));
	colour += texture(colourTarget, texCoord + texel * vec2(-1,-1));
	colour += texture(colourTarget, texCoord + texel * vec2(0,1));
	colour += texture(colourTarget, texCoord + texel * vec2(0,-1));
	colour += texture(colourTarget, texCoord + texel * vec2(1,1));
	colour += texture(colourTarget, texCoord + texel * vec2(1,0));
	colour += texture(colourTarget, texCoord + texel * vec2(1,-1));
	//returns colour
	return colour / 9;
}

//Distort
vec4 Distort(vec2 texCoord)
{
	//middle
	vec2 mid = vec2(0.5f);
	//calculates the distance from the center
	float distanceFromCentre = distance(texCoord, mid);
	//normal coordinates based off the middle
	vec2 normalizedCoord = normalize(texCoord - mid);
	//bias of the distort
	float bias = distanceFromCentre + sin(distanceFromCentre * 15) * 0.05f;
	//recalculation for the coordinates
	vec2 newCoord = mid + bias * normalizedCoord;
	//returns the distorted value
	return texture(colourTarget, newCoord);
}

//Distort
vec4 DistortBlur(vec2 texCoord)
{
	//middle
	vec2 mid = vec2(0.5f);
	//calculates the distance from the center
	float distanceFromCentre = distance(texCoord, mid);
	//normal coordinates based off the middle
	vec2 normalizedCoord = normalize(texCoord - mid);
	//bias for the distort
	float bias = distanceFromCentre + sin(distanceFromCentre * 15) * 0.05f;
	//recalculation for the coordinates
	vec2 newCoord = mid + bias * normalizedCoord;
	//texel calculation
	vec2 texel = 20.0f/ textureSize(colourTarget, 0);
	//colour initialised
	vec4 colour = texture(colourTarget, newCoord);
	//colour gets modified based off different values in order to get a blur effect
	colour += texture(colourTarget, newCoord + texel * vec2(-1,1));
	colour += texture(colourTarget, newCoord + texel * vec2(-1,0));
	colour += texture(colourTarget, newCoord + texel * vec2(-1,-1));
	colour += texture(colourTarget, newCoord + texel * vec2(0,1));
	colour += texture(colourTarget, newCoord + texel * vec2(0,-1));
	colour += texture(colourTarget, newCoord + texel * vec2(1,1));
	colour += texture(colourTarget, newCoord + texel * vec2(1,0));
	colour += texture(colourTarget, newCoord + texel * vec2(1,-1));

	//returns the colour
	return colour / 9;
}

void main()
{
	//size
	vec2 texSize = textureSize(colourTarget, 0);
	//changes the size of the texel
	vec2 texelSize = 1.0f/texSize;

	//adjust coordinates
	vec2 scale = (texSize - texelSize)/texSize;
	//texture coordinate scale
	vec2 texCoord = vTexCoord/scale + texelSize * 0.5f;

	//sample post effect
	FragColour = Distort(texCoord);
}