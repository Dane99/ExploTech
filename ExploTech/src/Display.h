#pragma once

class GLFWwindow;

namespace Display {

	constexpr static int WIDTH = 1280;
	constexpr static int HEIGHT = 720;

	void init();
	void close();

	void clear();
	void update();

	bool isOpen();

	GLFWwindow* get();
}