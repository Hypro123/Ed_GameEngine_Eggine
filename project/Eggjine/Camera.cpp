#include "Camera.h"


//constructor
Camera::Camera(){}

//destructor
Camera::~Camera()
{}

//updates the view transform for the projection
void Camera::updateProjectionViewTransform()
{
	//updaets the projeciton view transform based on projection transform and view transform
	projectionViewTransform = projectionTransform * viewTransform;
}
//sets the perspective
void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far) 
{
	//projection transform calculation for perspective
	projectionTransform = glm::perspective(fieldOfView, aspectRatio, near, far);
	//updates the projection view matrix
	updateProjectionViewTransform();
}
//sets look at position
void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up) 
{
	//sets where the view transform is looking
	viewTransform = glm::lookAt(from, to, up);
	//uipdates the projection view matrix
	updateProjectionViewTransform();
}
//sets cameras position
void Camera::setPosition(glm::vec3 position) 
{
	
	worldTransform[3] = glm::vec4(position, worldTransform[3][3]);
	//uipdates the projection view matrix
	updateProjectionViewTransform();
}