#include "Display.h"
#include "Application.h"

int main()
{
	Display::init();
	Application::get().runMainGameLoop();
	return 0;
}