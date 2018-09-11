#ifndef __FLYCAMERA_H_
#define __FLYCAMERA_H_

#include"Camera.h"
#include"glfw3.h"

//inherits form camera
class FlyCamera : public Camera
{
public:
	//flycamera constructor
	FlyCamera(GLFWwindow* win);
	//destructor
	~FlyCamera();

	//updates the camera
	void update(float deltaTime);
	//sets the speed of th camera
	void setSpeed(float speed) { m_fspeed = speed; }

protected:
	//speed
	float m_fspeed;
	//up vector
	glm::vec3 m_up;

	//mouse position
	double m_mouseX;
	double m_mouseY;

	//mouse position
	double m_deltaMouseX;
	double m_deltaMouseY;

	//toggle
	bool canMoveCamera;
};

#endif