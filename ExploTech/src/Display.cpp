#include "Display.h"

#include <memory>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Display {
	
	GLFWwindow* window;

	void init()
	{
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			getchar();
			throw std::runtime_error("Error initializing GLFW.");
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
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
	}

	void close()
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	void clear()
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
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
		return window;
	}
}