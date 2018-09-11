#include "ProjectFile.h"
#include<iostream>

//constructor
ProjectFile::ProjectFile() {}

//destructor
ProjectFile::~ProjectFile() {}

//acting constructor
bool ProjectFile::startup()
{
	//loads simple phong shader
	//loading vertext shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simple.vert");
	//loading fragment shjader
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simple.frag");
	//checking if the shader has loaded
	if (m_shader.link() == false)
	{
		//if the shader has not loaded the program will close
		printf("shader error %s", m_shader.getLastError());
		return false;
	}
	//temp variables for screen dimensions
	int H; //height
	int W; //weight
	//this function gets the window's size and stores the dimensions within H and W
	glfwGetWindowSize(window, &W, &H);

	//Attempts to initialise the rendertarget with the screens dimensions
	if (m_renderTarget.initialise(1, W, H) == false) {
		//If this fails the program will close
		printf("Render Target Error!\n");
		return false;
	}
	//initialises th quad
	m_fullscreenQuad.initialiseFullscreenQuad();
	//loading shaders for post processing
	//vertex shader fro post processing
	m_texturedshader.loadShader(aie::eShaderStage::VERTEX, "../shaders/simplePP.vert");
	//fragment shader for post processing
	m_texturedshader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/simplePP.frag");

	//checks if the textured shader is linked
	if (m_texturedshader.link() == false) {
		//program will not run if the shader is not found
		printf("Post Shader Error: %s\n",
			m_texturedshader.getLastError());
		return false;
	}
	//loading shaders for 
	//vertex shader for spear
	m_spearshader.loadShader(aie::eShaderStage::VERTEX, "../shaders/normalmap.vert");
	//fragment shader for spear
	m_spearshader.loadShader(aie::eShaderStage::FRAGMENT, "../shaders/normalmap.frag");

	//checks to see if the shader exists
	if (m_spearshader.link() == false)
	{
		//program closes if there is no shader found
		printf("shader error %s", m_spearshader.getLastError());
		return false;
	}

	//loading dragon obj
	if (m_dragonMesh.load("../stanford/dragon.obj") == false)
	{
		//program closes if the obj is not found
		printf("Mesh Error!\n");
		return false;
	}
	//loading rabbit obj
	if (m_RabbitMesh.load("../stanford/Bunny.obj") == false)
	{
		//program closes if the obj is not found
		printf("Mesh Error!\n");
		return false;
	}
	//loading spear obj
	if (m_spearMesh.load("../soulspear/soulspear.obj") == false)
	{
		//program closes if the obj is not found
		printf("Mesh Error!\n");
		return false;
	}

	//dragon transform initialisation
	m_dragonTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	//rabbit transform initialisation
	m_rabbitTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		10, 0, 0, 1
	};

	//spear transform initialisation
	m_SpearTransform = 
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 10, 1
	};

	//lightinitialisaion
	//setting light's diffuse colour
	m_light.diffuse = { 1, 0, 1 };
	//setting light's specular colour
	m_light.specular = {1, 0, 1};
	//setting lights direction
	m_light.direction = {-1, 3.14f, -1.5};
	//colour of ambient light
	ambientLight = { 0.0f, 1.0f, 1.0f};
	//power of specular lighting
	m_SpecularPower = 100;

	//light 2 initialisaion
	//setting light's diffuse colour
	m_light1.diffuse = { 0, 1, 1 };
	//setting light's specular colour
	m_light1.specular = { 0, 1, 0 };
	//setting lights direction
	m_light1.direction = { -1, -3.14f, -2.5f };
	//colour of ambient light
	ambientLight1 = { 1.0f, 1.0f, 0.0f };
	//power of specular lighting
	m_SpecularPower1 = 200;
	
	//light 3 values initialisaion
	//setting light's diffuse colour
	m_light2.diffuse = { 0.95f, 0.02f, 0.1f };
	//setting light's specular colour
	m_light2.specular = { 1, 1, 0 };
	//setting lights direction
	m_light2.direction = { 21, -3.14f, -2.5f };
	//colour of ambient light
	ambientLight2 = { 1.0f, 0.0f, 1.0f };
	//power of specular lighting
	m_SpecularPower2 = 500;

	//spear initialisation with lights
	m_GSpear = new GameObject(&m_spearMesh, fCam, &m_shader);
	//sets position of the spear
	m_GSpear->SetTransform(m_SpearTransform);
	//creates a light for the spear gameobject
	m_GSpear->CreateLight(m_light, ambientLight, m_SpecularPower);
	//rabbit initialisation with lights
	m_GRabbit = new GameObject(&m_RabbitMesh, fCam, &m_shader);
	//sets position for the rabbit
	m_GRabbit->SetTransform(m_rabbitTransform);
	//creates a light for the spear gameobject
	m_GRabbit->CreateLight(m_light1, ambientLight1, m_SpecularPower1);
	//dragon initialisation with lights
	m_GDragon = new GameObject(&m_dragonMesh, fCam, &m_shader);
	//sets position for the dragon
	m_GDragon->SetTransform(m_dragonTransform);
	//creates a light for the dragon gameobject
	m_GDragon->CreateLight(m_light2, ambientLight2, m_SpecularPower2);

	//camera initialisation
	fCam = new FlyCamera(window);
	
	return true;
}
//acting destructor
void ProjectFile::shutdown()
{
	//delets the camera
	delete fCam;
}
//update function
void ProjectFile::update(float deltaTime)
{
	//updates the camera
	fCam->update(deltaTime);
}

