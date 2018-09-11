#include "Mesh.h"
#include"gl_core_4_5.h"

Mesh::~Mesh()
{
	//deletes and cleans out buffers and vertex array
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

//initialises a mesh with vertex count, array fo verticies, index count and array of indicies
void Mesh::initialise(unsigned int vertexCount, const Vertex* verticies, unsigned int indexCount, unsigned int* indicies)
{
	assert(vao == 0);

	//gen buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array, mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	//bind indicies if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

		//divide by 3 in order to get triangle amount
		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}
	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::initialiseFullscreenQuad()
{
	assert(vao == 0);
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// define vertices
	float vertices[] = {
		-1,1, // left top
		-1,-1, // left bottom
		1,1, // right top
		-1,-1, // left bottom
		1,-1, // right bottom
		1, 1 // right top
	};
	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices,
		GL_STATIC_DRAW);
	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, 0);
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// quad has 2 triangles
	triCount = 2;
}

void Mesh::draw()
{
	//binds the vertext array
	glBindVertexArray(vao);
	//indicies or verticies
	//draws an object depending on the information stored in the two buffers
	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not initialized already
	assert(vao == 0);
	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// define 6 vertices for 2 triangles
	Vertex vertices[6];
	//sets positions
	vertices[0].Position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].Position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].Position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].Position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].Position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].Position = { 0.5f, 0, -0.5f, 1 };
	//sets normals
	vertices[0].Normal = {0, 1, 0, 0};
	vertices[1].Normal = { 0, 1, 0, 0 };
	vertices[2].Normal = { 0, 1, 0, 0 };
	vertices[3].Normal = { 0, 1, 0, 0 };
	vertices[4].Normal = { 0, 1, 0, 0 };
	vertices[5].Normal = { 0, 1, 0, 0 };
	//sets texture coordinates
	vertices[0].TexCoord = { 0, 1 }; // bottom left
	vertices[1].TexCoord = { 1, 1 }; // bottom right
	vertices[2].TexCoord = { 0, 0 }; // top left
	vertices[3].TexCoord = { 0, 0 }; // top left
	vertices[4].TexCoord = { 1, 1 }; // bottom right
	vertices[5].TexCoord = { 1, 0 }; // top right

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);
	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	// enable second element as normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	
	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// quad has 2 triangles
	triCount = 2;
}

//draws a box
void Mesh::drawBox(glm::vec3 center, glm::vec3 extents, glm::vec4 colour, glm::mat4* m)
{
	//stores box's transform
	transformStore = *m;

	//amount of vertexes a box requires
	Vertex verts[8];
	//assings a center for the box
	glm::vec3 c = center;
	
	//extents
	glm::vec3 vX(extents.x, 0, 0);
	glm::vec3 vY(0, extents.y, 0);
	glm::vec3 vZ(0, 0, extents.z);
	
	//if the matrix is not defined
	if (m != nullptr)
	{
		//sets the positions of the box's bounds
		vX = glm::vec3((*m * glm::vec4(vX, 0)));
		vY = glm::vec3((*m * glm::vec4(vX, 0)));
		vZ = glm::vec3((*m * glm::vec4(vX, 0)));
		c = glm::vec3(glm::vec3((*m)[3]) + c);
	}

	//sets the positions of the box based off extents
	verts[0].Position = glm::vec4(glm::vec3(extents.x / 2, -extents.y / 2, extents.z / 2), 1);
	verts[1].Position = glm::vec4(glm::vec3(extents.x / 2, -extents.y / 2, -extents.z / 2), 1);
	verts[2].Position = glm::vec4(glm::vec3(-extents.x / 2, -extents.y / 2, -extents.z / 2), 1);
	verts[3].Position = glm::vec4(glm::vec3(-extents.x / 2, -extents.y / 2, extents.z / 2), 1);
	verts[4].Position = glm::vec4(glm::vec3(extents.x / 2, extents.y / 2, extents.z / 2), 1);
	verts[5].Position = glm::vec4(glm::vec3(extents.x / 2, extents.y / 2, -extents.z / 2), 1);
	verts[6].Position = glm::vec4(glm::vec3(-extents.x / 2, extents.y / 2, -extents.z / 2), 1);
	verts[7].Position = glm::vec4(glm::vec3(-extents.x / 2, extents.y / 2, extents.z / 2), 1);

	//sets the indicies for the 6 quads to draw
	unsigned int indicies[36] = { 
		0, 1, 2, 2, 0, 3,
		0, 3, 7, 7, 0, 4,
		7, 6, 5, 5, 7, 4,
		3, 7, 2, 2, 7, 6,
		0, 1, 5, 5, 0, 4,
		6, 5, 1, 1, 6, 2
	};
	//calls initialise and creates a box
	initialise(8, verts, 36, indicies);
}

