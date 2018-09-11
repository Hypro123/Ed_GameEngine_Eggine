#include "FlyCamera.h"
#include"defines.h"

FlyCamera::FlyCamera(GLFWwindow* win)
{
	//stores window
	window = win;
	//takes in movement speed
	m_fspeed = 100.0f;
	//stores up vector
	m_up = glm::vec3(0, 1, 0);

	//initialises matricies
	worldTransform = glm::mat4(1);
	viewTransform = glm::mat4(1);
	projectionTransform = glm::mat4(1);
	projectionViewTransform = glm::mat4(1);

	//sets the position of the camera
	setPosition(glm::vec3(glm::vec3(20, 20, 20)));
	//sets the point the camera is looking at
	setLookAt(worldTransform[3], glm::vec3(0), m_up);
	//sets the perspective
	setPerspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	//moving the camera boolean
	canMoveCamera = true;
	//switching cursor mode
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//setting cursor position
	glfwSetCursorPos(window, resolutionX/2, resolutionY/2);
}

//destructor
FlyCamera::~FlyCamera()
{
}

//updating the fly camera
void FlyCamera::update(float deltaTime)
{	
	//checks if the camera should allow the player to move the camera
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		if (canMoveCamera == true)
		{
			//hides the cursor adn locks its position
			glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		}
		//checks if the camera can be moved
		canMoveCamera = false;
		//mouse
		glfwGetCursorPos(window, &m_mouseX, &m_mouseY);
		//assings the delta to be in the center of the screen
		m_deltaMouseX = (resolutionX / 2 - m_mouseX) * 0.9f;
		m_deltaMouseY = (resolutionY / 2 - m_mouseY) * 0.9f;

		//lock cursor - hardcoded
		glfwSetCursorPos(window, resolutionX / 2, resolutionY / 2);
		//rotate around world up
		glm::vec4 up = glm::inverse(worldTransform) * glm::vec4(0, 1, 0, 0);

		glm::mat4 rotmat(1);
		//rotate around world up
		rotmat = glm::rotate((float)-m_deltaMouseX * deltaTime, glm::vec3(up[0], up[1], up[2]));
		viewTransform = rotmat * viewTransform;
		//rotate up/down
		rotmat = glm::rotate((float)-m_deltaMouseY * deltaTime, glm::vec3(1, 0, 0));
		viewTransform = rotmat * viewTransform;
		//world transform update
		worldTransform = glm::inverse(viewTransform);
		//keyboard
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[2] * deltaTime * -m_fspeed;
		}
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[2] * deltaTime * m_fspeed;
		}
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[0] * deltaTime * -m_fspeed;
		}
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[0] * deltaTime * m_fspeed;
		}
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[1] * deltaTime * m_fspeed;
		}
		//keycode checking
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			//camera movement
			worldTransform[3] += worldTransform[1] * deltaTime * -m_fspeed;
		}

		//making sure position 3, 3 is 1
		worldTransform[3][3] = 1.0f;
		//takes in inverse of the world's transform
		viewTransform = glm::inverse(worldTransform);
		//udpaetrs the projection view matrix
		updateProjectionViewTransform();
	}
	else
	{
		//keeps cursor as normal
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		canMoveCamera = true;
	}
}