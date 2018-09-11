#version 410

//uses position
layout(location = 0) in  vec4 Position;
//uses normal
layout(location = 1) in vec4 Normal;

//takes in position
out vec4 vPosition;
//takes in normal
out vec3 vNormal;
//takes in the PVM
uniform mat4 ProjectionViewModel;
//takes in the mesh's transform
uniform mat4 ModelMatrix;
//takes in the normal of the mesh
uniform mat3 NormalMatrix;

//runs the shader
void main()
{
	//stores the position based off position and the Mesh's transform
	vPosition = ModelMatrix * Position;
	//stores the normal of the mesh
	vNormal = NormalMatrix * Normal.xyz;
	//sets the position based off the PVM and the position
	gl_Position = ProjectionViewModel * Position;
}