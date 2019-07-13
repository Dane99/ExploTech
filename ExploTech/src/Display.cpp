#include "Display.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Display {
	
	GLFWwindow* window = nullptr;
	bool isWindowConstructed = false;

	void init()
	{
		// Ensure we can only create one window
		if (window == nullptr) 
		{
			glewExperimental = GL_TRUE;
			if (!glfwInit())
			{
				fprintf(stderr, "Failed to initialize GLFW\n");
				throw std::runtime_error("Error initializing GLFW.");
			}

			glfwWindowHint(GLFW_SAMPLES, 16); // TODO look at this more closely.
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			window = glfwCreateWindow(WIDTH, HEIGHT, "ExploTech", nullptr, nullptr);
			glfwMakeContextCurrent(window);

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// Ensure we can capture the escape key being pressed below
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

			glewInit();
			glViewport(0, 0, WIDTH, HEIGHT);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glDepthFunc(GL_LESS);
			glfwSwapInterval(0); //vsync off (on by default).
		}
	}

	void close()
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void clear()
	{
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	}

	void update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	bool isOpen()
	{
		return !glfwWindowShouldClose(window);
	}

	GLFWwindow* get()
	{
		// if window is not constructed yet, manually construct it. We do this because of active-type singletons (not very important).
		if (window == nullptr) 
		{
			init();
			return window;
		}
		else
		{
			return window;
		}
	}
}