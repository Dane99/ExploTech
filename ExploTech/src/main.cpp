#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>

#include "Display.h"
#include "Application.h"

int main()
{
	Display::init();

	Application app;

	app.runMainGameLoop();

	return 0;

}