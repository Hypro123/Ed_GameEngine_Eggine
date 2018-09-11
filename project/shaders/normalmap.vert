#version 410

layout( location = 0 ) in vec4 Position; //position
layout( location = 1 ) in vec4 Normal; //normal
layout( location = 2 ) in vec2 TexCoord; //texture coordinates
layout( location = 3 ) in vec4 Tangent; //tangent

out vec2 vTexCoord; //outputs texture coordinates
out vec3 vNormal; //outputs normal
out vec3 vTangent; //outputs tangent
out vec3 vBiTangent; //outputs BiTangent
out vec4 vPosition; //outputs position

//projection view model
uniform mat4 ProjectionViewModel;

// we need the model matrix seperate
uniform mat4 ModelMatrix;

// we need this matrix to transform the normal
uniform mat3 NormalMatrix;

void main() {
	//texture coordinates stored
	vTexCoord = TexCoord;
	//texture coordinates of y inversed
	vTexCoord.y = -TexCoord.y;
	//position of mesh
	vPosition = ModelMatrix * Position;
	//normal of mesh
	vNormal = NormalMatrix * Normal.xyz;
	//tangent of the mesh
	vTangent = NormalMatrix * Normal.xyz;
	//bitangent calculation
	vBiTangent = cross(vNormal, vTangent) * Tangent.w;
	//assigns position for the shader
	gl_Position = ProjectionViewModel * Position;
}