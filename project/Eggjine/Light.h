#ifndef __LIGHT_H_
#define __LIGHT_H_

#include"ext.hpp"

//struct for the lights, stores all of their information
struct Light
{
	//light's direction
	glm::vec3 direction;
	//lights diffuse colour
	glm::vec3 diffuse;
	//lights specular colour
	glm::vec3 specular;
};

#endif