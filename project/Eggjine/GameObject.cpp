#include "GameObject.h"

//constructor for gameobject
GameObject::GameObject(aie::OBJMesh* m, FlyCamera *c, aie::ShaderProgram* s)
{
	//reference for the shader
	m_shaderReference = s;
	//reference for the camera
	camReference = c;
	//reference for the mesh
	m_myImportedMesh = m;
}

//destructor
GameObject::~GameObject()
{
	//delets all pointers
	delete m_shaderReference;
	delete camReference;
	delete m_myImportedMesh;
	//clears list
	lightsList.clear();
}

//creates a light and stores it in the gameobject
void GameObject::CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight, float spec)
{
	//assinging of values
	Light l;
	//direction of lights
	l.direction = lightDirection;
	//lights diffuse
	l.diffuse = lightDiffuse;
	//specular level of the lights
	l.specular = lightSpecular;
	//anbient colour of the light
	ambientLight = ambLight;
	//specular lighting's power
	m_specLight = spec;
	
	//adding this to a list of lights for sotring
	lightsList.push_back(l);
}

//creates a light and stores it in the gameobject
void GameObject::CreateLight(Light l, glm::vec3 amb, float spec)
{
	//assignfing of values
	ambientLight = amb;
	//specular lighting amount
	m_specLight = spec;
	//add to list of lights
	lightsList.push_back(l);
}

//draws gameobject
void GameObject::draw(FlyCamera* f, aie::ShaderProgram* rt)
{
	//stores camera
	camReference = f;
	//binds the shader
	rt->bind();
	//binds the shader to the camera transform
	rt->bindUniform("cameraPosition", camReference->getWorldTransform()[3]);

	//loop is useless
	for (int i = 0; i < lightsList.size(); i++)
	{
		//assigns light direction uniform
		rt->bindUniform("lightDirection", lightsList[i].direction);
		//asssigns ambiant light
		rt->bindUniform("Ia", ambientLight);
		//assigns diffuse values
		rt->bindUniform("Id", lightsList[i].diffuse);
		//assigns specular lighting
		rt->bindUniform("Is", lightsList[i].specular);
		//assigns specular lighting power
		rt->bindUniform("specularPower", m_specLight);

		//projection view model calculated
		auto pvm = camReference->getProjection() * camReference->getView() * m_transform;
		//binds the projection view model
		m_shaderReference->bindUniform("ProjectionViewModel", pvm);
		//binds normal matrix
		m_shaderReference->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_transform)));
		//draws the mesh
		m_myImportedMesh->draw();
	}
}