#pragma once

struct GLFWwindow;

namespace Display {

	constexpr static int WIDTH = 3000;
	constexpr static int HEIGHT = 2000;

	void init();
	void close();

	void clear();
	void update();

	bool isOpen();

	GLFWwindow* get();
}