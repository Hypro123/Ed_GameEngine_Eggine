#ifndef __APP_H_
#define __APP_H_

#include<glm.hpp>
#include<ext.hpp>

#include"../dependencies/glCore/gl_core_4_5.h"
#include"glfw3.h"
#include<chrono>

#include"Gizmos.h"

//deltatime ease of use
using ullong = unsigned long long;
using nanoseconds = std::chrono::nanoseconds;

//stores values for ease of use for deltatime
static const double NANO_TO_SECONDS = 0.0000000001;
static const ullong NANO_IN_SECONDS = 1000000000ULL;

//used in namespace to avoid problems
namespace egg
{
	//stores clock and curent time
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;
};

class Application
{
public:
	//constructor for application
	Application();
	//destructor for application
	~Application();

	int Initialise(); //initialise
	void run(); //runs main loop
	void terminate(); //Clean Up

protected:
	//startup virtual function
	virtual bool startup() = 0;
	//shutdown virtual function
	virtual void shutdown() = 0;
	//update virtual function
	virtual void update(float deltaTime) = 0;
	//draw virtual function
	virtual void draw() = 0;
	//clears the screen
	void clearScreen();

protected:
	//stores window
	GLFWwindow * window;
	
	//uses namespace to avoid issues
	egg::clock myClock;
	egg::time m_startTime;
	egg::time m_currentTime;
	egg::time m_prevTime;
	
	//checks if the software is running or not
	bool m_IsRunning;
};

#endif