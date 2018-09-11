#ifndef __PROJ_H_
#define __PROJ_H_

#include"Application.h"
#include"FlyCamera.h"

#include"Shader.h"
#include"Mesh.h"
#include"OBJMesh.h"
#include"Texture.h"
#include"RenderTarget.h"

#include"Light.h"

#include"GameObject.h"

//inherits form application and every virtual function is called from here
class ProjectFile : public Application
{
public:
	//constructor
	ProjectFile();
	//destructor
	~ProjectFile();

	//acting constructor
	bool startup();
	//acting destructor
	void shutdown();
	//updates the project
	void update(float deltaTime);
	//draws everything in the scene
	void draw();

protected:

	FlyCamera* fCam;

	//soulspear
	aie::OBJMesh m_spearMesh; //mesh
	glm::mat4 m_SpearTransform; //transform
	GameObject* m_GSpear; //gameobject

	//Rabbit
	aie::OBJMesh m_RabbitMesh; //mesh
	glm::mat4 m_rabbitTransform;//transform
	GameObject* m_GRabbit;//gameobject
	
	//Dragon
	aie::OBJMesh m_dragonMesh;
	glm::mat4 m_dragonTransform;//transform
	GameObject* m_GDragon;//gameobject
	
	//shaders
	aie::ShaderProgram m_shader;	//shader for the other two gameobject
	aie::ShaderProgram m_texturedshader;	//shader for the post processing
	aie::ShaderProgram m_spearshader;	//spears normal map shader
	aie::RenderTarget m_renderTarget;	//for post processing effetc

	//fullscreen Quad
	Mesh m_fullscreenQuad;
	
	//light decleration for usage on gameobjects
	Light m_light;	//light for first object
	Light m_light1; //light for second object
	Light m_light2; //light for third object

	//ambient light in scene
	glm::vec3 ambientLight;	//ambience for first light
	float m_SpecularPower;	//specular power for 1st light
	glm::vec3 ambientLight1; //ambience for second light
	float m_SpecularPower1; //specular power for 2nd light
	glm::vec3 ambientLight2; //ambience for third light
	float m_SpecularPower2; //specular power for 3rd light
};

#endif