//is able to draw a cylinder
//THIS IS INCOMEPLETE AND WILL BE IMPLEMENTED COMPLETELY AT A LATER DATE
void Mesh::drawCylinder(glm::vec3 center, float radius, float height, int segments, glm::vec4 colour, glm::mat4* m)
{
	//creates 2 circles and stores their data
	meshData retdat1 = getCircleStruct(glm::vec4(center.x, center.y + height/2, center.z, 1), radius, segments, colour);
	meshData retdat2 = getCircleStruct(glm::vec4(center.x, center.y + -height/2, center.z, 1), radius, segments, colour);

	//initialises the indicies of the 2 circles into 1 array
	unsigned int* indicies = new unsigned int[retdat1.indiciCount + retdat2.indiciCount];
	//initialises the amount of indicies used for the 2 circles
	unsigned int indCount = retdat1.indiciCount + retdat2.indiciCount ;
	
	//initialises vertex arrays into one
	Vertex* verts = new Vertex[retdat1.vertAmount + retdat2.vertAmount];
	//initialises the amount of verticies used for the 2 circles
	unsigned int vertCount = retdat1.vertAmount + retdat2.vertAmount;

	//indicies
	for(int i = 0; i < retdat1.indiciCount; i++)
	{
		//adds first set of indicies to array
		indicies[i] = retdat1.indicies[i];
	}
	for(int i = (retdat1.indiciCount); i < indCount; i++)
	{
		//adds second set of indicies to the array
		indicies[i] = retdat2.indicies[i - retdat2.indiciCount] + segments + 1;
	}

	//verticies
	for(int i = 0; i < retdat1.vertAmount; i++)
	{
		//adds first set of verticies to the array
		verts[i] = retdat1.v[i];
	}
	for(int i = retdat1.vertAmount; i < vertCount; i++)
	{
		//adds second set of verticies to the array
		verts[i] = retdat2.v[i - retdat2.vertAmount];
	}
	//initialsies this gameobject
	initialise(vertCount, verts, indCount, indicies);
}

//creats a circle and returns the information
meshData Mesh::getCircleStruct(glm::vec3 center, float radius, int segments, glm::vec4 colour)
{
	//initialises vertex amount by adding in the centerpoint of the circle
	int vertAmount = segments + 1;
	Vertex* verts = new Vertex[vertAmount];
	//initialises the indicies pointer
	unsigned int* indicies;
	//initialises the indicies array with given informaiton
	int count = segments * 3 + 1;
	indicies = new unsigned int[count];
	//temporary value
	int tempValue = 0;
	

	//initialies positions of everything for the texture
	for (int i = 0; i < vertAmount; i++)
	{
		//initialises the vertex's positions
		verts[i].Position = glm::vec4(center, 1);
		//initialises the vertex normals
		verts[i].Normal = glm::vec4(0.0f, 0.0f, 0.0f, 1);
		//initialises the vertex's texture coordinates
		verts[i].TexCoord = glm::vec2(0.0f, 0.0f);
	}


	//initialisation
	for (int i = 0; i < count; ++i)
	{
		//initialises indicies at 0
		indicies[i] = 0;
	}
	//sets position of all the points
	for (int i = 1; i < vertAmount; i++)
	{
		//this assigns all of the verticie's positions
		verts[i].Position = glm::vec4(sinf((2 * glm::pi<float>()) / segments * i) * radius, center.y, cosf((2 * glm::pi<float>()) / segments * i) * radius, 1);
	}

	//loop that assings all of the circle indicies
	for (int i = 1; i < count; i++)
	{
		if ((i % 3) == 0)
		{
			//uses the centerpoint of the circle
			indicies[i] = 0;
			//increments the temporary value
			tempValue += 2;
		}
		else
		{
			//run through in order
			indicies[i] = (i - tempValue);
			//goes to next point
			indicies[i + 1] = indicies[i] + 1;
		}
		//this makes sure that the circle will not outgrow the amount of segments it has
		if (indicies[i] > segments)
			indicies[i] = indicies[1];
	}
	
	count--;

	//adds all data to meshdata
	meshData retData;
	//amount of indicies
	retData.indiciCount = count;
	//indicies array
	retData.indicies = indicies;
	//verticies array
	retData.v = verts;
	//amount of verticies
	retData.vertAmount = vertAmount;
	//returns the calculated data
	return retData;
}