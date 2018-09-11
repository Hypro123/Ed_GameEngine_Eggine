#include "Application.h"
#include"defines.h"

//constructor
Application::Application() {}

//destructor
Application::~Application() {}

//initialsies the application
int Application::Initialise()
{
	//is the applicaiton running
	m_IsRunning = true;
	//deltatime clock calculations
	m_startTime = myClock.now();
	m_currentTime = myClock.now();
	m_prevTime = myClock.now();

	//If, we can hook into the GPU
	if (glfwInit() == false)
	{
		//stop from starting if error
		//-1 is failure code
		return -1;
	}
	//creates a windows for openGL
	window = glfwCreateWindow(resolutionX, resolutionY, "Eggjine", nullptr, nullptr); //last 2 pointers allow for fullscreen/windowed, screen pointer

	if (window == nullptr)
	{
		//stop from starting if error
		//Clean up window and GPU linkage
		glfwTerminate();
		return -2;
	}

	//bring to front
	glfwMakeContextCurrent(window);

	// before loading interface functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		//stop from starting if error
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	//Open GL version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	//prints openGL version
	printf("GL: %i.%i\n", major, minor);
}

//runs the application
void Application::run()
{
	//clears the colour to the bellow values
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//sets max tris, lines and such
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	//running of the program
	if (startup())
	{

		while (glfwWindowShouldClose(window) == false &&
			m_IsRunning) {
			//DeltaTime calculations
			m_prevTime = m_currentTime;
			//gets current time
			m_currentTime = myClock.now();
			//gets the difference between the previous fram and the current one
			auto difference = m_currentTime - m_prevTime;
			//turns deltatime to seconds
			float deltaTime = difference.count() * NANO_TO_SECONDS;

			//Clearing buffer - Colour and depth checks
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			aie::Gizmos::clear();

			//keeps the program running until the appropriate key is pressed
			if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				//is running is set to false and the loop stops
				m_IsRunning = false;
			}
			//draw and update virtual functions are called
			update(deltaTime);
			draw();
			//swaps the buffers for the window
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		//cleanup
		shutdown();
		terminate();
	}
}
//clears the screen
void Application::clearScreen() {
	//clears the screen by clearing the colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//terminates the GLFW window
void Application::terminate()
{	
	//destoys all Gizmos
	aie::Gizmos::destroy();
	//destroys the window
	glfwDestroyWindow(window);
	//terminates glfw processes
	glfwTerminate();
}