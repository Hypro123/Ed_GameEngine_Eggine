#version 410

//takes in a position
layout(location = 0) in vec2 Position;

//sends out the texture coordinates
out vec2 vTexCoord;

void main()
{
	//texture coordinate is calculated and stored within vTexCoord
	vTexCoord = Position * 0.5f + 0.5f;
	//takes in posiiton of the mesh
	gl_Position = vec4(Position, 0, 1);
}