//draw function, draws everything in the scene
void ProjectFile::draw()
{
	//binds for post processing
	m_renderTarget.bind();
	//clears screen
	clearScreen();

	//pvm calulations
	auto pvm = fCam->getProjection() * fCam->getView() * m_SpearTransform;
	//binding all required values to the spear
	//binds PVM
	m_spearshader.bindUniform("ProjectionViewModel", pvm);
	//binds spears transform
	m_spearshader.bindUniform("ModelMatrix", m_SpearTransform);
	//binds the diffuse texture
	m_spearshader.bindUniform("diffuseTexture", 0);
	//binds specular lighting texture
	m_spearshader.bindUniform("specularTexture", 0);
	//binds normal texture
	m_spearshader.bindUniform("normalTexture", 0);
	//binds the normal Matrix of the spear, the inverse
	m_spearshader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_SpearTransform)));
	//draws the spear
	m_GSpear->draw(fCam, &m_spearshader);

	//shaders
	m_shader.bind();

	//binding
	m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	//camera and normal mapping
	pvm = fCam->getProjection() * fCam->getView() *  m_dragonTransform;
	//binding all required values to the dragon
	//binds the PVM
	m_shader.bindUniform("ProjectionViewModel", pvm);
	//binds rabbits transform
	m_shader.bindUniform("ModelMatrix", m_dragonTransform);
	//binds the inverse of the dragons transform
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_dragonTransform)));
	//draws the dragon
	m_GDragon->draw(fCam, &m_shader);

	//binding
	m_shader.bindUniform("cameraPosition", fCam->getWorldTransform()[3]);

	//camera and normal mapping
	pvm = fCam->getProjection() * fCam->getView() *  m_rabbitTransform;
	//binding all required values to rabbit
	//binds PVM
	m_shader.bindUniform("ProjectionViewModel", pvm);
	//binds rabbits transform
	m_shader.bindUniform("ModelMatrix", m_rabbitTransform);
	//binds the inverse of the rabbits transform
	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_rabbitTransform)));
	
	//draws the rabbit
	m_GRabbit->draw(fCam, &m_shader);
	//unbinds the rendere
	m_renderTarget.unbind();

	clearScreen();
	//post processing effects
	//binds the post processing shader
	m_texturedshader.bind();
	//binds the colourtarget
	m_texturedshader.bindUniform("colourTarget", 0);
	//binds it to the rendertarget
	m_renderTarget.getTarget(0).bind(0);
	
	//draws full screen quad
	m_fullscreenQuad.draw();

	aie::Gizmos::draw(fCam->getProjectionView());
}