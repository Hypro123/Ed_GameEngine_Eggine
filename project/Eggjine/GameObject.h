#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_

//#include"Mesh.h"
#include"OBJMesh.h"
#include"FlyCamera.h"
#include"Shader.h"
#include"Light.h"
#include<vector>
#include"RenderTarget.h"

class GameObject
{
public:
	//constructor override
	GameObject() { m_myImportedMesh = nullptr; m_shaderReference = nullptr; camReference = nullptr; }
	//constructor used as default constructor
	GameObject(aie::OBJMesh*, FlyCamera*, aie::ShaderProgram*);
	//destructor
	~GameObject();

	//creates light and adds it to a list
	void CreateLight(glm::vec3 lightDirection, glm::vec3 lightDiffuse, glm::vec3 lightSpecular, glm::vec3 ambLight, float m_SpecularPower);
	//creates light and adds it to a list override
	void CreateLight(Light l, glm::vec3 amb, float m_SpecularPower);
	
	//draws the gameobject when called
	void draw(FlyCamera*, aie::ShaderProgram*);

	//gets the transform of the gameobject
	glm::mat4 getTransform() { return m_transform; }
	//sets the transofrm of the gameobject
	void SetTransform(glm::mat4 m) { m_transform = m; }

private:
	//reference to the Mesh
	aie::OBJMesh* m_myImportedMesh;
	//reference to the shader
	aie::ShaderProgram* m_shaderReference;
	//camera reference
	FlyCamera *camReference;
	//transform
	glm::mat4 m_transform;
	
	//lights
	std::vector<Light> lightsList;
	//ambient lighting
	glm::vec3 ambientLight;
	//specular lighting
	float m_specLight;
};
#endif