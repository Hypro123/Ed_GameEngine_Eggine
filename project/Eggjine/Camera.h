#ifndef __CAMERA_H_
#define __CAMERA_H_

#include<ext.hpp>
#include"glfw3.h"
#include"gtc\quaternion.hpp"
#include"gtx\quaternion.hpp"

class Camera
{
public:
	//constructor
	Camera();
	//destructor
	~Camera();
	//virtually updates the camera
	virtual void update(float deltaTime) = 0;
//updates the view transform	
	void updateProjectionViewTransform();
	//sets the perspective
	void setPerspective(float fieldOfView, float aspectRatio, float near, float far);
	//sets where the camera looks at
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	//sets position in world space for the camera
	void setPosition(glm::vec3 position);
	//gets world transform
	glm::mat4 getWorldTransform() { return worldTransform; }
	//gets view transform
	glm::mat4 getView() { return viewTransform; }
	//gets projection transform
	glm::mat4 getProjection() { return projectionTransform; }
	//gets [rpjection's view transform
	glm::mat4 getProjectionView() { return projectionViewTransform; }


protected:
	//world transform
	glm::mat4 worldTransform;
	//transform of the view
	glm::mat4 viewTransform;
	//transform of the projection
	glm::mat4 projectionTransform;
	//view of the projection
	glm::mat4 projectionViewTransform;
	//stores window
	GLFWwindow* window;
};

#endif