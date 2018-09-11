#ifndef __MESH_H_
#define __MESH_H_
#include<ext.hpp>

//vertex data
struct Vertex
{
	//vertex's position
	glm::vec4 Position;
	//vertex's normal
	glm::vec4 Normal;
	//vertex's texture coordinates
	glm::vec2 TexCoord;
};

//holds data for the mesh
struct meshData
{
	//vertex array
	Vertex* v;
	//vertex segment amount
	int vertAmount;
 	//indicies array
	unsigned int * indicies;
	//amount of indicies in the array
	int indiciCount;
};

class Mesh
{
public:
	//sets base default values for constructor
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) { }
	//virtual delete
	virtual ~Mesh();
	
	//initialise for any shape
	void initialise(unsigned int vertexCount, const Vertex* verticies, unsigned int indexCount = 0, unsigned int* indicies = nullptr);
	//initialises a quad for the screen
	void initialiseFullscreenQuad();
	//initialises a quad
	void initialiseQuad();
	
	//draws the mesh
	void draw();
	//draws a box
	void drawBox(glm::vec3 center, glm::vec3 extents, glm::vec4 colour, glm::mat4* m = nullptr);
	//not complete yet, this is a work in progress function
	void drawCylinder(glm::vec3 center, float radius, float height, int segments, glm::vec4 colour, glm::mat4* m = nullptr);

	//gets position of mesh
	glm::mat4 getTransform() { return transformStore; }
	//sets position of mesh
	void setTransform(glm::mat4 m) { transformStore = m; }

	//circle
	meshData getCircleStruct(glm::vec3 center, float radius, int segments, glm::vec4 colour);

protected:
	//amount of tri's in an object
	unsigned int triCount;
	//decleration of buffers adnnvertex array
	unsigned int vao, vbo, ibo;
	//stores the transform
	glm::mat4 transformStore;
};

#endif